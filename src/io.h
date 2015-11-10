#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>
#include <string>
#include <iomanip>
#include <sstream>
#include <eigen3/Eigen/Dense>
#include <algorithm>


void ReadParamfile(const string &fd_file);

void ReadGrids(const string &grid_file);

void WriteCov();

void WriteSignal();

void WriteMean();

#endif