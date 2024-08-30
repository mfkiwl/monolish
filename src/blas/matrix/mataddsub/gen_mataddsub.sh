#!/bin/bash
echo "// This code is generated by gen_mataddsub.sh
#include \"dense_mataddsub.hpp\"
#include \"crs_mataddsub.hpp\"
#include \"linearoperator_mataddsub.hpp\"

namespace monolish::blas {
"

# matadd dense
for prec in double float; do
  for arg1 in matrix::Dense\<$prec\> view_Dense\<vector\<$prec\>,$prec\> view_Dense\<matrix::Dense\<$prec\>,$prec\> view_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
    for arg2 in matrix::Dense\<$prec\> view_Dense\<vector\<$prec\>,$prec\> view_Dense\<matrix::Dense\<$prec\>,$prec\> view_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
      for arg3 in matrix::Dense\<$prec\> view_Dense\<vector\<$prec\>,$prec\> view_Dense\<matrix::Dense\<$prec\>,$prec\> view_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
        echo "void matadd(const $arg1 &A, const $arg2 &B, $arg3 &C) { matadd_core(A, B, C); }"
      done
    done
  done
done

echo ""

# matadd crs
for prec in double float; do
  echo "void matadd(const matrix::CRS<$prec> &A, const matrix::CRS<$prec> &B, matrix::CRS<$prec> &C) { matadd_core(A, B, C); }"
done

echo ""

# matadd linearoperator
for prec in double float; do
  echo "void matadd(const matrix::LinearOperator<$prec> &A, const matrix::LinearOperator<$prec> &B, matrix::LinearOperator<$prec> &C) { matadd_core(A, B, C); }"
done

echo ""

# matsub dense
for prec in double float; do
  for arg1 in matrix::Dense\<$prec\> view_Dense\<vector\<$prec\>,$prec\> view_Dense\<matrix::Dense\<$prec\>,$prec\> view_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
    for arg2 in matrix::Dense\<$prec\> view_Dense\<vector\<$prec\>,$prec\> view_Dense\<matrix::Dense\<$prec\>,$prec\> view_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
      for arg3 in matrix::Dense\<$prec\> view_Dense\<vector\<$prec\>,$prec\> view_Dense\<matrix::Dense\<$prec\>,$prec\> view_Dense\<tensor::tensor_Dense\<$prec\>,$prec\>; do
        echo "void matsub(const $arg1 &A, const $arg2 &B, $arg3 &C) { matsub_core(A, B, C); }"
      done
    done
  done
done

echo ""

# matsub crs
for prec in double float; do
  echo "void matsub(const matrix::CRS<$prec> &A, const matrix::CRS<$prec> &B, matrix::CRS<$prec> &C) { matsub_core(A, B, C); }"
done

echo ""

# matsub linearoperator
for prec in double float; do
  echo "void matsub(const matrix::LinearOperator<$prec> &A, const matrix::LinearOperator<$prec> &B, matrix::LinearOperator<$prec> &C) { matsub_core(A, B, C); }"
done

echo "}"