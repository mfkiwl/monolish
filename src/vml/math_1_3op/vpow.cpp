#include "../../../include/monolish_vml.hpp"
#include "../../internal/monolish_internal.hpp"

namespace monolish {
  namespace{
    template <typename F1, typename F2, typename F3>
      void vvpow_core(const F1 &a, const F2 &b, F3 &y) {
        Logger &logger = Logger::get_instance();
        logger.func_in(monolish_func);

        // err
        assert(util::is_same_size(a, b, y));
        assert(util::is_same_device_mem_stat(a, b, y));

        internal::vpow(y.size(), a.data(), b.data(), y.data(),
            y.get_device_mem_stat());

        logger.func_out();
      }

    template <typename F1, typename F2, typename F3>
      void svpow_core(const F1 &a, const F2 &alpha, F3 &y) {
        Logger &logger = Logger::get_instance();
        logger.func_in(monolish_func);

        // err
        assert(util::is_same_size(a, y));
        assert(util::is_same_device_mem_stat(a, y));

        internal::vpow(y.size(), a.data(), alpha, y.data(), y.get_device_mem_stat());

        logger.func_out();
      }
  }


  namespace vml {
    void pow(const vector<double> &a, const vector<double> &b, vector<double> &y) {
      vvpow_core(a, b, y);
    }

    void pow(const vector<float> &a, const vector<float> &b, vector<float> &y) {
      vvpow_core(a, b, y);
    }

    void pow(const vector<double> &a, const double alpha, vector<double> &y) {
      svpow_core(a, alpha, y);
    }

    void pow(const vector<float> &a, const float alpha, vector<float> &y) {
      svpow_core(a, alpha, y);
    }
  }
}
