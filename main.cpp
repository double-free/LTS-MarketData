#include <cstdio>
#include <cstring>
#include <csignal>

#include <mutex>
#include <condition_variable>

#include "ltsmdspi.h"

// kill -l: signal 1~64
int signaled = 0;
std::mutex signal_mu;
std::condition_variable signal_cond;

void signal_handler(int sig) {
  // use signal handler to avoid unsafe quit
  std::lock_guard<std::mutex> lg(signal_mu);
  signaled = sig;
  signal_cond.notify_one();
}

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <config file>\n", argv[0]);
    exit(-1);
  }

  // set handler for signal
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  LtsMdSpi spi(argv[1]);
  // LtsMdSpi spi(std::string(argv[1]));
  spi.start_serve();

  {
    std::unique_lock<std::mutex> ul(signal_mu);
    signal_cond.wait(ul, []{return signaled != 0;});
  }

  printf("Terminated by signal: %d\n", signaled);
  return 0;
}
