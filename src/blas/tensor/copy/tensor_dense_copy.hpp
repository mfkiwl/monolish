#include "../../../../include/monolish_blas.hpp"
#include "../../../internal/monolish_internal.hpp"

namespace monolish {

namespace {
template <typename TENS1, typename TENS2>
void copy_core(const TENS1 &A, TENS2 &C) {
  Logger &logger = Logger::get_instance();
  logger.util_in(monolish_func);

  // err
  assert(util::is_same_size(A, C));
  assert(util::is_same_device_mem_stat(A, C));

  internal::vcopy(A.get_nnz(), A.begin(), C.begin(), A.get_device_mem_stat());

  logger.util_out();
}
} // namespace
} // namespace monolish
