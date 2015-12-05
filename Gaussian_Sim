#pragma once
// Class Gaussian Data simulator 
// This Class generates simulated data which comes from a given Gaussian Process;

#define PI 3.141592654



#include <gsl/gsl_linalg.h>
#include <gsl/gsl_sf_bessel.h>
#include <algorithm>
#include <vector>
#include <iomanip>

const char * GAUS_SIM_DAT_PATH = "C:/Users/z084079/Documents/Visual Studio 2015/Projects/test_c++/ConsoleApplication1/ConsoleApplication1/Sim_data_output/";

struct Gaussian_Sim_Dat
{
	int n;
	int	p;
	double dis;
	double rho; 
	double nu;
	double phi;
	double mu;
	double sf;
	double snr;
	double dense;
	gsl_matrix * X_true;
	gsl_matrix * X_true_spars;
	gsl_matrix * Y_sim;
	gsl_matrix * Y_sim_spars;
	gsl_matrix * T_time;
	gsl_matrix * T_time_spars;
	//gsl_matrix * Idx;
	gsl_matrix * C_Tcov;
	gsl_matrix * Mu_fun;
	//gsl_matrix * t;
};

typedef Gaussian_Sim_Dat * GSD_Element_pt;


//================================
//================================
//
//Definition of the Class
//
//================================
//================================

class  Gaussian_Sim_Class {

private:
	Gaussian_Sim_Dat Init0;
	double Matern_function(double D, double rho, double nu, double phi);
	
public:
	
	GSD_Element_pt Init_Gaussian_sim(ParameterListClass *ParameterList);
	//void test_func(ParameterListClass *ParameterList);
	GSD_Element_pt Generate_Gaussian_sim(ParameterListClass *ParameterList);
	int Random_Sampling_Index(vector<int> & rand_sample_index, int pool_size, int sample_size, const char if_replace);
	void Print_Gaussian_DSN(ParameterListClass *ParameterList);
	int Write_MatrixDate(gsl_matrix* DSN, int  row_n, int  col_n, char * filename);

};

/*
Constructor
*/







//==============================



GSD_Element_pt Gaussian_Sim_Class::Init_Gaussian_sim(ParameterListClass *ParameterList) {
	
	int spars_length;

	GSD_Element_pt Init_pt;

	
	Init_pt = &Init0;

	if (ParameterList->LookupParameter("p", &Init_pt->p) < 0) {
		cout << "Read Parameter (P) with Error, progam end!" << endl;
		exit(EXIT_FAILURE);
	}
	else if (ParameterList->LookupParameter("n", &Init_pt->n) < 0) {
		cout << "Read Parameter (n) with Error, progam end!" << endl;
		exit(EXIT_FAILURE);
	}
	else if (ParameterList->LookupParameter("rho", &Init_pt->rho) < 0){
		cout << "Read Parameter (rho) with Error, progam end!" << endl;
		exit(EXIT_FAILURE);
	}
	else if (ParameterList->LookupParameter("mu", &Init_pt->mu) < 0) {
		cout << "Read Parameter (mu) with Error, progam end!" << endl;
		exit(EXIT_FAILURE);
	}
	else if (ParameterList->LookupParameter("nu", &Init_pt->nu) < 0) {
		cout << "Read Parameter (nu) with Error, progam end!" << endl;
		exit(EXIT_FAILURE);
	}
	else if (ParameterList->LookupParameter("sf", &Init_pt->sf) < 0) {
		cout << "Read Parameter (sf) with Error, progam end!" << endl;
		exit(EXIT_FAILURE);
	}
	else if (ParameterList->LookupParameter("snr", &Init_pt->snr) < 0) {
		cout << "Read Parameter (snr) with Error, progam end!" << endl;
		exit(EXIT_FAILURE);
	}
	else if (ParameterList->LookupParameter("dense", &Init_pt->dense) < 0) {
		cout << "Read Parameter (dense) with Error, progam end!" << endl;
		exit(EXIT_FAILURE);
	}

	spars_length = int(ceil(Init_pt->dense*Init_pt->p));
	

	//Init_pt->t = gsl_matrix_alloc(1, Init_pt->p);
	Init_pt->Mu_fun = gsl_matrix_alloc(1, Init_pt->p);
	//Init_pt->Idx = gsl_matrix_alloc(1, Init_pt->p);
	Init_pt->X_true = gsl_matrix_alloc(Init_pt->n, Init_pt->p);
	Init_pt->X_true_spars = gsl_matrix_alloc(Init_pt->n,  spars_length);
	Init_pt->Y_sim = gsl_matrix_alloc(Init_pt->n, Init_pt->p);
	Init_pt->Y_sim_spars = gsl_matrix_alloc(Init_pt->n,  spars_length);
	Init_pt->T_time = gsl_matrix_alloc(Init_pt->n, Init_pt->p);
	Init_pt->T_time_spars = gsl_matrix_alloc(Init_pt->n, spars_length);
	Init_pt->C_Tcov = gsl_matrix_alloc(Init_pt->p, Init_pt->p);


	cout << "Initialzing Gaussian Simulation Data Success!" << endl;
	return Init_pt;

}

