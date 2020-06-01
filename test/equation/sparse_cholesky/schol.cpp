#include<iostream>
#include"../../test_utils.hpp"
#include"../include/monolish_equation.hpp"
#include"../include/monolish_blas.hpp"

int main(int argc, char** argv){

	if(argc!=3){
		std::cout << "error $1:matrix filename, $2:error check (1/0)" << std::endl;
		return 1;
	}

	char* file = argv[1];
	int check_ans = atoi(argv[2]);

	//monolish::util::set_log_level(3);
	//monolish::util::set_log_filename("./monolish_test_log.txt");

	monolish::equation::Cholesky Cholesky_solver;

	monolish::matrix::COO<double> COO(file);
	monolish::matrix::CRS<double> A(COO);

	// ans is 1
	monolish::vector<double> ans(A.get_row(), 1.0);
	monolish::vector<double> b(A.get_row(), 0.0);

	// initial x is rand(0~1)
	monolish::vector<double> x(A.get_row(), 0.0, 1.0);

	// data send gpu
	monolish::util::send(A, ans, b, x);

	// make ans
	monolish::blas::spmv(A, ans, b);

	//Cholesky_solver.set_reorder(1);
	
	//solve
	Cholesky_solver.solve(A, x, b);

	//std::cout << monolish::util::get_residual_l2(A,x,b) << std::endl;

	// data recv gpu
	ans.recv();
	x.recv();

	if(check_ans == 1){
		if(ans_check<double>(x.data(), ans.data(), x.size(), 1.0e-8) == false){
			x.print_all();
			return 1;
		};
	}


	return 0;
}
