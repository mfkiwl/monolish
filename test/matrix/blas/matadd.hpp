#include "../../test_utils.hpp"

template <typename T>
void ans_matadd(const monolish::matrix::Dense<T> &A,
                const monolish::matrix::Dense<T> &B,
                monolish::matrix::Dense<T> &C) {

  if (A.get_row() != B.get_row()) {
    std::runtime_error("A.row != B.row");
  }
  if (A.get_col() != B.get_col()) {
    std::runtime_error("A.col != B.col");
  }

  // MN=MN+MN
  int M = A.get_row();
  int N = A.get_col();

  for (int i = 0; i < A.get_nnz(); i++) {
    C.begin()[i] = A.begin()[i] + B.begin()[i];
  }
}

template <typename T, typename MAT_A, typename MAT_B, typename MAT_C>
bool test_send_matadd_core(const size_t M, const size_t N, double tol,
                           monolish::matrix::Dense<T> &AA,
                           monolish::matrix::Dense<T> &BB,
                           monolish::matrix::Dense<T> &CC, MAT_A &A, MAT_B &B,
                           MAT_C &C) {
  ans_matadd(AA, BB, CC);
  monolish::matrix::COO<T> ansC(CC);

  monolish::util::send(A, B, C);
  monolish::blas::matadd(A, B, C);
  monolish::util::recv(A, B, C);

  monolish::matrix::COO<T> resultC(C);

  return ans_check<T>(__func__, A.type(), resultC.begin(), ansC.begin(),
                      ansC.get_nnz(), tol);
}

template <typename MAT_A, typename MAT_B, typename MAT_C, typename T>
bool test_send_matadd(const size_t M, const size_t N, double tol) {
  monolish::matrix::COO<T> seedA = get_random_structure_matrix<T>(M, N);

  MAT_A A(seedA);
  MAT_B B(seedA);
  MAT_C C(seedA);

  monolish::matrix::Dense<T> AA(seedA);
  monolish::matrix::Dense<T> BB(seedA);
  monolish::matrix::Dense<T> CC(seedA);

  return test_send_matadd_core<T, MAT_A, MAT_B, MAT_C>(M, N, tol, AA, BB, CC, A,
                                                       B, C);
}

template <typename T, typename MAT_A, typename MAT_B, std::size_t K = 0,
          typename... Tp>
inline typename std::enable_if<K == sizeof...(Tp), bool>::type
test_send_matadd_view_core3(const size_t M, const size_t N, double tol,
                            monolish::matrix::Dense<T> &AA,
                            monolish::matrix::Dense<T> &BB,
                            monolish::matrix::Dense<T> &CC, MAT_A &A, MAT_B &B,
                            std::tuple<Tp...> &Cs) {
  return true;
}

template <typename T, typename MAT_A, typename MAT_B, std::size_t K = 0,
          typename... Tp>
    inline typename std::enable_if <
    K<sizeof...(Tp), bool>::type
    test_send_matadd_view_core3(const size_t M, const size_t N, double tol,
                                monolish::matrix::Dense<T> &AA,
                                monolish::matrix::Dense<T> &BB,
                                monolish::matrix::Dense<T> &CC, MAT_A &A,
                                MAT_B &B, std::tuple<Tp...> &Cs) {
  A = AA;
  B = BB;
  if (!test_send_matadd_core(M, N, tol, AA, BB, CC, A, B, std::get<K>(Cs))) {
    return false;
  }
  return test_send_matadd_view_core3<T, MAT_A, MAT_B, K + 1, Tp...>(
      M, N, tol, AA, BB, CC, A, B, Cs);
}

template <typename T, typename MAT_A, std::size_t J = 0, typename... Tp>
inline typename std::enable_if<J == sizeof...(Tp), bool>::type
test_send_matadd_view_core2(const size_t M, const size_t N, double tol,
                            monolish::matrix::Dense<T> &AA,
                            monolish::matrix::Dense<T> &BB,
                            monolish::matrix::Dense<T> &CC, MAT_A &A,
                            std::tuple<Tp...> &Bs, std::tuple<Tp...> &Cs) {
  return true;
}

