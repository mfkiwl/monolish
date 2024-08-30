// This code is generated by gen_scal.sh
#include "crs_scal.hpp"
#include "dense_scal.hpp"

namespace monolish::blas {

void mscal(const double alpha, matrix::Dense<double> &A) {
  mscal_core(alpha, A);
}
void mscal(const double alpha, view_Dense<vector<double>, double> &A) {
  mscal_core(alpha, A);
}
void mscal(const double alpha, view_Dense<matrix::Dense<double>, double> &A) {
  mscal_core(alpha, A);
}
void mscal(const double alpha,
           view_Dense<tensor::tensor_Dense<double>, double> &A) {
  mscal_core(alpha, A);
}
void mscal(const float alpha, matrix::Dense<float> &A) { mscal_core(alpha, A); }
void mscal(const float alpha, view_Dense<vector<float>, float> &A) {
  mscal_core(alpha, A);
}
void mscal(const float alpha, view_Dense<matrix::Dense<float>, float> &A) {
  mscal_core(alpha, A);
}
void mscal(const float alpha,
           view_Dense<tensor::tensor_Dense<float>, float> &A) {
  mscal_core(alpha, A);
}

void mscal(const double alpha, matrix::CRS<double> &A) { mscal_core(alpha, A); }
void mscal(const float alpha, matrix::CRS<float> &A) { mscal_core(alpha, A); }
} // namespace monolish::blas