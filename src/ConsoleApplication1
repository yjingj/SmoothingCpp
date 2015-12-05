
#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <random>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <vector>
using namespace std;


#include <cmath>
#include <cstdlib>

//#include "sub_basic.h"



#include "class_parameter_list.h"
#include "Gaussian_Sim.h"
#include "Read_Dat.h"
//#include "class_integrator.h"
//#include "class_solution.h"
//#include "class_stat.h"




int main()
{

	ParameterListClass parameter_list;
	ParameterListClass *ParameterList;
	ParameterList = &parameter_list;

	//StatClass AllData;
	Gaussian_Sim_Class Gaussian_sim;
	Read_Data_Class Read_Data_T, Read_Data_Y;
	

	// Read Parameters from file
	if (ParameterList->ReadParameters("params.in") < 0) {
		cout << "Exiting...\n";
		exit(1);
	 }

    ParameterList->Print_Parameter_List();




	Gaussian_sim.Print_Gaussian_DSN(ParameterList);
	if (Read_Data_T.Read_Dat_Func("Time_matrix.txt")
		|| Read_Data_Y.Read_Dat_Func("Y_sim_dat.txt")
		)
		cout << "Read data failed!" << endl;
	else {
		cout << "Read data success!" << endl;
		//Read_Data_T.print_dat_read();
		//cout << "=====================" << endl;
		//Read_Data_Y.print_dat_read();
	}
	cout << "Free data arrays  ... " << endl;
	Read_Data_T.Read_Dat_free_array();
	Read_Data_Y.Read_Dat_free_array();

	//else print_dat_read(Mu_func, test_vector);

	// Init Integrator
	//if(AllData.Init(ParameterList) < 0){
	//  AllData.Print_Init_ErrorMessage();
	//  cout << "Exiting...\n";
	//  exit(1);
	// }



	// AllData.PrintParameters();


	// if(AllData.write_soln_in_the_beginning())   AllData.WriteSolution();



	// while(AllData.integrate()) {
	//  AllData.make_one_step();
	//  AllData.UpdateTimeVariables();
	//  AllData.PrintMessage();
	//  AllData.WriteSolution();

	//  AllData.ComputeStat();
	//   AllData.Print_Running_Stat();
	// }

	// AllData.OutputStat();

	return 0;
}
