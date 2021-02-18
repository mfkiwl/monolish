#!/bin/bash
echo "//this code is generated by gen_matvec_blas.sh
#include \"../../../../include/monolish_blas.hpp\"
#include \"../../../internal/monolish_internal.hpp\"
#include \"crs_matvec.hpp\"
#include \"dense_matvec.hpp\"
#include \"linearoperator_matvec.hpp\"

namespace monolish {
namespace blas {
"

## matvec Dense
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    for arg2 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      if [ $prec = "double" ]
      then
        echo "void matvec(const matrix::Dense<$prec> &A, const $arg1 &x, $arg2 &y){Dmatvec_core(A, x, y);}"
      else
        echo "void matvec(const matrix::Dense<$prec> &A, const $arg1 &x, $arg2 &y){Smatvec_core(A, x, y);}"
      fi
    done
  done
done

echo ""

## matvec CRS
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    for arg2 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      if [ $prec = "double" ]
      then
        echo "void matvec(const matrix::CRS<$prec> &A, const $arg1 &x, $arg2 &y){Dmatvec_core(A, x, y);}"
      else
        echo "void matvec(const matrix::CRS<$prec> &A, const $arg1 &x, $arg2 &y){Smatvec_core(A, x, y);}"
      fi
    done
  done
done

echo ""

## matvec LinearOperator
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    for arg2 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      echo "void matvec(const matrix::LinearOperator<$prec> &A, const $arg1 &x, $arg2 &y){matvec_core(A, x, y);}"
    done
  done
done

## rmatvec LinearOperator
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    for arg2 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      echo "void rmatvec(const matrix::LinearOperator<$prec> &A, const $arg1 &x, $arg2 &y){rmatvec_core(A, x, y);}"
    done
  done
done

echo "
} // namespace blas
} // namespace monolish"