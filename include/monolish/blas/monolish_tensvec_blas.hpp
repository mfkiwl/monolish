// this code is generated by gen_tensvec_blas.sh
#pragma once
#include "../common/monolish_common.hpp"

namespace monolish {
/**
 * @brief
 * Basic Linear Algebra Subprograms for tensor_Dense Tensor, tensor_Dense
 * Matrix, Sparse Matrix, Vector and Scalar
 */
namespace blas {

/**
 * @addtogroup BLASLV2
 * @{
 */

/**
 * \defgroup times monolish::blas::times
 * @brief element by element multiplication
 * @{
 */
/**
 * @brief Row-wise tensor_Dense tensor and vector times:
 * C[i][j] = A[i][j] * x[j]
 * @param A tensor_Dense tensor (size M x N)
 * @param x monolish vector (size M)
 * @param C tensor_Dense tensor (size M x N)
 * @note
 * - # of computation: MN
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
 */
void times_row(const tensor::tensor_Dense<double> &A, const vector<double> &x,
               tensor::tensor_Dense<double> &C);
void times_row(const tensor::tensor_Dense<double> &A,
               const view1D<vector<double>, double> &x,
               tensor::tensor_Dense<double> &C);
void times_row(const tensor::tensor_Dense<double> &A,
               const view1D<tensor::tensor_Dense<double>, double> &x,
               tensor::tensor_Dense<double> &C);
void times_row(const tensor::tensor_Dense<float> &A, const vector<float> &x,
               tensor::tensor_Dense<float> &C);
void times_row(const tensor::tensor_Dense<float> &A,
               const view1D<vector<float>, float> &x,
               tensor::tensor_Dense<float> &C);
void times_row(const tensor::tensor_Dense<float> &A,
               const view1D<tensor::tensor_Dense<float>, float> &x,
               tensor::tensor_Dense<float> &C);
/**@}*/

/**
 * \defgroup times monolish::blas::times
 * @brief element by element multiplication
 * @{
 */
/**
 * @brief Specified row of dense tensor and vector times:
 * C[num][j] = A[num][j] * x[j]
 * @param A tensor_Dense tensor (size M x N)
 * @param num row number
 * @param x monolish vector (size M)
 * @param C tensor_Dense tensor (size M x N)
 * @note
 * - # of computation: N
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
 */
void times_row(const tensor::tensor_Dense<double> &A, const size_t num,
               const vector<double> &x, tensor::tensor_Dense<double> &C);
void times_row(const tensor::tensor_Dense<double> &A, const size_t num,
               const view1D<vector<double>, double> &x,
               tensor::tensor_Dense<double> &C);
void times_row(const tensor::tensor_Dense<double> &A, const size_t num,
               const view1D<tensor::tensor_Dense<double>, double> &x,
               tensor::tensor_Dense<double> &C);
void times_row(const tensor::tensor_Dense<float> &A, const size_t num,
               const vector<float> &x, tensor::tensor_Dense<float> &C);
void times_row(const tensor::tensor_Dense<float> &A, const size_t num,
               const view1D<vector<float>, float> &x,
               tensor::tensor_Dense<float> &C);
void times_row(const tensor::tensor_Dense<float> &A, const size_t num,
               const view1D<tensor::tensor_Dense<float>, float> &x,
               tensor::tensor_Dense<float> &C);
/**@}*/

/**
 * \defgroup times monolish::blas::times
 * @brief element by element multiplication
 * @{
 */
/**
 * @brief Column-wise tensor_Dense tensor and vector times:
 * C[i][j] = A[i][j] * x[i]
 * @param A tensor_Dense tensor (size M x N)
 * @param x monolish vector (size M)
 * @param C tensor_Dense tensor (size M x N)
 * @note
 * - # of computation: MN
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
 */
void times_col(const tensor::tensor_Dense<double> &A, const vector<double> &x,
               tensor::tensor_Dense<double> &C);
void times_col(const tensor::tensor_Dense<double> &A,
               const view1D<vector<double>, double> &x,
               tensor::tensor_Dense<double> &C);
void times_col(const tensor::tensor_Dense<double> &A,
               const view1D<tensor::tensor_Dense<double>, double> &x,
               tensor::tensor_Dense<double> &C);
void times_col(const tensor::tensor_Dense<float> &A, const vector<float> &x,
               tensor::tensor_Dense<float> &C);
void times_col(const tensor::tensor_Dense<float> &A,
               const view1D<vector<float>, float> &x,
               tensor::tensor_Dense<float> &C);
void times_col(const tensor::tensor_Dense<float> &A,
               const view1D<tensor::tensor_Dense<float>, float> &x,
               tensor::tensor_Dense<float> &C);
/**@}*/

/**
 * \defgroup times monolish::blas::times
 * @brief element by element multiplication
 * @{
 */
/**
 * @brief Specified col of dense tensor and vector times:
 * C[i][num] = A[i][num] * x[j]
 * @param A tensor_Dense tensor (size M x N)
 * @param num column number
 * @param x monolish vector (size M)
 * @param C tensor_Dense tensor (size M x N)
 * @note
 * - # of computation: M
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
 */
void times_col(const tensor::tensor_Dense<double> &A, const size_t num,
               const vector<double> &x, tensor::tensor_Dense<double> &C);
void times_col(const tensor::tensor_Dense<double> &A, const size_t num,
               const view1D<vector<double>, double> &x,
               tensor::tensor_Dense<double> &C);
void times_col(const tensor::tensor_Dense<double> &A, const size_t num,
               const view1D<tensor::tensor_Dense<double>, double> &x,
               tensor::tensor_Dense<double> &C);
void times_col(const tensor::tensor_Dense<float> &A, const size_t num,
               const vector<float> &x, tensor::tensor_Dense<float> &C);
void times_col(const tensor::tensor_Dense<float> &A, const size_t num,
               const view1D<vector<float>, float> &x,
               tensor::tensor_Dense<float> &C);
void times_col(const tensor::tensor_Dense<float> &A, const size_t num,
               const view1D<tensor::tensor_Dense<float>, float> &x,
               tensor::tensor_Dense<float> &C);
/**@}*/

/**
 * \defgroup tensvec_dense monolish::blas::tensvec (tensor_Dense)
 * @brief tensor_Dense tensor and vector multiplication: y = Ax
 * @{
 */
/**
 * @brief tensor_Dense tensor and vector multiplication: y = Ax
 * @param A tensor_Dense tensor (size M x N)
 * @param x monolish vector (size M)
 * @param y tensor_Dense tensor (size M)
 * @note
 * - # of computation: MN
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
 */
void tensvec(const tensor::tensor_Dense<double> &A, const vector<double> &x,
             tensor::tensor_Dense<double> &y);
void tensvec(const tensor::tensor_Dense<double> &A,
             const view1D<vector<double>, double> &x,
             tensor::tensor_Dense<double> &y);
void tensvec(const tensor::tensor_Dense<double> &A,
             const view1D<tensor::tensor_Dense<double>, double> &x,
             tensor::tensor_Dense<double> &y);
void tensvec(const tensor::tensor_Dense<float> &A, const vector<float> &x,
             tensor::tensor_Dense<float> &y);
void tensvec(const tensor::tensor_Dense<float> &A,
             const view1D<vector<float>, float> &x,
             tensor::tensor_Dense<float> &y);
void tensvec(const tensor::tensor_Dense<float> &A,
             const view1D<tensor::tensor_Dense<float>, float> &x,
             tensor::tensor_Dense<float> &y);
/**@}*/

/**
 * \defgroup tensvec_dense_N monolish::blas::tensvec_N (tensor_Dense)
 * @brief tensor_Dense tensor and vector multiplication: y = A^N x
 * @{
 */
/**
 * @brief tensor_Dense tensor and vector multiplication: y = A^N x
 * @param A tensor_Dense tensor (size M x N)
 * @param x monolish vector (size M)
 * @param y tensor_Dense tensor (size M)
 * @note
 * - # of computation: MN
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
 */
void tensvec_N(const tensor::tensor_Dense<double> &A, const vector<double> &x,
               tensor::tensor_Dense<double> &y);
void tensvec_N(const tensor::tensor_Dense<double> &A,
               const view1D<vector<double>, double> &x,
               tensor::tensor_Dense<double> &y);
void tensvec_N(const tensor::tensor_Dense<double> &A,
               const view1D<tensor::tensor_Dense<double>, double> &x,
               tensor::tensor_Dense<double> &y);
void tensvec_N(const tensor::tensor_Dense<float> &A, const vector<float> &x,
               tensor::tensor_Dense<float> &y);
void tensvec_N(const tensor::tensor_Dense<float> &A,
               const view1D<vector<float>, float> &x,
               tensor::tensor_Dense<float> &y);
void tensvec_N(const tensor::tensor_Dense<float> &A,
               const view1D<tensor::tensor_Dense<float>, float> &x,
               tensor::tensor_Dense<float> &y);
/**@}*/

/**
 * \defgroup tensvec_dense_T monolish::blas::tensvec_T (tensor_Dense)
 * @brief tensor_Dense tensor and vector multiplication: y = A^T x
 * @{
 */
/**
 * @brief tensor_Dense tensor and vector multiplication: y = A^T x
 * @param A tensor_Dense tensor (size M x N)
 * @param x monolish vector (size M)
 * @param y tensor_Dense tensor (size M)
 * @note
 * - # of computation: MN
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
 */
void tensvec_T(const tensor::tensor_Dense<double> &A, const vector<double> &x,
               tensor::tensor_Dense<double> &y);
void tensvec_T(const tensor::tensor_Dense<double> &A,
               const view1D<vector<double>, double> &x,
               tensor::tensor_Dense<double> &y);
void tensvec_T(const tensor::tensor_Dense<double> &A,
               const view1D<tensor::tensor_Dense<double>, double> &x,
               tensor::tensor_Dense<double> &y);
void tensvec_T(const tensor::tensor_Dense<float> &A, const vector<float> &x,
               tensor::tensor_Dense<float> &y);
void tensvec_T(const tensor::tensor_Dense<float> &A,
               const view1D<vector<float>, float> &x,
               tensor::tensor_Dense<float> &y);
void tensvec_T(const tensor::tensor_Dense<float> &A,
               const view1D<tensor::tensor_Dense<float>, float> &x,
               tensor::tensor_Dense<float> &y);
/**@}*/
/**@}*/
/**@}*/
} // namespace blas
} // namespace monolish
