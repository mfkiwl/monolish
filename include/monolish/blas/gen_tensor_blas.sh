#!/bin/bash
echo "//this code is generated by gen_tensor_blas.sh
#pragma once
#include \"../common/monolish_common.hpp\"

namespace monolish {
/**
* @brief
* Basic Linear Algebra Subprograms for Dense Matrix, Sparse Matrix, Vector and
* Scalar
*/
namespace blas {
"

echo "
/**
 * @addtogroup BLASLV3
 * @{
 */
"

## copy tensor_Dense
echo "
/**
 * \defgroup tens_copy_Dense monolish::blas::copy (tensor_Dense)
 * @brief tensor_Dense tensor copy (C=A)
 * @{
 */
 /**
 * @brief tensor_Dense tensor copy (C=A)
 * @param A monolish tensor_Dense tensor
 * @param C monolish tensor_Dense tensor
 * @note
 * - # of computation: size
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
 */ "
for prec in double float; do
  for arg1 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
    for arg2 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
      echo "void copy(const $arg1 &A, $arg2 &C);"
    done
  done
done

echo "/**@}*/"

##############################################

#tscal tensor_Dense
echo "
/**
 * \defgroup tscal_dense monolish::blas::tscal (tensor_Dense)
 * @brief tensor_Dense tensor scal: A = alpha * A
 * @{
 */
/**
 * @brief tensor_Dense tensor scal: A = alpha * A
 * @param alpha scalar value
 * @param A Dense tensor
 * @note
 * - # of computation: size
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
*/ "
for prec in double float; do
  for arg1 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
    echo "void tscal(const $prec alpha, $arg1 &A);"
  done
done

echo "/**@}*/"

##############################################
# times scalar (almost same as tscal)

# times scalar tensor_Dense
echo "
/**
 * \defgroup times monolish::blas::times
 * @brief element by element multiplication
 * @{
 */
/**
 * @brief tensor_Dense tensor times: C = alpha * A
 * @param alpha scalar value
 * @param A tensor_Dense tensor
 * @param C tensor_Dense tensor
 * @note
 * - # of computation: size
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
*/ "
for prec in double float; do
  for arg1 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
    for arg2 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
      echo "void times(const $prec alpha, const $arg1 &A, $arg2 &C);"
    done
  done
done
echo "/**@}*/"

##############################################
# adds scalar

# adds scalar tensor_Dense
echo "
/**
 * \defgroup adds monolish::blas::adds
 * @brief element by element multiplication
 * @{
 */
/**
 * @brief tensor_Dense tensor adds: C = alpha + A
 * @param alpha scalar value
 * @param A tensor_Dense tensor
 * @param C tensor_Dense tensor
 * @note
 * - # of computation: size
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
*/ "
for prec in double float; do
  for arg1 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
    for arg2 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
      echo "void adds(const $prec alpha, const $arg1 &A, $arg2 &C);"
    done
  done
done
echo "/**@}*/"

##############################################

#tensadd tensor_Dense
echo "
/**
 * \defgroup madd_dense monolish::blas::tensadd (tensor_Dense)
 * @brief tensor_Dense tensor addition: C = A + B
 * @{
 */
/**
 * @brief Dense tensor addition: C = A + B
 * @param A tensor_Dense tensor
 * @param B tensor_Dense tensor
 * @param C tensor_Dense tensor
 * @note
 * - # of computation: size
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
*/ "
for prec in double float; do
  for arg1 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
    for arg2 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
      for arg3 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
        echo "void tensadd(const $arg1 &A, const $arg2 &B, $arg3 &C);"
      done
    done
  done
done
echo "/**@}*/"

echo ""

#tenssub tensor_Dense
echo "
/**
 * \defgroup msub_dense monolish::blas::tenssub (tensor_Dense)
 * @brief tensor_Dense tensor subtract: C = A - B
 * @{
 */
/**
 * @brief Dense tensor subtract: C = A - B
 * @param A tensor_Dense tensor
 * @param B tensor_Dense tensor
 * @param C tensor_Dense tensor
 * @note
 * - # of computation: ?
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
*/ "
for prec in double float; do
  for arg1 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
    for arg2 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
      for arg3 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
        echo "void tenssub(const $arg1 &A, const $arg2 &B, $arg3 &C);"
      done
    done
  done
done
echo "/**@}*/"

echo ""
#################################

#tensmul tensor_Dense
echo "
/**
 * \defgroup mm_dense monolish::blas::tensmul (tensor_Dense, tensor_Dense, tensor_Dense)
 * @brief tensor_Dense tensor multiplication: C = AB
 * @{
 */
/**
 * @brief tensor_Dense tensor multiplication: C = AB
 * @param A tensor_Dense tensor
 * @param B tensor_Dense tensor
 * @param C tensor_Dense tensor
 * @note
 * - # of computation: ?
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
*/ "
for prec in double float; do
  for arg1 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
    for arg2 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
      for arg3 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
        echo "void tensmul(const $arg1 &A, const $arg2 &B, $arg3 &C);"
      done
    done
  done
done
echo "/**@}*/"

echo "
/**
 * \defgroup mm_dense monolish::blas::tensmul (Float, tensor_Dense, tensor_Dense, Float, tensor_Dense)
 * @brief tensor_Dense tensor multiplication: C = aAB+bC
 * @{
 */
/**
 * @brief tensor_Dense tensor multiplication: C = aAB+bC
 * @param a Float
 * @param A tensor_Dense tensor
 * @param B tensor_Dense tensor
 * @param b Float
 * @param C tensor_Dense tensor
 * @note
 * - # of computation: ?
 * - Multi-threading: true
 * - GPU acceleration: true
 *    - # of data transfer: 0
*/ "
for prec in double float; do
  for arg1 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
    for arg2 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
      for arg3 in tensor::tensor_Dense\<$prec\> view_tensor_Dense\<vector\<$prec\>,$prec\> view_tensor_Dense\<matrix::Dense\<$prec\>,$prec\> view_tensor_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
        echo "void tensmul(const $prec &a, const $arg1 &A, const $arg2 &B, const $prec &b, $arg3 &C);"
      done
    done
  done
done
echo "/**@}*/"

echo "}"
echo "}"