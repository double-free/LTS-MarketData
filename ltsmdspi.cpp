#include <cstdio>
#include <fstream>
#include <set>
#include <utility>
#include <chrono>
#include <cstring>

#include <sys/stat.h>
#include <unistd.h>

#include "ltsmdspi.h"
#include "logger.hpp"

std::string LtsMdSpi::getCurrentDate() {
  std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  char buf[100];
  std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&now));
  return std::string(buf);
}

LtsMdSpi::LtsMdSpi(const std::string& config_file) :
          config_(config_file) {
  std::string dataDir = config_.Get("SavePath", "MdDir", "");
  std::string logDir = config_.Get("SavePath", "LogDir", "");

  std::string currentDate = getCurrentDate();

  if (access(dataDir.c_str(), F_OK && W_OK) < 0) {
    mkdir(dataDir.c_str(), 0751);
  }
  std::string md_path = dataDir + "MarketData_" + currentDate;

  if (access(logDir.c_str(), F_OK && W_OK) < 0) {
    mkdir(logDir.c_str(), 0751);
  }
  std::string output_path = logDir + "output_" + currentDate;
  std::string error_path = logDir + "error_" + currentDate;
  freopen(output_path.c_str(), "w", stdout);
  freopen(error_path.c_str(), "w", stderr);

  // 以 1GB 为单位
  writer_ = new mem::Writer((size_t)config_.GetInteger("Buffer", "InitSize", 1)<<30, md_path);

  reqID_ = 0;
  api_ = CSecurityFtdcL2MDUserApi::CreateFtdcL2MDUserApi();
  common::Logger::t_out("Market data spi created...\n");
}

LtsMdSpi::~LtsMdSpi() {

  api_->Release();
  delete writer_;
  common::Logger::t_out("Market data spi deleted...\n");
  fclose(stdout);
  fclose(stderr);
}

void LtsMdSpi::start_serve() {
  api_->RegisterSpi(this);
  std::string addr = config_.Get("FrontServer", "Address", "");
  api_->RegisterFront((char *)addr.c_str());
  api_->Init();
  // 为了实现捕获信号退出，在主线程阻塞而不在这里Join
  // api_->Join();
}


void LtsMdSpi::OnFrontConnected() {
  CSecurityFtdcUserLoginField loginField;
  memset(&loginField, 0, sizeof(loginField));
  std::string BrokerID = config_.Get("LoginField", "BrokerID", "");
  std::string UserID = config_.Get("LoginField", "UserID", "");
  std::string Password = config_.Get("LoginField", "Password", "");
  strncpy(loginField.BrokerID, BrokerID.c_str(), sizeof(loginField.BrokerID));
  strncpy(loginField.UserID, UserID.c_str(), sizeof(loginField.UserID));
  strncpy(loginField.Password, Password.c_str(), sizeof(loginField.Password));
  common::Logger::t_out("Login with: user = %s, pwd = %s\n", loginField.UserID, loginField.Password);
  api_->ReqUserLogin(&loginField, reqID_++);
}

void LtsMdSpi::OnRspUserLogin(CSecurityFtdcUserLoginField *pUserLogin,
                              CSecurityFtdcRspInfoField *pRspInfo,
                              int nRequestID, bool bIsLast) {
  if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
    const std::string SH_FILE = std::move(config_.Get("Instruments", "PathSH", ""));
    const std::string SZ_FILE = std::move(config_.Get("Instruments", "PathSZ", ""));
    const std::string SH_ID = "SSE";
    const std::string SZ_ID = "SZE";

    subscribe_instruments_in_file_(SH_FILE, SH_ID);
    subscribe_instruments_in_file_(SH_FILE, SZ_ID);
  } else {
    common::Logger::t_err("Login failed: %s(errno: %d)\n", pRspInfo->ErrorMsg,
           pRspInfo->ErrorID);
  }
}

// 订阅回复
void LtsMdSpi::OnRspSubL2MarketData(
    CSecurityFtdcSpecificInstrumentField *pSpecificInstrument,
    CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
    if (bIsLast) {
      common::Logger::t_out("Subscribe to instruments (data) succeed.\n");
    }
  } else {
    common::Logger::t_err("Subscribe market data failed: %s(errno: %d)\n", pRspInfo->ErrorMsg,
           pRspInfo->ErrorID);
  }
}

void LtsMdSpi::OnRspSubL2Index(
    CSecurityFtdcSpecificInstrumentField *pSpecificInstrument,
    CSecurityFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
  if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
    if (bIsLast) {
      common::Logger::t_out("Subscribe to instruments (index) succeed.\n");
    }
  } else {
    common::Logger::t_err("Subscribe market index failed: %s(errno: %d)\n", pRspInfo->ErrorMsg,
           pRspInfo->ErrorID);
  }
}

void LtsMdSpi::OnRspSubL2OrderAndTrade(CSecurityFtdcRspInfoField *pRspInfo,
                                       int nRequestID, bool bIsLast) {
  if (pRspInfo == nullptr || pRspInfo->ErrorID == 0) {
    if (bIsLast) {
      common::Logger::t_out("Subscribe to instruments of (order) succeed.\n");
    }
  } else {
    common::Logger::t_err("Subscribe market order failed: %s(errno: %d)\n", pRspInfo->ErrorMsg,
           pRspInfo->ErrorID);
  }
}

void LtsMdSpi::OnRtnL2MarketData(
    CSecurityFtdcL2MarketDataField *pL2MarketData) {
  // printf("ticker header size = %d\n", sizeof(h)); // 24
  writer_->write_market_data((const char *)pL2MarketData, sizeof(CSecurityFtdcL2MarketDataField), 1);
}

void LtsMdSpi::OnRtnL2Index(CSecurityFtdcL2IndexField *pL2Index) {
  // printf("ticker header size = %d\n", sizeof(h)); // 24
  writer_->write_market_data((const char *)pL2Index, sizeof(CSecurityFtdcL2IndexField), 2);
}

void LtsMdSpi::OnRtnL2Order(CSecurityFtdcL2OrderField *pL2Order) {
  // printf("ticker header size = %d\n", sizeof(h)); // 24
  writer_->write_market_data((const char *)pL2Order, sizeof(CSecurityFtdcL2OrderField), 3);
}

void LtsMdSpi::OnRtnL2Trade(CSecurityFtdcL2TradeField *pL2Trade) {
  // printf("ticker header size = %d\n", sizeof(h)); // 24
  writer_->write_market_data((const char *)pL2Trade, sizeof(CSecurityFtdcL2TradeField), 4);
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
  common::Logger::t_err("Disconnected from front server (reason: %d).\n\t"
        "Reconnecting...\n", reason);
  std::string addr = config_.Get("FrontServer", "Address", "");
  api_->RegisterFront((char *)addr.c_str());
}
