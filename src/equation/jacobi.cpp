#include "../../include/monolish_equation.hpp"
#include "../../include/monolish_blas.hpp"
#include<iostream>

namespace monolish{

	//Jacobi solver
	int equation::Jacobi::monolish_Jacobi(matrix::CRS<double> &A, vector<double> &x, vector<double> &b){
		Logger& logger = Logger::get_instance();
		logger.solver_in(monolish_func);

		x = A.get_diag();
		blas::spmv(A, b, x); // x = Ab

		logger.solver_out();
		return 0;
	}
	// Jacobi solver
	int equation::Jacobi::solve(matrix::CRS<double> &A, vector<double> &x, vector<double> &b){
		int ret = monolish_Jacobi(A, x, b);
		return ret;
	}

	int equation::Jacobi::Pinit(matrix::CRS<double> &A, vector<double> &x, vector<double> &b){
		return 0;
	}

	int equation::Jacobi::Papply(matrix::CRS<double> &A, vector<double> &x, vector<double> &b){
		return 0;
	}
}