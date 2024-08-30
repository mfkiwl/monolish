#!/bin/bash
echo "// This code is generated by gen_copy.sh
#include \"dense_copy.hpp\"
#include \"crs_copy.hpp\"
#include \"linearOperator_copy.hpp\"

namespace monolish::blas {
"

# copy dense
for prec in double float; do
  for arg1 in matrix::Dense\<$prec\> view_Dense\<vector\<$prec\>,$prec\> view_Dense\<matrix::Dense\<$prec\>,$prec\> view_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
    for arg2 in matrix::Dense\<$prec\> view_Dense\<vector\<$prec\>,$prec\> view_Dense\<matrix::Dense\<$prec\>,$prec\> view_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
      echo "void copy(const $arg1 &A, $arg2 &C){ copy_core(A, C); }"
    done
  done
done

echo ""

# copy crs
for prec in double float; do
  echo "void copy(const matrix::CRS<$prec> &A, matrix::CRS<$prec> &C){ copy_core(A, C); }"
done

echo ""

# copy linearOperator
for prec in double float; do
  echo "void copy(const matrix::LinearOperator<$prec> &A, matrix::LinearOperator<$prec> &C){ copy_core(A, C); }"
done

echo "}"