#include "main.h"
#include "io.h"
#include "nlopt.hpp"

//#define MATHLIB_STANDALONE      
//#include    "Rmath.h" 

using namespace Eigen;
using namespace std;

typedef Matrix<bool, Dynamic, Dynamic> Matrixb;
typedef Matrix<double, Dynamic, 1> VectorXd;

int main (int argc, char **argv)
{
	// Retrieve the (non-option) argument:
    if ( (argc <= 1) || (argv[argc-1] == NULL) || (argv[argc-1][0] == '-') ) {  // there is NO input...
        cerr << "No argument provided!" << endl;
        return 1;
    }

    int opt;
    opterr = 0;

    string fd_file, grid_file, mean_file, cov_file;
    int delta, mcmc_itr, mcmc_burnin; 
    bool matern;
    double w, ws, sd_noise, nu, rho, sd_signal;


    // Retrieve the options:
    while ( (opt = getopt(argc, argv, "d:g:a:i:b:m:w:v:n:u:r:s:M:C")) != -1 ) {  // for each option...
        switch ( opt ) {
            case 'd':
                fd_file=optarg;
                break;
            case 'g':
                grid_file=optarg;
                break;
            case 'a':
                delta=atoi(optarg);
                break;
            case 'i':
                mcmc_itr=atoi(optarg);
                break;
            case 'b':
                mcmc_burnin=atoi(optarg);
                break;
            case 'm':
                matern=atoi(optarg);
                break;
            case 'w':
                w=atod(optarg);
                break;    
            case 'v':
                ws=atod(optarg);
                break;
            case 'n':
                sd_noise=atod(optarg);
                break;
            case 'u':
                nu=atod(optarg);
                break;
            case 'r':
                rho=atod(optarg);
                break;
            case 's':
                sd_signal=atod(optarg);
                break;
            case '?':  // unknown option...
                    cerr << "Unknown option: '" << char(optopt) << "'!" << endl;
                break;
        }
    }

    // Debug:
    cout << "fd_file = " << fd_file << "; grid_file = " << grid_file << endl;
    cout << "delta = " << delta << "; matern = "<< matern << endl; 
    cout << "mcmc_burnin = " << mcmc_burnin << "; mcmc_itr = "<< mcmc_itr << endl;
    cout << "w = " << w << "; ws = "<< ws << endl;
    cout << "nu = " << nu << "; rho = "<< rho << endl;
    cout << "sd_noise = " << sd_noise << "; sd_signal = "<< sd_signal << endl;
    cout << "w = " << w << "; ws = "<< ws << endl;


    // Generate functional data from given GP 


    //Load in functional data (grids + signals)


    // obtain sample mean and covariance estimates (smoothed)


    // call BABF to smooth raw signals


    // write outputs (smoothed signals + mean-covariance estiamtes)


    // write outputs (estimates for other parameters)
	



	return 0;
}