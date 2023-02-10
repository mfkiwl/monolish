#pragma once
#include "./monolish_dense.hpp"
#include "./monolish_logger.hpp"
#include "./monolish_view1D.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <omp.h>
#include <stdexcept>
#include <string>
#include <vector>

#if USE_SXAT
#undef _HAS_CPP17
#endif
#include <random>
#if USE_SXAT
#define _HAS_CPP17 1
#endif

#if defined USE_MPI
#include <mpi.h>
#endif

namespace monolish {

/**
 * @addtogroup Vector_class
 * @{
 */

/**
 * @brief vector class
 * @note
 * - Multi-threading: true
 * - GPU acceleration: false
 */
template <typename Float> class vector {
private:
  /**
   * @brief vector data (pointer)
   */
  std::shared_ptr<Float> vad;

  /**
   * @brief vector size
   */
  std::size_t vad_nnz = 0;

  /**
   * @brief alloced vector size
   */
  std::size_t alloc_nnz = 0;

  /**
   * @brief vector create flag;
   */
  bool vad_create_flag = false;


  /**
   * @brief true: sended, false: not send
   **/
  mutable bool gpu_status = false;

public:
  vector() {
    vad_create_flag = true;
  }

  // constructor ///////////////////////////////////////////////////////
  /**
   * @brief allocate size N vector
   * @param N vector length
   * @note
   * - # of computation: N
   * - Multi-threading: false
   * - GPU acceleration: false
   **/
  vector(const size_t N);

  /**
   * @brief initialize size N vector, value to fill the container
   * @param N vector length
   * @param value fill Float type value to all elements
   * @note
   * - # of computation: N
   * - Multi-threading: false
   * - GPU acceleration: false
   **/
  vector(const size_t N, const Float value);

  /**
   * @brief copy from std::vector
   * @param vec input std::vector
   * @note
   * - # of computation: N
   * - Multi-threading: false
   * - GPU acceleration: false
   **/
  vector(const std::vector<Float> &vec);

  /**
   * @brief copy from initializer_list
   * @param list input initializer_list
   * @note
   * - # of computation: N
   * - Multi-threading: false
   * - GPU acceleration: false
   **/
  vector(const std::initializer_list<Float> &list);

  /**
   * @brief copy from monolish::vector
   * @param vec input monolish::vector
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   *    - # of data transfer: N (only allocation)
   *        - if `gpu_status == true`; coping data on CPU and GPU
   *respectively
   *        - else; coping data only on CPU
   **/
  vector(const vector<Float> &vec);

  /**
   * @brief copy from monolish::view1D from vector
   * @param vec input monolish::view1D from vector
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   *    - # of data transfer: N (only allocation)
   *        - if `gpu_status == true`; coping data on CPU and GPU
   *respectively
   *        - else; coping data only on CPU
   **/
  vector(const view1D<vector<Float>, Float> &vec);

  /**
   * @brief copy from monolish::view1D from monolish::matrix::Dense
   * @param vec input monolish::view1D from monolish::matrix::Dense
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   *    - # of data transfer: N (only allocation)
   *        - if `gpu_status == true`; coping data on CPU and GPU
   *respectively
   *        - else; coping data only on CPU
   **/
  vector(const view1D<matrix::Dense<Float>, Float> &vec);

  /**
   * @brief copy from pointer
   * @param start start pointer
   * @param end  end pointer
   * @note
   * - # of computation: N
   * - Multi-threading: false
   * - GPU acceleration: false
   **/
  vector(const Float *start, const Float *end);

  /**
   * @brief create N length rand(min~max) vector
   * @param N vector length
   * @param min rand min
   * @param max rand max
   * @note
   * - # of computation: N
   * - Multi-threading: false
   * - GPU acceleration: false
   **/
  vector(const size_t N, const Float min, const Float max);

  /**
   * @brief create N length rand(min~max) vector with random seed
   * @param N vector length
   * @param min rand min
   * @param max rand max
   * @param seed random seed
   * @note
   * The ramdom number generator is random generator is mt19937
   * - # of computation: N
   * - Multi-threading: false
   * - GPU acceleration: false
   **/
  vector(const size_t N, const Float min, const Float max,
         const std::uint32_t seed);

  // communication
  // ///////////////////////////////////////////////////////////////////////////
  /**
   * @brief send data to GPU
   * @note
   * - # of data transfer: N
   * - Multi-threading: false
   * - GPU acceleration: true
   **/
  void send() const;

  /**
   * @brief recv data from GPU, and free data on GPU
   * @note
   * - # of data transfer: N
   * - Multi-threading: false
   * - GPU acceleration: true
   **/
  void recv();

  /**
   * @brief recv data from GPU (w/o free)
   * @note
   * - # of data transfer: N
   * - Multi-threading: false
   * - GPU acceleration: true
   **/
  void nonfree_recv();

  /**
   * @brief free data on GPU
   * @note
   * - # of data transfer: 0
   * - Multi-threading: false
   * - GPU acceleration: true
   **/
  void device_free() const;

  /**
   * @brief true: sended, false: not send
   * @return gpu status
   * @note
   * - # of data transfer: 0
   * - Multi-threading: false
   * - GPU acceleration: true
   **/
  [[nodiscard]] bool get_device_mem_stat() const { return gpu_status; }

  /**
   * @brief destructor of vector, free GPU memory
   * @note
   * - # of data transfer: 0
   * - Multi-threading: false
   * - GPU acceleration: true
   **/
  ~vector() {
    if (get_device_mem_stat()) {
      device_free();
    }
  }

  [[nodiscard]] size_t get_offset() const { return 0; }

  // util
  // ///////////////////////////////////////////////////////////////////////////

  /**
   * @brief returns a direct pointer to the vector
   * @return A const pointer to the first element
   * @note
   * - # of computation: 1
   **/
  [[nodiscard]] const Float *data() const { return vad.get(); }

  /**
   * @brief returns a direct pointer to the vector
   * @return A pointer to the first element
   * @note
   * - # of computation: 1
   **/
  [[nodiscard]] Float *data() { return vad.get(); }

  /**
   * @brief resize vector (only CPU)
   * @param N vector length
   * @note
   * - # of computation: N
   * - Multi-threading: false
   * - GPU acceleration: false
   **/
  void resize(size_t N, Float val = 0) {
    if (get_device_mem_stat()) {
      throw std::runtime_error("Error, GPU vector cant use resize");
    }
    if(vad_create_flag){
      std::shared_ptr<Float> tmp(new Float[N], std::default_delete<Float[]>());
      size_t copy_size = std::min(vad_nnz, N);
      for (size_t i = 0; i < copy_size; i++){
        tmp.get()[i] = vad.get()[i];
      }
      for (size_t i = copy_size; i < N; i++){
        tmp.get()[i] = val;
      }
      vad = tmp;
      alloc_nnz = N;
      vad_nnz = N;
    }else{
      throw std::runtime_error("Error, not create vector cant use resize");
    }
  }

  /**
   * @brief Add a new element at the end of the vector (only CPU)
   * @param val new element
   * @note
   * - # of computation: 1
   **/
  void push_back(Float val) {
    if (get_device_mem_stat()) {
      throw std::runtime_error("Error, GPU vector cant use push_back");
    }
    if(vad_create_flag){
      if(vad_nnz >= alloc_nnz){
        size_t tmp = vad_nnz;
        alloc_nnz = 2*alloc_nnz+1;
        resize(alloc_nnz);
        vad_nnz = tmp;
      }
      vad.get()[vad_nnz] = val;
      vad_nnz++;
    }else{
      throw std::runtime_error("Error, not create vector cant use push_back");
    }
  }

  /**
   * @brief returns a begin iterator
   * @return begin iterator
   * @note
   * - # of computation: 1
   **/
  [[nodiscard]] const Float *begin() const { return vad.get(); }

  /**
   * @brief returns a begin iterator
   * @return begin iterator
   * @note
   * - # of computation: 1
   **/
  [[nodiscard]] Float *begin() { return vad.get(); }

  /**
   * @brief returns a end iterator
   * @return end iterator
   * @note
   * - # of computation: 1
   **/
  [[nodiscard]] const Float *end() const { return vad.get() + size(); }

  /**
   * @brief returns a end iterator
   * @return end iterator
   * @note
   * - # of computation: 1
   **/
  [[nodiscard]] Float *end() { return vad.get() + size(); }

  /**
   * @brief get vector size
   * @return vector size
   * @note
   * - # of computation: 1
   **/
  [[nodiscard]] size_t size() const { return vad_nnz; }

  /**
   * @brief get vector size
   * @return vector size
   * @note
   * - # of computation: 1
   **/
  [[nodiscard]] size_t get_nnz() const { return vad_nnz; }

  /**
   * @brief fill vector elements with a scalar value
   * @param value scalar value
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   **/
  void fill(Float value);

  /**
   * @brief print all elements to standart I/O
   * @param force_cpu Ignore device status and output CPU data
   * @note
   * - # of computation: N
   * - Multi-threading: false
   * - GPU acceleration: true (doesn't work in parallel)
   **/
  void print_all(bool force_cpu = false) const;

  /**
   * @brief print all elements to file
   * @param filename output filename
   * @note
   * - # of computation: N
   * - Multi-threading: false
   * - GPU acceleration: false
   **/
  void print_all(std::string filename) const;

  // operator
  // ///////////////////////////////////////////////////////////////////////////

  /**
   * @brief copy vector, It is same as copy ( Copy the memory on CPU and GPU )
   * @param vec source vector
   * @return output vector
   * @note
   * - # of computation: N
   * - Multi-threading: false
   * - GPU acceleration: true
   *    - # of data transfer: 0
   *        - if `gpu_statius == true`; coping data on GPU
   *        - else; coping data on CPU
   **/
  void operator=(const vector<Float> &vec);

  /**
   * @brief copy vector, It is same as copy ( Copy the memory on CPU and GPU )
   * @param vec source view1D from monolish::vector
   * @return output vector
   * @note
   * - # of computation: N
   * - Multi-threading: false
   * - GPU acceleration: true
   *    - # of data transfer: 0
   *        - if `gpu_statius == true`; coping data on GPU
   *        - else; coping data on CPU
   **/
  void operator=(const view1D<vector<Float>, Float> &vec);

  /**
   * @brief copy vector, It is same as copy ( Copy the memory on CPU and GPU )
   * @param vec source view1D from monolish::matrix::Dense
   * @return output vector
   * @note
   * - # of computation: N
   * - Multi-threading: false
   * - GPU acceleration: true
   *    - # of data transfer: 0
   *        - if `gpu_statius == true`; coping data on GPU
   *        - else; coping data on CPU
   **/
  void operator=(const view1D<matrix::Dense<Float>, Float> &vec);

  /**
   * @brief copy vector from std::vector
   * @param vec source std::vector
   * @return output vector
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: false
   **/
  void operator=(const std::vector<Float> &vec);

  /**
   * @brief Sign inversion
   * @return output vector
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   **/
  [[nodiscard]] vector<Float> operator-();

  /**
   * @brief reference to the element at position (v[i])
   * @param i Position of an element in the vector
   * @return vector element (v[i])
   * @note
   * - # of computation: 1
   * - Multi-threading: false
   * - GPU acceleration: false
   **/
  [[nodiscard]] Float &operator[](size_t i) {
    if (get_device_mem_stat()) {
      throw std::runtime_error("Error, GPU vector cant use operator[]");
    }
    return vad.get()[i];
  }

  /**
   * @brief Comparing matrices (A == mat)
   * @param vec vector
   * @param compare_cpu_and_device compare data on both CPU and GPU
   * @return true or false
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   **/
  bool equal(const vector<Float> &vec,
             bool compare_cpu_and_device = false) const;

  /**
   * @brief Comparing matrices (A == mat)
   * @param vec view1D from monolish::vector
   * @param compare_cpu_and_device compare data on both CPU and GPU
   * @return true or false
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   **/
  bool equal(const view1D<vector<Float>, Float> &vec,
             bool compare_cpu_and_device = false) const;

  /**
   * @brief Comparing matrices (A == mat)
   * @param vec view1D from monolish::matrix::Dense
   * @param compare_cpu_and_device compare data on both CPU and GPU
   * @return true or false
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   **/
  bool equal(const view1D<matrix::Dense<Float>, Float> &vec,
             bool compare_cpu_and_device = false) const;

  /**
   * @brief Comparing vectors (v == vec)
   * @param vec vector (size N)
   * @return true or false
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   *   - if `gpu_status == true`; compare data on GPU
   *   - else; compare data on CPU
   **/
  bool operator==(const vector<Float> &vec) const;

  /**
   * @brief Comparing vectors (v == vec)
   * @param vec view1D from monolish::vector (size N)
   * @return true or false
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   *   - if `gpu_status == true`; compare data on GPU
   *   - else; compare data on CPU
   **/
  bool operator==(const view1D<vector<Float>, Float> &vec) const;

  /**
   * @brief Comparing vectors (v == vec)
   * @param vec view1D from monolish::matrix::Dense (size N)
   * @return true or false
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   *   - if `gpu_status == true`; compare data on GPU
   *   - else; compare data on CPU
   **/
  bool operator==(const view1D<matrix::Dense<Float>, Float> &vec) const;

  /**
   * @brief Comparing vectors (v != vec)
   * @param vec vector (size N)
   * @return true or false
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   *   - if `gpu_status == true`; compare data on GPU
   *   - else; compare data on CPU
   **/
  bool operator!=(const vector<Float> &vec) const;

  /**
   * @brief Comparing vectors (v != vec)
   * @param vec vector (size N)
   * @return true or false
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   *   - if `gpu_status == true`; compare data on GPU
   *   - else; compare data on CPU
   **/
  bool operator!=(const view1D<vector<Float>, Float> &vec) const;

  /**
   * @brief Comparing vectors (v != vec)
   * @param vec vector (size N)
   * @return true or false
   * @note
   * - # of computation: N
   * - Multi-threading: true
   * - GPU acceleration: true
   *   - if `gpu_status == true`; compare data on GPU
   *   - else; compare data on CPU
   **/
  bool operator!=(const view1D<matrix::Dense<Float>, Float> &vec) const;
};
/**@}*/
} // namespace monolish
