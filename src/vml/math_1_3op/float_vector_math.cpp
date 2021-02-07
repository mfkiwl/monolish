#include "../../../include/monolish_vml.hpp"
#include "../../internal/monolish_internal.hpp"

namespace monolish {


void vml::pow(const vector<float> &a, const float alpha, vector<float> &y) {
}

//////////////////////////////////////////
// other
//////////////////////////////////////////
void vml::max(const vector<float> &a, const vector<float> &b,
              vector<float> &y) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  // err
  assert(util::is_same_size(a, b, y));
  assert(util::is_same_device_mem_stat(a, b, y));

  internal::vmax(y.size(), a.data(), b.data(), y.data(),
                 y.get_device_mem_stat());

  logger.func_out();
}

float vml::max(const vector<float> &y) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  float max = internal::vmax(y.size(), y.data(), y.get_device_mem_stat());

  logger.func_out();
  return max;
}

void vml::min(const vector<float> &a, const vector<float> &b,
              vector<float> &y) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  // err
  assert(util::is_same_size(a, b, y));
  assert(util::is_same_device_mem_stat(a, b, y));

  internal::vmin(y.size(), a.data(), b.data(), y.data(),
                 y.get_device_mem_stat());

  logger.func_out();
}

float vml::min(const vector<float> &y) {
  Logger &logger = Logger::get_instance();
  logger.func_in(monolish_func);

  float min = internal::vmin(y.size(), y.data(), y.get_device_mem_stat());

  logger.func_out();
  return min;
}

} // namespace monolish