GSD_Element_pt Gaussian_Sim_Class::Generate_Gaussian_sim(ParameterListClass *ParameterList) {
	
	int spars_length, int_temp;

	double phi, dis, temp, temp_mu, noise_num, sn;

	char Station_Index[100];

	GSD_Element_pt Output_pt;

	Output_pt = Init_Gaussian_sim(ParameterList);

	gsl_matrix * t = gsl_matrix_alloc(1, Output_pt->p);
	gsl_matrix * Noise = gsl_matrix_alloc(Output_pt->n, Output_pt->p);
	gsl_matrix * Temp_chol = gsl_matrix_alloc(Output_pt->p, Output_pt->p);
	gsl_matrix * Singal_part1 = gsl_matrix_alloc(Output_pt->n, Output_pt->p);
	gsl_matrix * Singal_part2 = gsl_matrix_alloc(Output_pt->n, Output_pt->p);

	std::default_random_engine random_generator;
	std::normal_distribution<double> Norm_Dist(0, 1);


	//===== create t vector ====//
	for (int i = 0; i < Output_pt->p; i++) {
		gsl_matrix_set(t, 0, i, PI / (2 * Output_pt->p - 2)*i);
	}

	phi = pow(Output_pt->sf, 2);

	//==== create mu_function , covaraince matrix, and random noise matrix ======//
	if (ParameterList->LookupParameter("STATIONARY_SIM", Station_Index) == 0) {
		//cout << "Out Put Station_index" << Station_Index << endl;
		if (strcasecmp(Station_Index, "YES") == 0) {
			for (int i = 0; i < Output_pt->p; i++) {
				// generate stationary mu_function vector//
				temp_mu = 3 * sin(gsl_matrix_get(t, 0, i) * 4);
				gsl_matrix_set(Output_pt->Mu_fun, 0, i, temp_mu);
				// generate stationary covariance matrix //
				for (int j = 0; j < Output_pt->p; j++) {
					dis = fabs(gsl_matrix_get(t, 0, i) - gsl_matrix_get(t, 0, j));
					gsl_matrix_set(Output_pt->C_Tcov, i, j, Matern_function(dis, Output_pt->rho, Output_pt->nu, phi));
				}
				// generate noise matrix size p*n//
				for (int j = 0; j < Output_pt->n; j++) {
					noise_num = Norm_Dist(random_generator);
					gsl_matrix_set(Noise, j, i, noise_num);
				}

			}
		}
		else if (strcasecmp(Station_Index, "NO") == 0) {
			for (int i = 0; i < Output_pt->p; i++) {
				// generate Non-stationary mu_function vector//
				temp = gsl_matrix_get(t, 0, i);
				temp_mu = (temp + 0.5) * 3 * sin(pow(temp, 1.5) * 4);
				// generate Non-stationary covariance matrix //
				for (int j = 0; j < Output_pt->p; j++) {
					dis = fabs(pow(gsl_matrix_get(t, 0, i), 1.5) - pow(gsl_matrix_get(t, 0, j), 1.5));
					temp = (gsl_matrix_get(t, 0, i) + 0.5) * (gsl_matrix_get(t, 0, j) + 0.5)*Matern_function(dis, Output_pt->rho, Output_pt->nu, phi);
					gsl_matrix_set(Output_pt->C_Tcov, i, j, temp);
				}
				// generate noise matrix size p*n//
				for (int j = 0; j < Output_pt->n; j++) {
					noise_num = Norm_Dist(random_generator);
					gsl_matrix_set(Noise, j, i, noise_num);
				}
			}
		}
		else {
			cout << "Undefined Stationary indication. Must be Yes or NO! Program ends!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	else {
		cout << "Read Stationary indication variable wrong! Program end!" << endl;
		exit(EXIT_FAILURE);
	}

	//==== Generate functional data on pooled grid  =====//
	if (gsl_matrix_memcpy(Temp_chol, Output_pt->C_Tcov)) {
		cout << "Copy covariance matrix with error!" << endl;
		exit(EXIT_FAILURE);
	}

	else {
		if (gsl_linalg_cholesky_decomp(Temp_chol)) {
			cout << "Cholesky decompistion falied" << endl;
			exit(EXIT_FAILURE);
		}
		else {
			for (int i = 0; i < Output_pt->p; i++) {
				for (int j = i + 1; j < Output_pt->p; j++) {
					gsl_matrix_set(Temp_chol, i, j, 0);
				}
			}
			cout << "Cholesky decompistion Successed" << endl;
		}
	}
	// Generate true , simulated signal and time matrix//
	gsl_matrix_set_zero(Singal_part1);
	gsl_matrix_memcpy(Singal_part2, Noise);
	sn = Output_pt->sf / Output_pt->snr;
	if (gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, Noise, Temp_chol, 0.0, Singal_part1) && gsl_matrix_scale(Singal_part2, sn)) {
		cout << "Generate True signal Step 1 error!" << endl;
		exit(EXIT_FAILURE);
	}
	else {
		for (int i = 0; i < Output_pt->n; i++) {
			for (int j = 0; j < Output_pt->p; j++) {
				gsl_matrix_set(Output_pt->X_true, i, j, gsl_matrix_get(Singal_part1, i, j) + gsl_matrix_get(Output_pt->Mu_fun, 0, j));
				gsl_matrix_set(Output_pt->T_time, i, j, gsl_matrix_get(t, 0, j));
			}
		}
		if (gsl_matrix_memcpy(Output_pt->Y_sim, Output_pt->X_true) && gsl_matrix_sub(Output_pt->Y_sim, Singal_part2)) {
			cout << "Generate Simulate signal error!" << endl;
			exit(EXIT_FAILURE);
		}
		else cout << "Generate ture and simulated signal successd!" << endl;
	}

	//====Create Random Sampled functional data ====//
	// create spars grid data //
	spars_length = int(ceil(Output_pt->dense*Output_pt->p));
	//cout << spars_length << endl;
	std::vector<int> rand_index;
	for (int loop = 0; loop < Output_pt->n; loop++) {
		if (!Random_Sampling_Index(rand_index, Output_pt->p, spars_length, 'N')) {
			//cout << rand_index.size() << endl;
			sort(rand_index.begin(), rand_index.end());
			for (int j = 0; j < spars_length; j++) {
				int_temp = rand_index[j];
				//cout << int_temp << endl;
				gsl_matrix_set(Output_pt->T_time_spars, loop, j, gsl_matrix_get(t, 0, int_temp));
				gsl_matrix_set(Output_pt->X_true_spars, loop, j, gsl_matrix_get(Output_pt->X_true, loop, int_temp));
				gsl_matrix_set(Output_pt->Y_sim_spars, loop, j, gsl_matrix_get(Output_pt->Y_sim, loop, int_temp));
			}
		}
		else {
			cout << "Error happened at " << loop << " th iteration. Program End" << endl;
			exit(EXIT_FAILURE);
		}
	}


	//==== free temp matrix ====//
	gsl_matrix_free(t);
	gsl_matrix_free(Noise);
	gsl_matrix_free(Temp_chol);
	gsl_matrix_free(Singal_part1);
	gsl_matrix_free(Singal_part2);



   //===return function value===//
	return Output_pt;
}

