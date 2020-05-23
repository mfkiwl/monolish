#include<iostream>
#include<typeinfo>

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<openacc.h>
#include "../../../include/monolish_blas.hpp"

#ifdef USE_GPU
	#include<cublas.h>
#else
	#include<cblas.h>
#endif
namespace monolish{

	// double ///////////////////
	void blas::axpy(const double alpha, const vector<double> &x, vector<double> &y){
		Logger& logger = Logger::get_instance();
		logger.func_in(monolish_func);

		//err
		if( x.size() != y.size()){
			throw std::runtime_error("error vector size is not same");
		}

		const double* xd = x.data();
		double* yd = y.data();
		size_t size = x.size();
	
#if USE_GPU

		#pragma acc host_data use_device(xd, yd)
		{
			cublasDaxpy(size, alpha, xd, 1, yd, 1);
		}
#else
		cblas_daxpy(size, alpha, xd, 1, yd, 1);
#endif
		logger.func_out();
	}
}
