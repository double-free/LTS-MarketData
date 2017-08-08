#include "ringbuffer.h"
#include <chrono>
#include <cstring> // for memcpy
#include <fstream>
#include <thread>

RingBuffer::RingBuffer() {
  buffer_ = nullptr;
  in_ = 0;
  out_ = 0;

  threadPool_ = new ThreadPool(1);
}

RingBuffer::RingBuffer(size_t size) {
  if (is_power_of_2_(size) == false) {
    size = roundup_power_of_2(size);
  }
  size_ = size;
  buffer_ = new char[size];
  in_ = 0;
  out_ = 0;
  threadPool_ = new ThreadPool(1);
}

RingBuffer::~RingBuffer() {
  if (buffer_) {
    delete[] buffer_;
    buffer_ = nullptr;
  }
  if (threadPool_) {
    delete threadPool_;
  }
}

void RingBuffer::setSize(size_t size) {
  if (is_power_of_2_(size) == false) {
    size = roundup_power_of_2(size);
  }
  if (buffer_) {
    delete[] buffer_;
  }
  buffer_ = new char[size];
  size_ = size;
}

void RingBuffer::getData(char *buf, size_t datalen) {
  if (buf == nullptr || buffer_ == nullptr)
    return;
  datalen = std::min(datalen, in_ - out_);
  size_t len = std::min(datalen, size_ - (out_ & (size_ - 1)));
  memcpy(buf, buffer_ + (out_ & (size_ - 1)), len);
  memcpy(buf + len, buffer_, datalen - len);
  out_ += datalen;
}

/*****************************************************
 * 实现思路1： 一个线程 putData，另一个线程定时异步写入文件
 * 优点：可以根据写入结果修改out，保证正确性
 * 缺点：线程安全问题，需要使用 memory barrier
 *****************************************************/
/*
void RingBuffer::putData(char* data, size_t datalen) {
  if (data == nullptr || buffer_ == nullptr) return;
  datalen = std::min(datalen, size_ - in_ + out_);
  size_t len = std::min(datalen, size_ - (in_ & (size_ - 1)));
  memcpy(buffer_ + (in_ & (size_-1)), data, len);
  memcpy(buffer_, data + len, datalen - len);
  in_ += datalen;
  // printf("PUT: \n\tpos in increase to %lu, out = %lu, data length = %lu(of
%lu)\n", in_, out_, dataLength(), size_);
}
*/
// for xtp market data
// 异步写文件
/*
void RingBuffer::startWrite(const std::string& path, size_t time_interval) {
  auto f = [this](const std::string& path_, size_t time_interval_){
    printf("Worker Thread: %08x\n", std::this_thread::get_id());
    while (true) {
      this->writeDataToFile(path_);
      std::this_thread::sleep_for(std::chrono::seconds(time_interval_));
    }
  };
  std::thread t(f, std::ref(path), time_interval);
  t.detach();
}

void RingBuffer::writeDataToFile(const std::string& path) {
  size_t size_to_write = in_ - out_;
  std::ofstream fs(path, std::ios::out | std::ios::app);
  if (fs.is_open() == false || size_to_write == 0) {
    return;
  }
  size_t len = std::min(size_to_write, size_ - (out_ & (size_ - 1)));
  fs.write(buffer_ + (out_ & (size_ -1)), len);
  fs.write(buffer_, size_to_write - len);
  fs.close();
  out_ += size_to_write;
  // printf("GET: \n\tpos out increase to %lu, in = %lu, data length = %lu(of
%lu)\n", out_, in_, dataLength(), size_);
}
*/

/********************************************************
 * 实现思路2：一个线程 putData，超过一定量后修改 out，再异步写入
 * 优点： 修改 in out 都在一个线程，不需要任何同步
 * 缺点： 不能确保写入成功与否，写入失败会出现问题
 * 缺点: 如果出现第一次写入尚未结束，第二次写入又开始的情况会发生什么?
 ********************************************************/
void RingBuffer::setSavePath(const std::string &path) { outFilePath_ = path; }

void RingBuffer::putData(char *data, size_t datalen) {
  // std::lock_guard<std::mutex> lg(mu_);
  if (data == nullptr || buffer_ == nullptr)
    return;
  datalen = std::min(datalen, size_ - in_ + out_);
  size_t len = std::min(datalen, size_ - (in_ & (size_ - 1)));
  memcpy(buffer_ + (in_ & (size_ - 1)), data, len);
  memcpy(buffer_, data + len, datalen - len);
  in_ += datalen;
  // printf("PUT: \n\tpos in increase to %lu, out = %lu, data length = %lu(of
  // %lu)\n", in_, out_, dataLength(), size_);
  size_t currentDataLen = dataLength();
  if (currentDataLen > (size_ >> 1) && outFilePath_.empty() == false) {
    /*
    auto f = [this](const std::string& path, size_t out, size_t len) {
      this->writeDataToFile(path, out, len);
    };
    */
    /* 这样会在每次写入时有新建线程的额外开销
    std::thread t1(&RingBuffer::writeDataToFile, this, std::ref(outFilePath_),
    out_, currentDataLen);
    t1.detach();
    */
    threadPool_->doJob(std::bind(&RingBuffer::writeDataToFile, this,
                                 std::cref(outFilePath_), out_,
                                 currentDataLen));
    out_ = in_;
  }
}

void RingBuffer::writeDataToFile(const std::string &path, size_t out,
                                 size_t size_to_write) {
  // 整个函数中并没有用到 in，所以无论另一个线程如何 putData
  // 都不会影响这个函数的运作
  printf(
      "Write at thread: %08x, from %lu to %lu(not precisely), length = %lu\n",
      std::this_thread::get_id(), out, in_, size_to_write);
  std::ofstream fs(path, std::ios::out | std::ios::app);
  if (fs.is_open() == false || size_to_write == 0) {
    return;
  }
  size_t len = std::min(size_to_write, size_ - (out & (size_ - 1)));
  fs.write(buffer_ + (out & (size_ - 1)), len);
  fs.write(buffer_, size_to_write - len);
  fs.close();
  printf("\tWrite finished...\n");
  // printf("GET: \n\tpos out increase to %lu, in = %lu, data length = %lu(of
  // %lu)\n", out_, in_, dataLength(), size_);
}