double Gaussian_Sim_Class::Matern_function(double D, double rho, double nu, double phi) {
	
	double dm, con, ac;

	dm = D * (sqrt(2 * nu) / rho);

	if (dm == 0) {
			dm = 0.000000001;
	}

	if (D < 0) {
		cout << "distance argument must be nonnegative. Progam end with Error!" << endl;
		exit(EXIT_FAILURE);
	}
	con = 1 / (pow(2, (nu - 1)))*tgamma(nu);
	ac = (phi)*con*pow(dm, nu)*gsl_sf_bessel_Knu(nu, dm); // need change//

	return ac;
}

int Gaussian_Sim_Class::Random_Sampling_Index(vector<int> & rand_sample_index, int pool_size, int sample_size, const char if_replacement) {

	rand_sample_index.clear();

	if (strcasecmp(&if_replacement, "Y") == 0) {
		for (int i = 0; i < sample_size; ++i) {
			rand_sample_index.push_back(rand()% pool_size);
		}
		//cout << "Generate random sample index WITH replacement success!" << endl;
		return 0;
	}
	else if (strcasecmp(&if_replacement, "N") == 0) {
		std::random_device device;
		std::mt19937 generator(device());
		std::uniform_int_distribution<> distribution(0, pool_size-1);
		// Generate a vector with all possible numbers and shuffle it.
	    for (int i = 0; i < pool_size; ++i)
			rand_sample_index.push_back(i);
		std::random_shuffle(rand_sample_index.begin(), rand_sample_index.end());
			// Truncate to the requested size.
		rand_sample_index.resize(sample_size);
		//cout << "Generate random sample index WITHOUT replacement success!" << endl;
		return 0;
	}

	else {
		cout << "Generate random sample index with Error, Please check!";
		return 1;
	}


}


