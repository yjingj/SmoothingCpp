#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "base_func.h"
using namespace std;

const char * READ_DAT_PATH = "C:/Users/z084079/Documents/Visual Studio 2015/Projects/test_c++/ConsoleApplication1/ConsoleApplication1/Sim_data_output/";


class Read_Data_Class {
private:
	double ** Dat_array;
	vector<int> ncol;

public:
	int Read_Dat_Func(char* filename);
	void print_dat_read();
	void Read_Dat_free_array();

};



int  Read_Data_Class::Read_Dat_Func(char* filename) {
	
	char Path[500];
	char * Path_pt;
	char * pch, *nch;
	string temp_str, temp_str2;
	int cw,tab_count,row=0;
	ifstream InputFile;

	ncol.clear();

	strncpy_s(Path, READ_DAT_PATH, 500);
	strncat_s(Path, filename, 500);

	Path_pt = Path;
	
	InputFile.open(Path_pt, ios::in);

	if (InputFile.fail()) {
		cout << "Cannot open " << Path_pt << " for Inputting!!" << endl;;
		return -1;
	}
	else cout << "Start reading file from" << Path_pt <<"!"<< endl;

	while (!InputFile.eof()) {
		getline(InputFile, temp_str);
		pch = (char *)temp_str.c_str();
		cw = countWords(pch);
		ncol.push_back(cw);
		//cout << ncol[(ncol.size() - 1)] << " and cw = " << cw << endl;
	}
	cout <<"the size of the vector is "<< ncol.size() << endl;

	Dat_array = new double *[ncol.size()];

	for (unsigned i = 0; i < ncol.size(); i++) {
		Dat_array[i] = new double[ncol[i]];
	}

	InputFile.close();

	InputFile.open(Path_pt, ios::in);

	while (!InputFile.eof()) {
		getline(InputFile, temp_str);
		pch = (char *)temp_str.c_str();
		for (tab_count = 0; pch != NULL; tab_count++) {
			nch = strchr(pch, '\t');
			if (nch == NULL) 
				temp_str2.assign(pch);
			else temp_str2.assign(pch, nch - pch);
			Dat_array[row][tab_count] = strtod(temp_str2.c_str(), NULL);
			pch = (nch == NULL) ? NULL : nch + 1;
		}
		row++;
	}

	InputFile.close();
	return 0;
}


void  Read_Data_Class::print_dat_read() {
	for (unsigned i = 0; i < ncol.size(); i++) {
		for (int j = 0; j < ncol[i]; j++) {
			cout << Dat_array[i][j] << " ";
		}
		cout << endl;
	}
}

void  Read_Data_Class::Read_Dat_free_array() {
	for (unsigned i = 0; i < ncol.size(); i++)
		delete[] Dat_array[i];
	delete[] Dat_array;
}
