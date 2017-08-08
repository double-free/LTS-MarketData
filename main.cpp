#include <cstdio>
#include <cstring>
#include <thread>

#include "ltsmdspi.h"

int main(int argc, const char *argv[]) {
  /*
  printf("Size of:\n\tMarket Data: %lu\n\tMarket Index: %lu\n\tMarket Order: "
         "%lu\n\tMarket Trade: %lu\n",
         sizeof(CSecurityFtdcL2MarketDataField), // 847
         sizeof(CSecurityFtdcL2IndexField),      // 126
         sizeof(CSecurityFtdcL2OrderField),      // 81
         sizeof(CSecurityFtdcL2TradeField));     // 91
  */
  int mode;
  if (argc > 2) {
    printf("Usage: %s SH\n\tor: %s SZ\n\tor: %s ALL(default)\n",
            argv[0], argv[0], argv[0]);
    exit(-1);
  } else if ( argc == 1) {
    mode = 0;
  } else {
    mode = LtsMdSpi::whichMode(argv[1]);
    if (mode == -1) {
      printf("Usage: %s SH\n\tor: %s SZ\n\tor: %s ALL(default)\n",
            argv[0], argv[0], argv[0]);
      exit(-1);
    }
  }

  LtsMdSpi spi(mode);
  spi.start_serve();
  return 0;
}
