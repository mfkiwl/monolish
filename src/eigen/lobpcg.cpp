#include "../../include/monolish_blas.hpp"
#include "../../include/monolish_eigen.hpp"
#include "../../include/monolish_lapack.hpp"
#include "../internal/monolish_internal.hpp"

namespace monolish {

template <typename MATRIX, typename T>
int eigen::LOBPCG<MATRIX, T>::monolish_LOBPCG(MATRIX const &A, T &l,
                                      monolish::vector<T> &x) {
  T residual = 1.0;
  T norm;
  std::size_t iter = 0;

  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  // Algorithm following DOI:10.1007/978-3-319-69953-0_14
  x[0] = 1.0;
  x[1] = -1.0;
  blas::nrm2(x, norm);
  blas::scal(1.0 / norm, x);
  monolish::vector<T> w(A.get_row());
  monolish::vector<T> p(A.get_row());
  monolish::vector<T> X(A.get_row());
  monolish::vector<T> W(A.get_row());
  monolish::vector<T> P(A.get_row());

  // X = A x
  blas::matvec(A, x, X);
  // mu = (x, X)
  T mu;
  blas::dot(x, X, mu);
  // w = X - mu x
  monolish::vector<T> vtmp1(A.get_row());
  vtmp1 = x;
  blas::scal(mu, vtmp1);
  blas::vecsub(X, vtmp1, w);
  blas::nrm2(w, norm);
  blas::scal(1.0 / norm, w);

  do {
    // W = A w
    blas::matvec(A, w, W);

    std::vector<T> Sa;
    std::vector<T> Sb;
    if (iter > 0) {
      // Sa = { w, x, p }^T { W, X, P }
      //    = { w, x, p }^T A { w, x, p }
      Sa.resize(9);
      blas::dot(w, W, Sa[0]);
      blas::dot(w, X, Sa[1]);
      blas::dot(w, P, Sa[2]);
      blas::dot(x, W, Sa[3]);
      blas::dot(x, X, Sa[4]);
      blas::dot(x, P, Sa[5]);
      blas::dot(p, W, Sa[6]);
      blas::dot(p, X, Sa[7]);
      blas::dot(p, P, Sa[8]);

      // Sb = { w, x, p }^T { w, x, p }
      Sb.resize(9);
      blas::dot(w, w, Sb[0]);
      blas::dot(w, x, Sb[1]);
      blas::dot(w, p, Sb[2]);
      blas::dot(x, w, Sb[3]);
      blas::dot(x, x, Sb[4]);
      blas::dot(x, p, Sb[5]);
      blas::dot(p, w, Sb[6]);
      blas::dot(p, x, Sb[7]);
      blas::dot(p, p, Sb[8]);
    } else {
      // Sa = { w, x }^T { W, X }
      //    = { w, x }^T A { w, x }
      Sa.resize(4);
      blas::dot(w, W, Sa[0]);
      blas::dot(w, X, Sa[1]);
      blas::dot(x, W, Sa[2]);
      blas::dot(x, X, Sa[3]);

      // Sb = { w, x }^T { w, x }
      Sb.resize(4);
      blas::dot(w, w, Sb[0]);
      blas::dot(w, x, Sb[1]);
      blas::dot(x, w, Sb[2]);
      blas::dot(x, x, Sb[3]);
    }
    matrix::Dense<T> Sam(std::sqrt(Sa.size()), std::sqrt(Sa.size()), Sa);
    matrix::Dense<T> Sbm(std::sqrt(Sb.size()), std::sqrt(Sb.size()), Sb);

    // Generalized Eigendecomposition
    //   Sa v = lambda Sb v
    monolish::vector<T> lambda(Sam.get_col());
    const char jobz = 'V';
    const char uplo = 'L';
    bool bl = lapack::sygv(1, &jobz, &uplo, Sam, Sbm, lambda);
    if (!bl) {
      throw std::runtime_error("LAPACK sygv failed");
    }
    std::size_t index = 0;
    l = lambda[index];

    // extract b which satisfies Aprime b = lambda_min b
    monolish::vector<T> b(Sam.get_col());
    Sam.col(index, b);

    if (iter > 0) {
      // x = b[0] w + b[1] x + b[2] p, normalize
      // p = b[0] w          + b[2] p, normalize
      blas::scal(b[0], w);
      blas::scal(b[1], x);
      blas::scal(b[2], p);
      blas::vecadd(w, p, p);
      blas::vecadd(x, p, x);

      // X = b[0] W + b[1] X + b[2] P, normalize with x
      // P = b[0] W          + b[2] P, normalize with p
      blas::scal(b[0], W);
      blas::scal(b[1], X);
      blas::scal(b[2], P);
      blas::vecadd(W, P, P);
      blas::vecadd(X, P, X);
    } else {
      // x = b[0] w + b[1] x, normalize
      // p = b[0] w         , normalize
      blas::scal(b[0], w);
      blas::scal(b[1], x);
      blas::vecadd(w, p, p);
      blas::vecadd(x, p, x);

      // X = b[0] W + b[1] X, normalize with x
      // P = b[0] W         , normalize with p
      blas::scal(b[0], W);
      blas::scal(b[1], X);
      blas::vecadd(W, P, P);
      blas::vecadd(X, P, X);
    }
    T normp;
    blas::nrm2(p, normp);
    blas::scal(1.0 / normp, p);
    T normx;
    blas::nrm2(x, normx);
    blas::scal(1.0 / normx, x);
    blas::scal(1.0 / normp, P);
    blas::scal(1.0 / normx, X);

    // w = X - lambda x
    vtmp1 = x;
    blas::scal(l, vtmp1);
    blas::vecsub(X, vtmp1, w);

    // residual calculation and normalize
    blas::nrm2(w, residual);
    blas::scal(1.0 / residual, w);
    if (this->get_print_rhistory()) {
      *this->rhistory_stream << iter + 1 << "\t" << std::scientific << residual
                             << std::endl;
    }
    ++iter;
  } while (residual > this->get_tol() || iter < this->get_maxiter());
  logger.func_out();
  if (iter >= this->get_maxiter()) {
    return MONOLISH_SOLVER_MAXITER;
  } else if (residual > this->get_tol()) {
    return MONOLISH_SOLVER_RESIDUAL_NAN;
  } else {
    return MONOLISH_SOLVER_SUCCESS;
  }
}

template int
eigen::LOBPCG<matrix::CRS<double>, double>::monolish_LOBPCG(matrix::CRS<double> const &A, double &l,
                                       vector<double> &x);
template int
eigen::LOBPCG<matrix::LinearOperator<double>, double>::monolish_LOBPCG(matrix::LinearOperator<double> const &A, double &l,
                                       vector<double> &x);

template <typename MATRIX, typename T>
int eigen::LOBPCG<MATRIX, T>::solve(MATRIX const &A, T &l, vector<T> &x) {
  Logger &logger = Logger::get_instance();
  logger.solver_in(monolish_func);

  int ret = 0;
  if (this->lib == 0) {
    ret = monolish_LOBPCG(A, l, x);
  }

  logger.solver_out();
  return ret; // err code
}
template int eigen::LOBPCG<matrix::CRS<double>, double>::solve(matrix::CRS<double> const &A,
                                          double &l, vector<double> &x);
template int eigen::LOBPCG<matrix::LinearOperator<double>, double>::solve(matrix::LinearOperator<double> const &A,
                                          double &l, vector<double> &x);
} // namespace monolish