template <typename T, typename MAT_A, std::size_t J = 0, typename... Tp>
    inline typename std::enable_if <
    J<sizeof...(Tp), bool>::type
    test_send_matadd_view_core2(const size_t M, const size_t N, double tol,
                                monolish::matrix::Dense<T> &AA,
                                monolish::matrix::Dense<T> &BB,
                                monolish::matrix::Dense<T> &CC, MAT_A &A,
                                std::tuple<Tp...> &Bs, std::tuple<Tp...> &Cs) {
  if (!test_send_matadd_view_core3(M, N, tol, AA, BB, CC, A, std::get<J>(Bs),
                                   Cs)) {
    return false;
  }
  return test_send_matadd_view_core2<T, MAT_A, J + 1, Tp...>(M, N, tol, AA, BB,
                                                             CC, A, Bs, Cs);
}

template <typename T, std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), bool>::type
test_send_matadd_view_core1(const size_t M, const size_t N, double tol,
                            monolish::matrix::Dense<T> &AA,
                            monolish::matrix::Dense<T> &BB,
                            monolish::matrix::Dense<T> &CC,
                            std::tuple<Tp...> &As, std::tuple<Tp...> &Bs,
                            std::tuple<Tp...> &Cs) {
  return true;
}

template <typename T, std::size_t I = 0, typename... Tp>
    inline typename std::enable_if <
    I<sizeof...(Tp), bool>::type test_send_matadd_view_core1(
        const size_t M, const size_t N, double tol,
        monolish::matrix::Dense<T> &AA, monolish::matrix::Dense<T> &BB,
        monolish::matrix::Dense<T> &CC, std::tuple<Tp...> &As,
        std::tuple<Tp...> &Bs, std::tuple<Tp...> &Cs) {
  if (!test_send_matadd_view_core2(M, N, tol, AA, BB, CC, std::get<I>(As), Bs,
                                   Cs)) {
    return false;
  }
  return test_send_matadd_view_core1<T, I + 1, Tp...>(M, N, tol, AA, BB, CC, As,
                                                      Bs, Cs);
}

template <typename T>
bool test_send_matadd_view(const size_t M, const size_t N, double tol) {
  monolish::matrix::COO<T> seedA = get_random_structure_matrix<T>(M, N);

  monolish::matrix::Dense<T> AA(seedA);
  monolish::matrix::Dense<T> BB(seedA);
  monolish::matrix::Dense<T> CC(seedA);

  using T1 = monolish::matrix::Dense<T>;
  using T2_ = monolish::vector<T>;
  using T2 = monolish::view_Dense<T2_, T>;
  using T3_ = monolish::matrix::Dense<T>;
  using T3 = monolish::view_Dense<T3_, T>;
  using T4_ = monolish::tensor::tensor_Dense<T>;
  using T4 = monolish::view_Dense<T4_, T>;
  T1 x1(M, N);
  T2_ x2_(2 * M * N, 0.0, 1.0);
  T2 x2(x2_, M / 2, M, N);
  T3_ x3_(2 * M * N, 1, 0.0, 1.0);
  T3 x3(x3_, M / 2, M, N);
  T4_ x4_({2 * M * N, 1, 1}, 0.0, 1.0);
  T4 x4(x4_, M / 2, M, N);

  T1 y1(M, N);
  T2_ y2_(2 * M * N, 0.0, 1.0);
  T2 y2(y2_, M / 2, M, N);
  T3_ y3_(2 * M * N, 1, 0.0, 1.0);
  T3 y3(y3_, M / 2, M, N);
  T4_ y4_({2 * M * N, 1, 1}, 0.0, 1.0);
  T4 y4(y4_, M / 2, M, N);

  T1 z1(M, N);
  T2_ z2_(2 * M * N, 0.0, 1.0);
  T2 z2(z2_, M / 2, M, N);
  T3_ z3_(2 * M * N, 1, 0.0, 1.0);
  T3 z3(z3_, M / 2, M, N);
  T4_ z4_({2 * M * N, 1, 1}, 0.0, 1.0);
  T4 z4(z4_, M / 2, M, N);

  auto As = std::make_tuple(x1, x2, x3, x4);
  auto Bs = std::make_tuple(y1, y2, y3, y4);
  auto Cs = std::make_tuple(z1, z2, z3, z4);

  return test_send_matadd_view_core1<T, 0, T1, T2, T3, T4>(M, N, tol, AA, BB,
                                                           CC, As, Bs, Cs);
}

