// this code is generated by gen_matvec_blas.sh
#include "../../../../include/monolish_blas.hpp"
#include "../../../internal/monolish_internal.hpp"
#include "crs-dense_matmul.hpp"
#include "dense-dense_matmul.hpp"
#include "linearoperator-dense_matmul.hpp"
#include "linearoperator-linearoperator_matmul.hpp"

namespace monolish::blas {

void matmul(const matrix::Dense<double> &A, const matrix::Dense<double> &B,
            matrix::Dense<double> &C) {
  Dense_Dense_Dmatmul_core(1.0, A, B, 0.0, C, false, false);
}
void matmul(const double &a, const matrix::Dense<double> &A,
            const matrix::Dense<double> &B, const double &b,
            matrix::Dense<double> &C) {
  Dense_Dense_Dmatmul_core(a, A, B, b, C, false, false);
}
void matmul(const matrix::Dense<float> &A, const matrix::Dense<float> &B,
            matrix::Dense<float> &C) {
  Dense_Dense_Smatmul_core(1.0, A, B, 0.0, C, false, false);
}
void matmul(const float &a, const matrix::Dense<float> &A,
            const matrix::Dense<float> &B, const float &b,
            matrix::Dense<float> &C) {
  Dense_Dense_Smatmul_core(a, A, B, b, C, false, false);
}

void matmul(const matrix::CRS<double> &A, const matrix::Dense<double> &B,
            matrix::Dense<double> &C) {
  CRS_Dense_Dmatmul_core(1.0, A, B, 0.0, C);
}
void matmul(const double &a, const matrix::CRS<double> &A,
            const matrix::Dense<double> &B, const double &b,
            matrix::Dense<double> &C) {
  CRS_Dense_Dmatmul_core(a, A, B, b, C);
}
void matmul(const matrix::CRS<float> &A, const matrix::Dense<float> &B,
            matrix::Dense<float> &C) {
  CRS_Dense_Smatmul_core(1.0, A, B, 0.0, C);
}
void matmul(const float &a, const matrix::CRS<float> &A,
            const matrix::Dense<float> &B, const float &b,
            matrix::Dense<float> &C) {
  CRS_Dense_Smatmul_core(a, A, B, b, C);
}

} // namespace monolish::blas
