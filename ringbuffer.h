/*******************************************************************
 * This ring buffer is designed only for 1 producer and 1 consumer *
 *******************************************************************/
#pragma once
#include "ThreadPool/thread_pool.h"
#include <cstddef>
#include <string>

class RingBuffer {
  // 1 个生产者，1 个消费者时不需要锁
  // LTS 有 3 个生产者，需要锁
  // XTP 只有 1 个生产者，不需要锁
public:
  RingBuffer();
  explicit RingBuffer(size_t size);
  ~RingBuffer();

  inline size_t dataLength() {
    /*
       _____out______in_____
      |_空闲_|__占用__|_空闲_|   occupied = in - out

       _____in______out_____
      |_占用_|__空闲__|_占用_|   occupied = in + size - out
      由于是无符号类型, in < out 时会自动 wrap-around
    */
    return in_ - out_;
  }

  void setSize(size_t size);

  void putData(char *data, size_t datalen);
  void getData(char *buf, size_t datalen);
  // void startWrite(const std::string& path, size_t time_interval = 1);
  void setSavePath(const std::string &path);

private:
  char *buffer_;
  size_t size_; // 缓冲区大小
  size_t in_;
  size_t out_;

  // for multi-thread putData
  // only one thread is ensured by ltsmdspi.
  // so we don't need the lock anymore.
  // std::mutex mu_;

  // path to save market data
  std::string outFilePath_;

  // a thread pool for writing file (1 thread is enough)
  ThreadPool *threadPool_;

  inline bool is_power_of_2_(size_t x) { return x != 0 && (x & (x - 1)) == 0; }
  inline size_t roundup_power_of_2(size_t x) {
    size_t ret = 1;
    while (ret < x) {
      ret = ret << 1;
    }
    return ret;
  }
  // void writeDataToFile(const std::string& path);
  void writeDataToFile(const std::string &path, size_t out, size_t dataLen);
};
