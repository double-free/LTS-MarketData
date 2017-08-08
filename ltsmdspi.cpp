#include <cstdio>
#include <fstream>
#include <set>
#include <utility>

#include <sys/stat.h>
#include <unistd.h>

#include "ltsmdspi.h"
#include "timing.hpp"

const char *modes[] = {"ALL", "SH", "SZ"};
// 返回对应模式序号
// 没找到返回 -1
int LtsMdSpi::whichMode(const char *s) {
  if (s == nullptr)
    return -1;
  int length = sizeof(modes) / sizeof(modes[0]);
  for (int i = 0; i < length; ++i) {
    if (strcmp(s, modes[i]) == 0) {
      return i;
    }
  }
  return -1;
}

LtsMdSpi::LtsMdSpi(int mode) : config_("config.ini"), ring_buffer_(1 << 30), mode_(mode) {
  std::string dataDir = config_.Get("MarketData", "SaveDir", "NOT FOUND");
  if (access(dataDir.c_str(), F_OK && W_OK) < 0) {
    mkdir(dataDir.c_str(), 0751);
  }
  ring_buffer_.setSavePath(dataDir + std::string(modes[mode]));
  reqID_ = 0;
  api_ = CSecurityFtdcL2MDUserApi::CreateFtdcL2MDUserApi();
  printf("Market data spi created...\n");
}

LtsMdSpi::~LtsMdSpi() {
  api_->Release();
  printf("Market data spi deleted...\n");
}

void LtsMdSpi::start_serve() {
  api_->RegisterSpi(this);
  std::string addr = config_.Get("FrontServer", "Address", "NOT FOUND");
  api_->RegisterFront((char *)addr.c_str());
  api_->Init();
  api_->Join();
}


void LtsMdSpi::OnFrontConnected() {
  CSecurityFtdcUserLoginField loginField;
  memset(&loginField, 0, sizeof(loginField));
  std::string BrokerID = config_.Get("LoginField", "BrokerID", "NOT FOUND");
  std::string UserID = config_.Get("LoginField", "UserID", "NOT FOUND");
  std::string Password = config_.Get("LoginField", "Password", "NOT FOUND");
  strcpy(loginField.BrokerID, BrokerID.c_str());
  strcpy(loginField.UserID, BrokerID.c_str());
  strcpy(loginField.Password, BrokerID.c_str());
  api_->ReqUserLogin(&loginField, reqID_++);
}

void LtsMdSpi::OnRspUserLogin(CSecurityFtdcUserLoginField *pUserLogin,
                              CSecurityFtdcRspInfoField *pRspInfo,
                              int nRequestID, bool bIsLast) {
  if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
    const std::string SH_FILE = std::move(config_.Get("Instruments", "PathSH", "NOT FOUND"));
    const std::string SZ_FILE = std::move(config_.Get("Instruments", "PathSZ", "NOT FOUND"));
    const std::string SH_ID = "SSE";
    const std::string SZ_ID = "SZE";
    switch (mode_) {
    case 0:
      subscribe_instruments_in_file_(SH_FILE, SH_ID);
      subscribe_instruments_in_file_(SH_FILE, SZ_ID);
      break;

    case 1:
      subscribe_instruments_in_file_(SH_FILE, SH_ID);
      break;

    case 2:
      subscribe_instruments_in_file_(SZ_FILE, SZ_ID);
      break;

    default:
      printf("Unknown mode %d\n", mode_);
    }
  } else {
    printf("Login failed: %s(errno: %d)\n", pRspInfo->ErrorMsg,
           pRspInfo->ErrorID);
  }
}

// 订阅回复
void LtsMdSpi::OnRspSubL2MarketData(
    CSecurityFtdcSpecificInstrumentField *pSpecificInstrument,
    CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
    if (bIsLast) {
      printf("Subscribe to instruments of %s (data) succeed.\n", modes[mode_]);
    }
  } else {
    printf("Subscribe market data failed: %s(errno: %d)\n", pRspInfo->ErrorMsg,
           pRspInfo->ErrorID);
  }
}

