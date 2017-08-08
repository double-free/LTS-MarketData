#pragma once

#include <cstring>
#include <ctime>
#include <iomanip>

#define PACKED __attribute__((packed))
#define unlikely(cond) __builtin_expect(!!(cond), 0)


namespace common {

constexpr static size_t nanos_per_second = 1'000'000'000;

static inline uint64_t local_timestamp_ns() {
  struct timespec ts;
  if (unlikely(clock_gettime(CLOCK_REALTIME, &ts) == -1))
    return 0;
  return ts.tv_sec * nanos_per_second + ts.tv_nsec;
}

struct tick_header {
  uint64_t timestamp = 0;
  // per msg seq id (not global seq id), 0 means not available
  uint64_t seq_id = 0;
  uint32_t msg_id = 0;
  uint32_t body_size = 0; // tick header itself is not involved

  inline void init() {
    timestamp = common::local_timestamp_ns();
    seq_id = 0;
    msg_id = 0;
    body_size = 0;
  }

  inline static void init(char *addr) {
    auto header = (tick_header *)addr;
    header->timestamp = common::local_timestamp_ns();
    header->seq_id = 0;
    header->msg_id = 0;
    header->body_size = 0;
  }

} PACKED;
}