template <typename MAT_A, typename MAT_B, typename MAT_C, typename T>
bool test_send_matadd_linearoperator(const size_t M, const size_t N,
                                     double tol) {
  monolish::matrix::COO<T> seedA = get_random_structure_matrix<T>(M, N);

  monolish::matrix::CRS<T> A1(seedA);
  monolish::matrix::CRS<T> B1(seedA);
  monolish::matrix::CRS<T> C1(seedA);

  monolish::matrix::Dense<T> AA(seedA);
  monolish::matrix::Dense<T> BB(seedA);
  monolish::matrix::Dense<T> CC(seedA);

  ans_matadd(AA, BB, CC);
  monolish::matrix::COO<T> ansC(CC);

  monolish::util::send(A1, B1, C1);
  MAT_A A(A1);
  MAT_B B(B1);
  MAT_C C(C1);
  monolish::blas::matadd(A, B, C);
  C.recv();

  monolish::matrix::COO<T> resultC(C);

  return ans_check<T>(__func__, A.type(), resultC.begin(), ansC.begin(),
                      ansC.get_nnz(), tol);
}

template <typename T, typename MAT_A, typename MAT_B, typename MAT_C>
bool test_matadd_core(const size_t M, const size_t N, double tol,
                      monolish::matrix::Dense<T> &AA,
                      monolish::matrix::Dense<T> &BB,
                      monolish::matrix::Dense<T> &CC, MAT_A &A, MAT_B &B,
                      MAT_C &C) {
  ans_matadd(AA, BB, CC);
  monolish::matrix::COO<T> ansC(CC);

  monolish::blas::matadd(A, B, C);

  monolish::matrix::COO<T> resultC(C);

  return ans_check<T>(__func__, A.type(), resultC.begin(), ansC.begin(),
                      ansC.get_nnz(), tol);
}

template <typename MAT_A, typename MAT_B, typename MAT_C, typename T>
bool test_matadd(const size_t M, const size_t N, double tol) {
  monolish::matrix::COO<T> seedA = get_random_structure_matrix<T>(M, N);

  MAT_A A(seedA);
  MAT_B B(seedA);
  MAT_C C(seedA);

  monolish::matrix::Dense<T> AA(seedA);
  monolish::matrix::Dense<T> BB(seedA);
  monolish::matrix::Dense<T> CC(seedA);

  return test_matadd_core<T, MAT_A, MAT_B, MAT_C>(M, N, tol, AA, BB, CC, A, B,
                                                  C);
}

template <typename T, typename MAT_A, typename MAT_B, std::size_t K = 0,
          typename... Tp>
inline typename std::enable_if<K == sizeof...(Tp), bool>::type
test_matadd_view_core3(const size_t M, const size_t N, double tol,
                       monolish::matrix::Dense<T> &AA,
                       monolish::matrix::Dense<T> &BB,
                       monolish::matrix::Dense<T> &CC, MAT_A &A, MAT_B &B,
                       std::tuple<Tp...> &Cs) {
  return true;
}

template <typename T, typename MAT_A, typename MAT_B, std::size_t K = 0,
          typename... Tp>
    inline typename std::enable_if <
    K<sizeof...(Tp), bool>::type
    test_matadd_view_core3(const size_t M, const size_t N, double tol,
                           monolish::matrix::Dense<T> &AA,
                           monolish::matrix::Dense<T> &BB,
                           monolish::matrix::Dense<T> &CC, MAT_A &A, MAT_B &B,
                           std::tuple<Tp...> &Cs) {
  A = AA;
  B = BB;
  if (!test_matadd_core(M, N, tol, AA, BB, CC, A, B, std::get<K>(Cs))) {
    return false;
  }
  return test_matadd_view_core3<T, MAT_A, MAT_B, K + 1, Tp...>(
      M, N, tol, AA, BB, CC, A, B, Cs);
}

template <typename T, typename MAT_A, std::size_t J = 0, typename... Tp>
inline typename std::enable_if<J == sizeof...(Tp), bool>::type
test_matadd_view_core2(const size_t M, const size_t N, double tol,
                       monolish::matrix::Dense<T> &AA,
                       monolish::matrix::Dense<T> &BB,
                       monolish::matrix::Dense<T> &CC, MAT_A &A,
                       std::tuple<Tp...> &Bs, std::tuple<Tp...> &Cs) {
  return true;
}

