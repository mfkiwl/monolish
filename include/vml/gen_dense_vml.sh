#!/bin/bash
echo "//this code is generated by gen_dense_vml.sh
#pragma once

#include \"../common/monolish_common.hpp\"

namespace monolish {
/**
 * @brief
 * Vector and Matrix element-wise math library
 */
namespace vml {
"
echo "
/**
 * @addtogroup Dense_VML
 * @{
 */
"

## Dense matrix-matrix arithmetic
detail=(addition subtract multiplication division)
func=(add sub mul div)
for i in ${!detail[@]}; do
echo "
/**
 * \defgroup vml_dns${func[$i]} monolish::vml::${func[$i]}
 * @brief element by element ${detail[$i]} Dense matrix A and Dense matrix B.
 * @{
 */
/**
 * @brief element by element ${detail[$i]} Dense matrix A and Dense matrix B.
 * @param A monolish Dense Matrix (size M x N)
 * @param B monolish Dense Matrix (size M x N)
 * @param C monolish Dense Matrix (size M x N)
 * @note
 * - # of computation: M*N
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
*/ "
for prec in double float; do
  echo "void ${func[$i]}(const matrix::Dense<$prec> &A, const matrix::Dense<$prec> &B, matrix::Dense<$prec> &C);"
done
echo "/**@}*/"
done

echo ""
################################################################

## Dense matrix-scalar arithmetic
detail=(addition subtract multiplication division)
func=(add sub mul div)
for i in ${!detail[@]}; do
echo "
/**
 * \defgroup vml_sdns${func[$i]} monolish::vml::${func[$i]}
 * @brief element by element ${detail[$i]} scalar alpha and Dense matrix A.
 * @{
 */
/**
 * @brief element by element ${detail[$i]} scalar alpha and Dense matrix A.
 * @param A monolish Dense Matrix (size M x N)
 * @param alpha scalar value
 * @param C monolish Dense Matrix (size M x N)
 * @note
 * - # of computation: M*N
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
*/ "
for prec in double float; do
  echo "void ${func[$i]}(const matrix::Dense<$prec> &A, const $prec alpha, matrix::Dense<$prec> &C);"
done
echo "/**@}*/"
done

echo ""
#############################################

## matrix-matrix pow
echo "
/**
 * \defgroup vml_dnspow monolish::vml::pow
 *@brief power to Dense matrix elements (C[0:N] = pow(A[0:N], B[0:N]))
 * @{
 */
/**
 *@brief power to Dense matrix elements (C[0:N] = pow(A[0:N], B[0:N]))
 * @param A monolish Dense Matrix (size M x N)
 * @param B monolish Dense Matrix (size M x N)
 * @param C monolish Dense Matrix (size M x N)
 * @note
 * - # of computation: M*N
 * - Multi-threading: true
 * - GPU acceleration: true
*/ "
for prec in double float; do
  echo "void pow(const matrix::Dense<$prec> &A, const matrix::Dense<$prec> &B, matrix::Dense<$prec> &C);"
done
echo "/**@}*/"
 
echo "
/**
 * \defgroup vml_sdnspow monolish::vml::pow
 * @brief power to Dense matrix elements by scalar value (C[0:N] = pow(A[0:N], alpha))
 * @{
 */
/**
 * @brief power to Dense matrix elements by scalar value (C[0:N] = pow(A[0:N], alpha))
 * @param A monolish Dense Matrix (size M x N)
 * @param alpha scalar value
 * @param C monolish Dense Matrix (size M x N)
 * @note
 * - # of computation: M*N
 * - Multi-threading: true
 * - GPU acceleration: true
*/ "
for prec in double float; do
  echo "void pow(const matrix::Dense<$prec> &A, const $prec alpha, matrix::Dense<$prec> &C);"
done
echo "/**@}*/"

echo ""
#############################################
## 2arg math
math=(sin sqrt sinh asin asinh tan tanh atan atanh ceil floor sign)
for math in ${math[@]}; do
echo "
/**
 * \defgroup vml_dns$math monolish::vml::$math
 * @brief $math to Dense matrix elements (C[0:nnz] = $math(A[0:nnz]))
 * @{
 */
/**
 * @brief $math to Dense matrix elements (C[0:nnz] = $math(A[0:nnz]))
 * @param A monolish Dense matrix (size M x N)
 * @param C monolish Dense matrix (size M x N)
 * @note
 * - # of computation: M*N
 * - Multi-threading: true
 * - GPU acceleration: true
*/ "
for prec in double float; do
  echo "void $math(const matrix::Dense<$prec> &A, matrix::Dense<$prec> &C);"
done
echo "/**@}*/"
done

echo ""
#############################################

## matrix-matrix max min
detail=(greatest smallest)
func=(max min)
for i in ${!detail[@]}; do
echo "
/**
* \defgroup vml_dnsdns${func[$i]} monolish::vml::${func[$i]}
 * @brief Create a new Dense matrix with ${detail[$i]} elements of two matrices (C[0:nnz] = ${func[$i]}(A[0:nnz], B[0:nnz]))
 * @{
 */
/**
 * @brief Create a new Dense matrix with ${detail[$i]} elements of two matrices (C[0:nnz] = ${func[$i]}(A[0:nnz], B[0:nnz]))
 * @param A monolish Dense matrix (size M x N)
 * @param B monolish Dense matrix (size M x N)
 * @param C monolish Dense matrix (size M x N)
 * @note
 * - # of computation: M*N
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
*/ "
for prec in double float; do
  echo "void ${func[$i]}(const matrix::Dense<$prec> &A, const matrix::Dense<$prec> &B, matrix::Dense<$prec> &C);"
done
echo "/**@}*/"
done

echo ""

## matrix-scalar max min
detail=(greatest smallest)
func=(max min)
for i in ${!detail[@]}; do
echo "
/**
* \defgroup vml_sdns${func[$i]} monolish::vml::${func[$i]}
 * @brief Create a new Dense matrix with ${detail[$i]} elements of Dense matrix or scalar (C[0:nnz] = ${func[$i]}(A[0:nnz], alpha))
 * @{
 */
/**
 * @brief Create a new Dense matrix with ${detail[$i]} elements of Dense matrix or scalar (C[0:nnz] = ${func[$i]}(A[0:nnz], alpha))
 * @param A monolish Dense matrix (size M x N)
 * @param alpha scalar value
 * @param C monolish Dense matrix (size M x N)
 * @note
 * - # of computation: M*N
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
*/ "
for prec in double float; do
  echo "void ${func[$i]}(const matrix::Dense<$prec> &A, const $prec alpha, matrix::Dense<$prec> &C);"
done
echo "/**@}*/"
done

echo ""

## Dense matrix max min
detail=(greatest smallest)
func=(max min)
for i in ${!detail[@]}; do
echo "
/**
* \defgroup vml_dns${func[$i]} monolish::vml::${func[$i]}
 * @brief Finds the ${detail[$i]} element in Dense matrix (${func[$i]}(C[0:nnz]))
 * @{
 */
/**
 * @brief Finds the ${detail[$i]} element in Dense matrix (${func[$i]}(C[0:nnz]))
 * @param C monolish Dense matrix (size M x N)
 * @return ${detail[$i]} value
 * @note
 * - # of computation: M*N
 * - Multi-threading: true
 * - GPU acceleration: true
*/ "
for prec in double float; do
    echo "[[nodiscard]] $prec ${func[$i]}(const matrix::Dense<$prec> &C);"
done
echo "/**@}*/"
done

echo ""
#############################################

## Dense matrix alo
echo "
/**
* \defgroup vml_sdnsalo monolish::vml::alo
 * @brief Asymmetric linear operation to Dense matrix elements (C[0:nnz] = alpha max(A[0:nnz], 0) + beta min(A[0:nnz], 0))
 * @{
 */
/**
 * @brief Asymmetric linear operation to Dense matrix elements (C[0:nnz] = alpha max(A[0:nnz], 0) + beta min(A[0:nnz], 0))
 * @param A monolish Dense matrix (size M x N)
 * @param alpha linear coefficient in positive range
 * @param beta linear coefficient in negative range
 * @param C monolish Dense matrix (size M x N)
 * @note
 * - # of computation: M*N
 * - Multi-threading: true
 * - GPU acceleration: true
*/ "
for prec in double float; do
  echo "void alo(const matrix::Dense<$prec> &A, const $prec alpha, const $prec beta, matrix::Dense<$prec> &C);"
done
echo "/**@}*/"

echo ""
#############################################

## reciprocal
echo "
/**
* \defgroup vml_dnsreciprocal monolish::vml::reciprocal
 * @brief Compute reciprocal to Dense matrix elements (C[0:nnz] = 1 / A[0:nnz])
 * @{
 */
/**
 * @brief Compute reciprocal to Dense matrix elements (C[0:nnz] = 1 / A[0:nnz])
 * @param A monolish Dense matrix (size M x N)
 * @param C monolish Dense matrix (size M x N)
 * @note
 * - # of computation: M*N
 * - Multi-threading: true
 * - GPU acceleration: true
*/ "
for prec in double float; do
  echo "void reciprocal(const matrix::Dense<$prec> &A, matrix::Dense<$prec> &C);"
done

echo "/**@}*/"
echo "/**@}*/"
echo "}"
echo "}"