void Gaussian_Sim_Class::Print_Gaussian_DSN(ParameterListClass *ParameterList) {

	int spars_length;
	int error=0;

	GSD_Element_pt sim_dsn;

	sim_dsn = Generate_Gaussian_sim(ParameterList);

	spars_length= int(ceil(sim_dsn->dense*sim_dsn->p));

	error = Write_MatrixDate(sim_dsn->X_true, sim_dsn->n, sim_dsn->p, "X_true_dat.txt") + error;
	error = Write_MatrixDate(sim_dsn->X_true_spars, sim_dsn->n, spars_length, "X_true_spars_dat.txt") + error;
	error = Write_MatrixDate(sim_dsn->Y_sim, sim_dsn->n, sim_dsn->p, "Y_sim_dat.txt") + error;
	error = Write_MatrixDate(sim_dsn->Y_sim_spars, sim_dsn->n, spars_length, "Y_sim_spars_dat.txt") + error;
	error = Write_MatrixDate(sim_dsn->C_Tcov, sim_dsn->p, sim_dsn->p, "True_Corvariance_dat.txt");
	error = Write_MatrixDate(sim_dsn->Mu_fun, 1, sim_dsn->p, "Mu_fun_dat.txt") + error;
	error = Write_MatrixDate(sim_dsn->T_time, sim_dsn->n, sim_dsn->p, "Time_matrix.txt") + error;
	error = Write_MatrixDate(sim_dsn->T_time_spars, sim_dsn->n, spars_length, "Time_spars_matrix.txt") + error;

	if (error == 0)
		cout << "All Gaussian simulation data files have been outputed!" << endl;
	else cout << "There is an error in outputting Gaussian simulation data process. Please check!!!" << endl;
	

	gsl_matrix_free(sim_dsn->Mu_fun);
	gsl_matrix_free(sim_dsn->C_Tcov);
	gsl_matrix_free(sim_dsn->X_true);
	gsl_matrix_free(sim_dsn->X_true_spars);
	gsl_matrix_free(sim_dsn->Y_sim);
	gsl_matrix_free(sim_dsn->Y_sim_spars);
	gsl_matrix_free(sim_dsn->T_time);
	gsl_matrix_free(sim_dsn->T_time_spars);

}

int Gaussian_Sim_Class::Write_MatrixDate(gsl_matrix* DSN, int row_n, int col_n, char * filename) {

	char Path[500];
	char * Path_pt;

	strncpy_s(Path, GAUS_SIM_DAT_PATH, 500);
	strncat_s(Path, filename, 500);

	Path_pt = Path;

	std::fstream tempfile;
	tempfile.open(Path_pt, std::fstream::out);



	if (!tempfile.is_open()) {
		cout << "Cannot open " << filename << " for writing!!" << endl;;
		return -1;
	}

	else{
		for (int j = 0; j < row_n; j++) {
			for (int i = 0; i < col_n; i++) {
				if (i < (col_n - 1))
					tempfile << scientific << setprecision(5) << gsl_matrix_get(DSN, j, i) << '\t';
				else tempfile << scientific << setprecision(5) << gsl_matrix_get(DSN, j, i);
			}
			if (j< (row_n-1)) tempfile << endl;
		}
		cout << "Writing file "<< filename <<" Success" << endl;
		tempfile.close();
		return 0;
	}

}