void LtsMdSpi::OnRspSubL2Index(
    CSecurityFtdcSpecificInstrumentField *pSpecificInstrument,
    CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
    if (bIsLast) {
      printf("Subscribe to instruments of %s (index) succeed.\n", modes[mode_]);
    }
  } else {
    printf("Subscribe market index failed: %s(errno: %d)\n", pRspInfo->ErrorMsg,
           pRspInfo->ErrorID);
  }
}

void LtsMdSpi::OnRspSubL2OrderAndTrade(CSecurityFtdcRspInfoField *pRspInfo,
                                       int nRequestID, bool bIsLast) {
  if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
    if (bIsLast) {
      printf("Subscribe to instruments of %s (order) succeed.\n", modes[mode_]);
    }
  } else {
    printf("Subscribe market order failed: %s(errno: %d)\n", pRspInfo->ErrorMsg,
           pRspInfo->ErrorID);
  }
}

void LtsMdSpi::OnRtnL2MarketData(
    CSecurityFtdcL2MarketDataField *pL2MarketData) {
  common::tick_header header;
  header.init();
  header.body_size = 847;
  header.msg_id = 1;
  // printf("ticker header size = %d\n", sizeof(h)); // 24
  std::lock_guard<std::mutex> lg(mu_);
  ring_buffer_.putData((char *)&header, 24);
  ring_buffer_.putData((char *)pL2MarketData, header.body_size);
}

void LtsMdSpi::OnRtnL2Index(CSecurityFtdcL2IndexField *pL2Index) {
  common::tick_header header;
  header.init();
  header.body_size = 126;
  header.msg_id = 2;
  // printf("ticker header size = %d\n", sizeof(h)); // 24
  std::lock_guard<std::mutex> lg(mu_);
  ring_buffer_.putData((char *)&header, 24);
  ring_buffer_.putData((char *)pL2Index, header.body_size);
}

void LtsMdSpi::OnRtnL2Order(CSecurityFtdcL2OrderField *pL2Order) {
  common::tick_header header;
  header.init();
  header.body_size = 81;
  header.msg_id = 3;
  // printf("ticker header size = %d\n", sizeof(h)); // 24
  std::lock_guard<std::mutex> lg(mu_);
  ring_buffer_.putData((char *)&header, 24);
  ring_buffer_.putData((char *)pL2Order, header.body_size);
}

void LtsMdSpi::OnRtnL2Trade(CSecurityFtdcL2TradeField *pL2Trade) {
  common::tick_header header;
  header.init();
  header.body_size = 91;
  header.msg_id = 4;
  // printf("ticker header size = %d\n", sizeof(h)); // 24
  std::lock_guard<std::mutex> lg(mu_);
  ring_buffer_.putData((char *)&header, 24);
  ring_buffer_.putData((char *)pL2Trade, header.body_size);
}

void LtsMdSpi::subscribe_instruments_in_file_(const std::string &filePath,
                                              const std::string &exchangeID) {
  std::set<std::string> subscriptions;
  std::ifstream ifs;
  ifs.open(filePath);
  const char delim('\n');
  std::string instrument;
  while (getline(ifs, instrument, delim)) {
    subscriptions.insert(std::move(instrument));
  }
  ifs.clear();
  ifs.close();

  char **subs = new char *[subscriptions.size()];
  int idx = 0;
  for (auto &str : subscriptions) {
    subs[idx++] = (char *)str.c_str();
  }
  api_->SubscribeL2MarketData(subs, idx, (char *)exchangeID.c_str());
  api_->SubscribeL2Index(subs, idx, (char *)exchangeID.c_str());
  api_->SubscribeL2OrderAndTrade();
  delete[] subs;
}

void LtsMdSpi::OnFrontDisconnected(int reason) {
  printf("Disconnected from front server (reason: %d).\n\t"
        "Reconnecting...\n", reason);
  std::string addr = config_.Get("FrontServer", "Address", "NOT FOUND");
  api_->RegisterFront((char *)addr.c_str());
}
