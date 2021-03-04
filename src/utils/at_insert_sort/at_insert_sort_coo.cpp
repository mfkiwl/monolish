#include "../../../include/common/monolish_dense.hpp"
#include "../../../include/common/monolish_logger.hpp"
#include "../../../include/common/monolish_matrix.hpp"
#include "../../internal/monolish_internal.hpp"

namespace monolish {
namespace matrix {

template <typename T> T COO<T>::at(const size_t i, const size_t j) const {

  assert(i <= get_row());
  assert(j <= get_col());

  // since last inserted element is effective elements,
  // checking from last element is necessary
  if (nnz != 0) {
    for (size_t k = nnz; k > 0; --k) {
      if (row_index[k - 1] == (int)i && col_index[k - 1] == (int)j) {
        return val[k - 1];
      }
    }
  }
  return 0.0;
}
template double COO<double>::at(const size_t i, const size_t j) const;
template float COO<float>::at(const size_t i, const size_t j) const;

// insert //
template <typename T>
void COO<T>::insert(const size_t m, const size_t n, const T value) {
  size_t rownum = m;
  size_t colnum = n;
  assert(rownum <= get_row());
  assert(colnum <= get_col());

  row_index.push_back(rownum);
  col_index.push_back(colnum);
  val.push_back(value);
  ++nnz;
}
template void COO<double>::insert(const size_t m, const size_t n,
                                  const double value);
template void COO<float>::insert(const size_t m, const size_t n,
                                 const float value);

// sort //

template <typename T> void COO<T>::_q_sort(int lo, int hi) {
  // Very primitive quick sort
  if (lo >= hi) {
    return;
  }

  int l = lo;
  int h = hi;
  int p = hi;
  int p1 = row_index[p];
  int p2 = col_index[p];
  double p3 = val[p];

  do {
    while ((l < h) && ((row_index[l] != row_index[p])
                           ? (row_index[l] - row_index[p])
                           : (col_index[l] - col_index[p])) <= 0) {
      l = l + 1;
    }
    while ((h > l) && ((row_index[h] != row_index[p])
                           ? (row_index[h] - row_index[p])
                           : (col_index[h] - col_index[p])) >= 0) {
      h = h - 1;
    }
    if (l < h) {
      int t = row_index[l];
      row_index[l] = row_index[h];
      row_index[h] = t;

      t = col_index[l];
      col_index[l] = col_index[h];
      col_index[h] = t;

      double td = val[l];
      val[l] = val[h];
      val[h] = td;
    }
  } while (l < h);

  row_index[p] = row_index[l];
  row_index[l] = p1;

  col_index[p] = col_index[l];
  col_index[l] = p2;

  val[p] = val[l];
  val[l] = p3;

  /* Sort smaller array first for less stack usage */
  if (l - lo < hi - l) {
    _q_sort(lo, l - 1);
    _q_sort(l + 1, hi);
  } else {
    _q_sort(l + 1, hi);
    _q_sort(lo, l - 1);
  }
}
template void COO<double>::_q_sort(int lo, int hi);
template void COO<float>::_q_sort(int lo, int hi);

template <typename T> void COO<T>::sort(bool merge) {
  //  Sort by first Col and then Row
  //  TODO: This hand-written quick sort function should be retired
  //        after zip_iterator() (available in range-v3 library) is available in
  //        the standard (hopefully C++23)
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);

  _q_sort(0, nnz - 1);

  /*  Remove duplicates */
  if (merge) {
    size_t k = 0;
    for (size_t i = 1; i < nnz; i++) {
      if ((row_index[k] != row_index[i]) || (col_index[k] != col_index[i])) {
        k++;
        row_index[k] = row_index[i];
        col_index[k] = col_index[i];
      }
      val[k] = val[i];
    }
    nnz = k + 1;
  }

  logger.util_out();
}
template void COO<double>::sort(bool merge);
template void COO<float>::sort(bool merge);

} // namespace matrix
} // namespace monolish
