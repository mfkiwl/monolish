#!/bin/bash
echo "// This code is generated by gen_vector_blas.sh
#include \"../../../include/monolish_blas.hpp\"
#include \"../../internal/monolish_internal.hpp\"
#include \"asum.hpp\"
#include \"axpy.hpp\"
#include \"axpyz.hpp\"
#include \"copy.hpp\"
#include \"dot.hpp\"
#include \"nrm1.hpp\"
#include \"nrm2.hpp\"
#include \"scal.hpp\"
#include \"sum.hpp\"
#include \"vecadd.hpp\"
#include \"vecsub.hpp\"
#include \"xpay.hpp\"

namespace monolish::blas {
"

## vecadd
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    for arg2 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      for arg3 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
        echo "void vecadd(const $arg1 &a, const $arg2 &b, $arg3 &y){vecadd_core(a, b, y);}"
      done
    done
  done
done

echo ""

## vecsub
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    for arg2 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      for arg3 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
        echo "void vecsub(const $arg1 &a, const $arg2 &b, $arg3 &y){vecsub_core(a, b, y);}"
      done
    done
  done
done

echo ""

## copy
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    for arg2 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      echo "void copy(const $arg1 &x, $arg2 &y){copy_core(x, y);}"
    done
  done
done

echo ""

## asum
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    if [ $prec = "double" ]
    then
      echo "$prec asum(const $arg1 &x){ return Dasum_core(x); }"
    else
      echo "$prec asum(const $arg1 &x){ return Sasum_core(x); }"
    fi
  done
done

echo ""

for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    echo "void asum(const $arg1 &x, $prec &ans){ ans = asum(x); }"
  done
done

echo ""

## sum
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    if [ $prec = "double" ]
    then
      echo "$prec sum(const $arg1 &x){ return Dsum_core(x); }"
    else
      echo "$prec sum(const $arg1 &x){ return Ssum_core(x); }"
    fi
  done
done

echo ""

for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    echo "void sum(const $arg1 &x, $prec &ans){ ans = sum(x); }"
  done
done

echo ""

## axpy
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    for arg2 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      if [ $prec = "double" ]
      then
        echo "void axpy(const $prec alpha, const $arg1 &x, $arg2 &y) {Daxpy_core(alpha, x, y);}"
      else
        echo "void axpy(const $prec alpha, const $arg1 &x, $arg2 &y) {Saxpy_core(alpha, x, y);}"
      fi
    done
  done
done

echo ""

## axpyz
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    for arg2 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      for arg3 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      if [ $prec = "double" ]
      then
        echo "void axpyz(const $prec alpha, const $arg1 &x, const $arg2 &y, $arg3 &z){Daxpyz_core(alpha, x, y, z);}"
      else
        echo "void axpyz(const $prec alpha, const $arg1 &x, const $arg2 &y, $arg3 &z){Saxpyz_core(alpha, x, y, z);}"
      fi
      done
    done
  done
done

echo ""

# ## dot
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    for arg2 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      if [ $prec = "double" ]
      then
        echo "$prec dot(const $arg1 &x, const $arg2 &y){return Ddot_core(x, y);}"
      else
        echo "$prec dot(const $arg1 &x, const $arg2 &y){return Sdot_core(x, y);}"
      fi
    done
  done
done

echo ""

# ## dot
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    for arg2 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      echo "void dot(const $arg1 &x, const $arg2 &y, $prec &ans){ ans = dot(x, y); }"
    done
  done
done

echo ""

## nrm1
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      if [ $prec = "double" ]
      then
        echo "$prec nrm1(const $arg1 &x){ return Dnrm1_core(x); }"
      else
        echo "$prec nrm1(const $arg1 &x){ return Snrm1_core(x); }"
      fi
  done
done

echo ""

## nrm1
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    echo "void nrm1(const $arg1 &x, $prec &ans){ ans = nrm1(x); }"
  done
done

echo ""

## nrm2
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      if [ $prec = "double" ]
      then
        echo "$prec nrm2(const $arg1 &x){ return Dnrm2_core(x); }"
      else
        echo "$prec nrm2(const $arg1 &x){ return Snrm2_core(x); }"
      fi
  done
done

echo ""

## nrm2
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    echo "void nrm2(const $arg1 &x, $prec &ans){ ans = nrm2(x); }"
  done
done

echo ""

## scal
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      if [ $prec = "double" ]
      then
        echo "void scal(const $prec alpha, $arg1 &x){ Dscal_core(alpha, x); }"
      else
        echo "void scal(const $prec alpha, $arg1 &x){ Sscal_core(alpha, x); }"
      fi
  done
done

echo ""

## xpay
for prec in double float; do
  for arg1 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
    for arg2 in vector\<$prec\> view1D\<vector\<$prec\>,$prec\> view1D\<matrix::Dense\<$prec\>,$prec\>; do
      if [ $prec = "double" ]
      then
        echo "void xpay(const $prec alpha, const $arg1 &x, $arg2 &y) {Dxpay_core(alpha, x, y);}"
      else
        echo "void xpay(const $prec alpha, const $arg1 &x, $arg2 &y) {Sxpay_core(alpha, x, y);}"
      fi
    done
  done
done

echo "}"