template <typename T, typename MAT_A, std::size_t J = 0, typename... Tp>
    inline typename std::enable_if <
    J<sizeof...(Tp), bool>::type
    test_matadd_view_core2(const size_t M, const size_t N, double tol,
                           monolish::matrix::Dense<T> &AA,
                           monolish::matrix::Dense<T> &BB,
                           monolish::matrix::Dense<T> &CC, MAT_A &A,
                           std::tuple<Tp...> &Bs, std::tuple<Tp...> &Cs) {
  if (!test_matadd_view_core3(M, N, tol, AA, BB, CC, A, std::get<J>(Bs), Cs)) {
    return false;
  }
  return test_matadd_view_core2<T, MAT_A, J + 1, Tp...>(M, N, tol, AA, BB, CC,
                                                        A, Bs, Cs);
}

template <typename T, std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), bool>::type
test_matadd_view_core1(const size_t M, const size_t N, double tol,
                       monolish::matrix::Dense<T> &AA,
                       monolish::matrix::Dense<T> &BB,
                       monolish::matrix::Dense<T> &CC, std::tuple<Tp...> &As,
                       std::tuple<Tp...> &Bs, std::tuple<Tp...> &Cs) {
  return true;
}

template <typename T, std::size_t I = 0, typename... Tp>
    inline typename std::enable_if <
    I<sizeof...(Tp), bool>::type test_matadd_view_core1(
        const size_t M, const size_t N, double tol,
        monolish::matrix::Dense<T> &AA, monolish::matrix::Dense<T> &BB,
        monolish::matrix::Dense<T> &CC, std::tuple<Tp...> &As,
        std::tuple<Tp...> &Bs, std::tuple<Tp...> &Cs) {
  if (!test_matadd_view_core2(M, N, tol, AA, BB, CC, std::get<I>(As), Bs, Cs)) {
    return false;
  }
  return test_matadd_view_core1<T, I + 1, Tp...>(M, N, tol, AA, BB, CC, As, Bs,
                                                 Cs);
}

template <typename T>
bool test_matadd_view(const size_t M, const size_t N, double tol) {
  monolish::matrix::COO<T> seedA = get_random_structure_matrix<T>(M, N);

  monolish::matrix::Dense<T> AA(seedA);
  monolish::matrix::Dense<T> BB(seedA);
  monolish::matrix::Dense<T> CC(seedA);

  using T1 = monolish::matrix::Dense<T>;
  using T2_ = monolish::vector<T>;
  using T2 = monolish::view_Dense<T2_, T>;
  using T3_ = monolish::matrix::Dense<T>;
  using T3 = monolish::view_Dense<T3_, T>;
  using T4_ = monolish::tensor::tensor_Dense<T>;
  using T4 = monolish::view_Dense<T4_, T>;
  T1 x1(M, N);
  T2_ x2_(2 * M * N, 0.0, 1.0);
  T2 x2(x2_, M / 2, M, N);
  T3_ x3_(2 * M * N, 1, 0.0, 1.0);
  T3 x3(x3_, M / 2, M, N);
  T4_ x4_({2 * M * N, 1, 1}, 0.0, 1.0);
  T4 x4(x4_, M / 2, M, N);

  T1 y1(M, N);
  T2_ y2_(2 * M * N, 0.0, 1.0);
  T2 y2(y2_, M / 2, M, N);
  T3_ y3_(2 * M * N, 1, 0.0, 1.0);
  T3 y3(y3_, M / 2, M, N);
  T4_ y4_({2 * M * N, 1, 1}, 0.0, 1.0);
  T4 y4(y4_, M / 2, M, N);

  T1 z1(M, N);
  T2_ z2_(2 * M * N, 0.0, 1.0);
  T2 z2(z2_, M / 2, M, N);
  T3_ z3_(2 * M * N, 1, 0.0, 1.0);
  T3 z3(z3_, M / 2, M, N);
  T4_ z4_({2 * M * N, 1, 1}, 0.0, 1.0);
  T4 z4(z4_, M / 2, M, N);

  auto As = std::make_tuple(x1, x2, x3, x4);
  auto Bs = std::make_tuple(y1, y2, y3, y4);
  auto Cs = std::make_tuple(z1, z2, z3, z4);

  return test_matadd_view_core1<T, 0, T1, T2, T3, T4>(M, N, tol, AA, BB, CC, As,
                                                      Bs, Cs);
}
