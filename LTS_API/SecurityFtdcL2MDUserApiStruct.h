/////////////////////////////////////////////////////////////////////////
///@company shanghai liber information Technology Co.,Ltd
///@file SecurityFtdcL2MDUserApiStruct.h
///@brief 定义业务数据结构
/////////////////////////////////////////////////////////////////////////

#if !defined(SECURITY_L2MD_FTDCSTRUCT_H)
#define SECURITY_L2MD_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SecurityFtdcL2MDUserApiDataType.h"

_LTS_NS_BEGIN_

#pragma pack(push)
#pragma pack(1)

///响应信息
struct CSecurityFtdcRspInfoField
{
	///错误代码
	TSecurityFtdcErrorIDType	ErrorID;
	///错误信息
	TSecurityFtdcErrorMsgType	ErrorMsg;
};

///用户登录信息
struct CSecurityFtdcUserLoginField
{
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///密码
	TSecurityFtdcPasswordType	Password;
	///行情数据等级
	TSecurityFtdcDataLevelType	DataLevel;
};

///用户登出信息
struct CSecurityFtdcUserLogoutField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
};

///指定的合约
struct CSecurityFtdcSpecificInstrumentField
{
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
};

///Level2行情
struct CSecurityFtdcL2MarketDataField
{
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///时间戳
	TSecurityFtdcTimeType	TimeStamp;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///昨收盘价
	TSecurityFtdcPriceType	PreClosePrice;
	///今开盘价
	TSecurityFtdcPriceType	OpenPrice;
	///收盘价
	TSecurityFtdcPriceType	ClosePrice;
	///净值估值
	TSecurityFtdcPriceType	IOPV;
	///到期收益率
	TSecurityFtdcRatioType	YieldToMaturity;
	///动态参考价格
	TSecurityFtdcPriceType	AuctionPrice;
	///交易阶段
	TSecurityFtdcTradingPhaseType	TradingPhase;
	///开仓限制
	TSecurityFtdcOpenRestrictionType	OpenRestriction;
	///最高价
	TSecurityFtdcPriceType	HighPrice;
	///最低价
	TSecurityFtdcPriceType	LowPrice;
	///最新价
	TSecurityFtdcPriceType	LastPrice;
	///成交笔数
	TSecurityFtdcLargeVolumeType	TradeCount;
	///成交总量
	TSecurityFtdcLargeVolumeType	TotalTradeVolume;
	///成交总金额
	TSecurityFtdcMoneyType	TotalTradeValue;
	///持仓量
	TSecurityFtdcLargeVolumeType	OpenInterest;
	///委托买入总量
	TSecurityFtdcLargeVolumeType	TotalBidVolume;
	///加权平均委买价
	TSecurityFtdcPriceType	WeightedAvgBidPrice;
	///债券加权平均委买价
	TSecurityFtdcPriceType	AltWeightedAvgBidPrice;
	///委托卖出总量
	TSecurityFtdcLargeVolumeType	TotalOfferVolume;
	///加权平均委卖价
	TSecurityFtdcPriceType	WeightedAvgOfferPrice;
	///债券加权平均委卖价格
	TSecurityFtdcPriceType	AltWeightedAvgOfferPrice;
	///买价深度
	TSecurityFtdcPriceLevelType	BidPriceLevel;
	///卖价深度
	TSecurityFtdcPriceLevelType	OfferPriceLevel;
	///申买价一
	TSecurityFtdcPriceType	BidPrice1;
	///申买量一
	TSecurityFtdcLargeVolumeType	BidVolume1;
	///实际买总委托笔数一
	TSecurityFtdcVolumeType	BidCount1;
	///申买价二
	TSecurityFtdcPriceType	BidPrice2;
	///申买量二
	TSecurityFtdcLargeVolumeType	BidVolume2;
	///实际买总委托笔数二
	TSecurityFtdcVolumeType	BidCount2;
	///申买价三
	TSecurityFtdcPriceType	BidPrice3;
	///申买量三
	TSecurityFtdcLargeVolumeType	BidVolume3;
	///实际买总委托笔数三
	TSecurityFtdcVolumeType	BidCount3;
	///申买价四
	TSecurityFtdcPriceType	BidPrice4;
	///申买量四
	TSecurityFtdcLargeVolumeType	BidVolume4;
	///实际买总委托笔数四
	TSecurityFtdcVolumeType	BidCount4;
	///申买价五
	TSecurityFtdcPriceType	BidPrice5;
	///申买量五
	TSecurityFtdcLargeVolumeType	BidVolume5;
	///实际买总委托笔数五
	TSecurityFtdcVolumeType	BidCount5;
	///申买价六
	TSecurityFtdcPriceType	BidPrice6;
	///申买量六
	TSecurityFtdcLargeVolumeType	BidVolume6;
	///实际买总委托笔数六
	TSecurityFtdcVolumeType	BidCount6;
	///申买价七
	TSecurityFtdcPriceType	BidPrice7;
	///申买量七
	TSecurityFtdcLargeVolumeType	BidVolume7;
	///实际买总委托笔数七
	TSecurityFtdcVolumeType	BidCount7;
	///申买价八
	TSecurityFtdcPriceType	BidPrice8;
	///申买量八
	TSecurityFtdcLargeVolumeType	BidVolume8;
	///实际买总委托笔数八
	TSecurityFtdcVolumeType	BidCount8;
	///申买价九
	TSecurityFtdcPriceType	BidPrice9;
	///申买量九
	TSecurityFtdcLargeVolumeType	BidVolume9;
	///实际买总委托笔数九
	TSecurityFtdcVolumeType	BidCount9;
	///申买价十
	TSecurityFtdcPriceType	BidPriceA;
	///申买量十
	TSecurityFtdcLargeVolumeType	BidVolumeA;
	///实际买总委托笔数十
	TSecurityFtdcVolumeType	BidCountA;
	///申卖价一
	TSecurityFtdcPriceType	OfferPrice1;
	///申卖量一
	TSecurityFtdcLargeVolumeType	OfferVolume1;
	///实际卖总委托笔数一
	TSecurityFtdcVolumeType	OfferCount1;
	///申卖价二
	TSecurityFtdcPriceType	OfferPrice2;
	///申卖量二
	TSecurityFtdcLargeVolumeType	OfferVolume2;
	///实际卖总委托笔数二
	TSecurityFtdcVolumeType	OfferCount2;
	///申卖价三
	TSecurityFtdcPriceType	OfferPrice3;
	///申卖量三
	TSecurityFtdcLargeVolumeType	OfferVolume3;
	///实际卖总委托笔数三
	TSecurityFtdcVolumeType	OfferCount3;
	///申卖价四
	TSecurityFtdcPriceType	OfferPrice4;
	///申卖量四
	TSecurityFtdcLargeVolumeType	OfferVolume4;
	///实际卖总委托笔数四
	TSecurityFtdcVolumeType	OfferCount4;
	///申卖价五
	TSecurityFtdcPriceType	OfferPrice5;
	///申卖量五
	TSecurityFtdcLargeVolumeType	OfferVolume5;
	///实际卖总委托笔数五
	TSecurityFtdcVolumeType	OfferCount5;
	///申卖价六
	TSecurityFtdcPriceType	OfferPrice6;
	///申卖量六
	TSecurityFtdcLargeVolumeType	OfferVolume6;
	///实际卖总委托笔数六
	TSecurityFtdcVolumeType	OfferCount6;
	///申卖价七
	TSecurityFtdcPriceType	OfferPrice7;
	///申卖量七
	TSecurityFtdcLargeVolumeType	OfferVolume7;
	///实际卖总委托笔数七
	TSecurityFtdcVolumeType	OfferCount7;
	///申卖价八
	TSecurityFtdcPriceType	OfferPrice8;
	///申卖量八
	TSecurityFtdcLargeVolumeType	OfferVolume8;
	///实际卖总委托笔数八
	TSecurityFtdcVolumeType	OfferCount8;
	///申卖价九
	TSecurityFtdcPriceType	OfferPrice9;
	///申卖量九
	TSecurityFtdcLargeVolumeType	OfferVolume9;
	///实际卖总委托笔数九
	TSecurityFtdcVolumeType	OfferCount9;
	///申卖价十
	TSecurityFtdcPriceType	OfferPriceA;
	///申卖量十
	TSecurityFtdcLargeVolumeType	OfferVolumeA;
	///实际卖总委托笔数十
	TSecurityFtdcVolumeType	OfferCountA;
	///行情类别
	TSecurityFtdcMDStreamIDType	MDStreamID;
	///合约状态
	TSecurityFtdcInstrumentStatusType	InstrumentStatus;
	///昨净值估值
	TSecurityFtdcPriceType	PreIOPV;
	///市盈率一
	TSecurityFtdcRatioType	PERatio1;
	///市盈率二
	TSecurityFtdcRatioType	PERatio2;
	///涨停价
	TSecurityFtdcPriceType	UpperLimitPrice;
	///跌停价
	TSecurityFtdcPriceType	LowerLimitPrice;
	///权证溢价率
	TSecurityFtdcRatioType	WarrantPremiumRatio;
	///权证执行总数量
	TSecurityFtdcLargeVolumeType	TotalWarrantExecQty;
	///升跌一
	TSecurityFtdcPriceType	PriceDiff1;
	///升跌二
	TSecurityFtdcPriceType	PriceDiff2;
	///ETF申购笔数
	TSecurityFtdcLargeVolumeType	ETFBuyNumber;
	///ETF申购数量
	TSecurityFtdcLargeVolumeType	ETFBuyAmount;
	///ETF申购金额
	TSecurityFtdcMoneyType	ETFBuyMoney;
	///ETF赎回笔数
	TSecurityFtdcLargeVolumeType	ETFSellNumber;
	///ETF赎回数量
	TSecurityFtdcLargeVolumeType	ETFSellAmount;
	///ETF赎回金额
	TSecurityFtdcMoneyType	ETFSellMoney;
	///买入撤单笔数
	TSecurityFtdcLargeVolumeType	WithdrawBuyNumber;
	///买入撤单数量
	TSecurityFtdcLargeVolumeType	WithdrawBuyAmount;
	///买入撤单金额
	TSecurityFtdcMoneyType	WithdrawBuyMoney;
	///买入总笔数
	TSecurityFtdcLargeVolumeType	TotalBidNumber;
	///买入委托成交最大等待时间
	TSecurityFtdcLargeVolumeType	BidTradeMaxDuration;
	///买方委托价位数
	TSecurityFtdcLargeVolumeType	NumBidOrders;
	///卖出撤单笔数
	TSecurityFtdcLargeVolumeType	WithdrawSellNumber;
	///卖出撤单数量
	TSecurityFtdcLargeVolumeType	WithdrawSellAmount;
	///卖出撤单金额
	TSecurityFtdcMoneyType	WithdrawSellMoney;
	///卖出总笔数
	TSecurityFtdcLargeVolumeType	TotalOfferNumber;
	///卖出委托成交最大等待时间
	TSecurityFtdcLargeVolumeType	OfferTradeMaxDuration;
	///卖方委托价位数
	TSecurityFtdcLargeVolumeType	NumOfferOrders;
};

///Level2行情更新时间属性
struct CSecurityFtdcL2UpdateTimeField
{
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///时间戳
	TSecurityFtdcTimeType	TimeStamp;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
};

///Level2行情静态属性
struct CSecurityFtdcL2StaticField
{
	///昨收盘价
	TSecurityFtdcPriceType	PreClosePrice;
	///今开盘价
	TSecurityFtdcPriceType	OpenPrice;
	///收盘价
	TSecurityFtdcPriceType	ClosePrice;
	///净值估值
	TSecurityFtdcPriceType	IOPV;
	///到期收益率
	TSecurityFtdcRatioType	YieldToMaturity;
	///动态参考价格
	TSecurityFtdcPriceType	AuctionPrice;
	///交易阶段
	TSecurityFtdcTradingPhaseType	TradingPhase;
	///开仓限制
	TSecurityFtdcOpenRestrictionType	OpenRestriction;
};

///Level2行情价格区间属性
struct CSecurityFtdcL2PriceIntervalField
{
	///最高价
	TSecurityFtdcPriceType	HighPrice;
	///最低价
	TSecurityFtdcPriceType	LowPrice;
};

///Level2行情基本信息
struct CSecurityFtdcL2BaseField
{
	///最新价
	TSecurityFtdcPriceType	LastPrice;
};

///Level2成交信息
struct CSecurityFtdcL2TradedField
{
	///成交笔数
	TSecurityFtdcLargeVolumeType	TradeCount;
	///成交总量
	TSecurityFtdcLargeVolumeType	TotalTradeVolume;
	///成交总金额
	TSecurityFtdcMoneyType	TotalTradeValue;
	///持仓量
	TSecurityFtdcLargeVolumeType	OpenInterest;
};

///Level2行情数据属性
struct CSecurityFtdcL2DataLevelField
{
	///价格
	TSecurityFtdcPriceType	Price;
	///数量
	TSecurityFtdcLargeVolumeType	Volume;
	///实际总委托笔数
	TSecurityFtdcVolumeType	Count;
};

///Level2委买信息
struct CSecurityFtdcL2BidOrderField
{
	///委托买入总量
	TSecurityFtdcLargeVolumeType	TotalBidVolume;
	///加权平均委买价
	TSecurityFtdcPriceType	WeightedAvgBidPrice;
	///债券加权平均委买价
	TSecurityFtdcPriceType	AltWeightedAvgBidPrice;
};

///Level2委卖信息
struct CSecurityFtdcL2OfferOrderField
{
	///委托卖出总量
	TSecurityFtdcLargeVolumeType	TotalOfferVolume;
	///加权平均委卖价
	TSecurityFtdcPriceType	WeightedAvgOfferPrice;
	///债券加权平均委卖价格
	TSecurityFtdcPriceType	AltWeightedAvgOfferPrice;
};

///Level2价格深度属性
struct CSecurityFtdcL2PriceLevelField
{
	///买价深度
	TSecurityFtdcPriceLevelType	BidPriceLevel;
	///卖价深度
	TSecurityFtdcPriceLevelType	OfferPriceLevel;
};

///Level2行情申买一属性
struct CSecurityFtdcL2Bid1Field
{
	///申买价一
	TSecurityFtdcPriceType	BidPrice1;
	///申买量一
	TSecurityFtdcLargeVolumeType	BidVolume1;
	///实际买总委托笔数一
	TSecurityFtdcVolumeType	BidCount1;
};

///Level2行情申卖一属性
struct CSecurityFtdcL2Offer1Field
{
	///申卖价一
	TSecurityFtdcPriceType	OfferPrice1;
	///申卖量一
	TSecurityFtdcLargeVolumeType	OfferVolume1;
	///实际卖总委托笔数一
	TSecurityFtdcVolumeType	OfferCount1;
};

///Level2行情申买二属性
struct CSecurityFtdcL2Bid2Field
{
	///申买价二
	TSecurityFtdcPriceType	BidPrice2;
	///申买量二
	TSecurityFtdcLargeVolumeType	BidVolume2;
	///实际买总委托笔数二
	TSecurityFtdcVolumeType	BidCount2;
};

///Level2行情申卖二属性
struct CSecurityFtdcL2Offer2Field
{
	///申卖价二
	TSecurityFtdcPriceType	OfferPrice2;
	///申卖量二
	TSecurityFtdcLargeVolumeType	OfferVolume2;
	///实际卖总委托笔数二
	TSecurityFtdcVolumeType	OfferCount2;
};

///Level2行情申买三属性
struct CSecurityFtdcL2Bid3Field
{
	///申买价三
	TSecurityFtdcPriceType	BidPrice3;
	///申买量三
	TSecurityFtdcLargeVolumeType	BidVolume3;
	///实际买总委托笔数三
	TSecurityFtdcVolumeType	BidCount3;
};

///Level2行情申卖三属性
struct CSecurityFtdcL2Offer3Field
{
	///申卖价三
	TSecurityFtdcPriceType	OfferPrice3;
	///申卖量三
	TSecurityFtdcLargeVolumeType	OfferVolume3;
	///实际卖总委托笔数三
	TSecurityFtdcVolumeType	OfferCount3;
};

///Level2行情申买四属性
struct CSecurityFtdcL2Bid4Field
{
	///申买价四
	TSecurityFtdcPriceType	BidPrice4;
	///申买量四
	TSecurityFtdcLargeVolumeType	BidVolume4;
	///实际买总委托笔数四
	TSecurityFtdcVolumeType	BidCount4;
};

///Level2行情申卖四属性
struct CSecurityFtdcL2Offer4Field
{
	///申卖价四
	TSecurityFtdcPriceType	OfferPrice4;
	///申卖量四
	TSecurityFtdcLargeVolumeType	OfferVolume4;
	///实际卖总委托笔数四
	TSecurityFtdcVolumeType	OfferCount4;
};

///Level2行情申买五属性
struct CSecurityFtdcL2Bid5Field
{
	///申买价五
	TSecurityFtdcPriceType	BidPrice5;
	///申买量五
	TSecurityFtdcLargeVolumeType	BidVolume5;
	///实际买总委托笔数五
	TSecurityFtdcVolumeType	BidCount5;
};

///Level2行情申卖五属性
struct CSecurityFtdcL2Offer5Field
{
	///申卖价五
	TSecurityFtdcPriceType	OfferPrice5;
	///申卖量五
	TSecurityFtdcLargeVolumeType	OfferVolume5;
	///实际卖总委托笔数五
	TSecurityFtdcVolumeType	OfferCount5;
};

///Level2行情申买六属性
struct CSecurityFtdcL2Bid6Field
{
	///申买价六
	TSecurityFtdcPriceType	BidPrice6;
	///申买量六
	TSecurityFtdcLargeVolumeType	BidVolume6;
	///实际买总委托笔数六
	TSecurityFtdcVolumeType	BidCount6;
};

///Level2行情申卖六属性
struct CSecurityFtdcL2Offer6Field
{
	///申卖价六
	TSecurityFtdcPriceType	OfferPrice6;
	///申卖量六
	TSecurityFtdcLargeVolumeType	OfferVolume6;
	///实际卖总委托笔数六
	TSecurityFtdcVolumeType	OfferCount6;
};

///Level2行情申买七属性
struct CSecurityFtdcL2Bid7Field
{
	///申买价七
	TSecurityFtdcPriceType	BidPrice7;
	///申买量七
	TSecurityFtdcLargeVolumeType	BidVolume7;
	///实际买总委托笔数七
	TSecurityFtdcVolumeType	BidCount7;
};

///Level2行情申卖七属性
struct CSecurityFtdcL2Offer7Field
{
	///申卖价七
	TSecurityFtdcPriceType	OfferPrice7;
	///申卖量七
	TSecurityFtdcLargeVolumeType	OfferVolume7;
	///实际卖总委托笔数七
	TSecurityFtdcVolumeType	OfferCount7;
};

///Level2行情申买八属性
struct CSecurityFtdcL2Bid8Field
{
	///申买价八
	TSecurityFtdcPriceType	BidPrice8;
	///申买量八
	TSecurityFtdcLargeVolumeType	BidVolume8;
	///实际买总委托笔数八
	TSecurityFtdcVolumeType	BidCount8;
};

///Level2行情申卖八属性
struct CSecurityFtdcL2Offer8Field
{
	///申卖价八
	TSecurityFtdcPriceType	OfferPrice8;
	///申卖量八
	TSecurityFtdcLargeVolumeType	OfferVolume8;
	///实际卖总委托笔数八
	TSecurityFtdcVolumeType	OfferCount8;
};

///Level2行情申买九属性
struct CSecurityFtdcL2Bid9Field
{
	///申买价九
	TSecurityFtdcPriceType	BidPrice9;
	///申买量九
	TSecurityFtdcLargeVolumeType	BidVolume9;
	///实际买总委托笔数九
	TSecurityFtdcVolumeType	BidCount9;
};

///Level2行情申卖九属性
struct CSecurityFtdcL2Offer9Field
{
	///申卖价九
	TSecurityFtdcPriceType	OfferPrice9;
	///申卖量九
	TSecurityFtdcLargeVolumeType	OfferVolume9;
	///实际卖总委托笔数九
	TSecurityFtdcVolumeType	OfferCount9;
};

///Level2行情申买十属性
struct CSecurityFtdcL2BidAField
{
	///申买价十
	TSecurityFtdcPriceType	BidPriceA;
	///申买量十
	TSecurityFtdcLargeVolumeType	BidVolumeA;
	///实际买总委托笔数十
	TSecurityFtdcVolumeType	BidCountA;
};

///Level2行情申卖十属性
struct CSecurityFtdcL2OfferAField
{
	///申卖价十
	TSecurityFtdcPriceType	OfferPriceA;
	///申卖量十
	TSecurityFtdcLargeVolumeType	OfferVolumeA;
	///实际卖总委托笔数十
	TSecurityFtdcVolumeType	OfferCountA;
};

///Level2行情申买属性
struct CSecurityFtdcL2BidField
{
	///申买价一
	TSecurityFtdcPriceType	BidPrice1;
	///申买量一
	TSecurityFtdcLargeVolumeType	BidVolume1;
	///实际买总委托笔数一
	TSecurityFtdcVolumeType	BidCount1;
	///申买价二
	TSecurityFtdcPriceType	BidPrice2;
	///申买量二
	TSecurityFtdcLargeVolumeType	BidVolume2;
	///实际买总委托笔数二
	TSecurityFtdcVolumeType	BidCount2;
	///申买价三
	TSecurityFtdcPriceType	BidPrice3;
	///申买量三
	TSecurityFtdcLargeVolumeType	BidVolume3;
	///实际买总委托笔数三
	TSecurityFtdcVolumeType	BidCount3;
	///申买价四
	TSecurityFtdcPriceType	BidPrice4;
	///申买量四
	TSecurityFtdcLargeVolumeType	BidVolume4;
	///实际买总委托笔数四
	TSecurityFtdcVolumeType	BidCount4;
	///申买价五
	TSecurityFtdcPriceType	BidPrice5;
	///申买量五
	TSecurityFtdcLargeVolumeType	BidVolume5;
	///实际买总委托笔数五
	TSecurityFtdcVolumeType	BidCount5;
	///申买价六
	TSecurityFtdcPriceType	BidPrice6;
	///申买量六
	TSecurityFtdcLargeVolumeType	BidVolume6;
	///实际买总委托笔数六
	TSecurityFtdcVolumeType	BidCount6;
	///申买价七
	TSecurityFtdcPriceType	BidPrice7;
	///申买量七
	TSecurityFtdcLargeVolumeType	BidVolume7;
	///实际买总委托笔数七
	TSecurityFtdcVolumeType	BidCount7;
	///申买价八
	TSecurityFtdcPriceType	BidPrice8;
	///申买量八
	TSecurityFtdcLargeVolumeType	BidVolume8;
	///实际买总委托笔数八
	TSecurityFtdcVolumeType	BidCount8;
	///申买价九
	TSecurityFtdcPriceType	BidPrice9;
	///申买量九
	TSecurityFtdcLargeVolumeType	BidVolume9;
	///实际买总委托笔数九
	TSecurityFtdcVolumeType	BidCount9;
	///申买价十
	TSecurityFtdcPriceType	BidPriceA;
	///申买量十
	TSecurityFtdcLargeVolumeType	BidVolumeA;
	///实际买总委托笔数十
	TSecurityFtdcVolumeType	BidCountA;
};

///Level2行情申卖属性
struct CSecurityFtdcL2OfferField
{
	///申卖价一
	TSecurityFtdcPriceType	OfferPrice1;
	///申卖量一
	TSecurityFtdcLargeVolumeType	OfferVolume1;
	///实际卖总委托笔数一
	TSecurityFtdcVolumeType	OfferCount1;
	///申卖价二
	TSecurityFtdcPriceType	OfferPrice2;
	///申卖量二
	TSecurityFtdcLargeVolumeType	OfferVolume2;
	///实际卖总委托笔数二
	TSecurityFtdcVolumeType	OfferCount2;
	///申卖价三
	TSecurityFtdcPriceType	OfferPrice3;
	///申卖量三
	TSecurityFtdcLargeVolumeType	OfferVolume3;
	///实际卖总委托笔数三
	TSecurityFtdcVolumeType	OfferCount3;
	///申卖价四
	TSecurityFtdcPriceType	OfferPrice4;
	///申卖量四
	TSecurityFtdcLargeVolumeType	OfferVolume4;
	///实际卖总委托笔数四
	TSecurityFtdcVolumeType	OfferCount4;
	///申卖价五
	TSecurityFtdcPriceType	OfferPrice5;
	///申卖量五
	TSecurityFtdcLargeVolumeType	OfferVolume5;
	///实际卖总委托笔数五
	TSecurityFtdcVolumeType	OfferCount5;
	///申卖价六
	TSecurityFtdcPriceType	OfferPrice6;
	///申卖量六
	TSecurityFtdcLargeVolumeType	OfferVolume6;
	///实际卖总委托笔数六
	TSecurityFtdcVolumeType	OfferCount6;
	///申卖价七
	TSecurityFtdcPriceType	OfferPrice7;
	///申卖量七
	TSecurityFtdcLargeVolumeType	OfferVolume7;
	///实际卖总委托笔数七
	TSecurityFtdcVolumeType	OfferCount7;
	///申卖价八
	TSecurityFtdcPriceType	OfferPrice8;
	///申卖量八
	TSecurityFtdcLargeVolumeType	OfferVolume8;
	///实际卖总委托笔数八
	TSecurityFtdcVolumeType	OfferCount8;
	///申卖价九
	TSecurityFtdcPriceType	OfferPrice9;
	///申卖量九
	TSecurityFtdcLargeVolumeType	OfferVolume9;
	///实际卖总委托笔数九
	TSecurityFtdcVolumeType	OfferCount9;
	///申卖价十
	TSecurityFtdcPriceType	OfferPriceA;
	///申卖量十
	TSecurityFtdcLargeVolumeType	OfferVolumeA;
	///实际卖总委托笔数十
	TSecurityFtdcVolumeType	OfferCountA;
};

///Level2指数行情
struct CSecurityFtdcL2IndexField
{
	///交易日
	TSecurityFtdcDateType	TradingDay;
	///行情时间（秒）
	TSecurityFtdcTimeType	TimeStamp;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///指数代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///前收盘指数
	TSecurityFtdcIndexType	PreCloseIndex;
	///今开盘指数
	TSecurityFtdcIndexType	OpenIndex;
	///今日收盘指数
	TSecurityFtdcIndexType	CloseIndex;
	///最高指数
	TSecurityFtdcIndexType	HighIndex;
	///最低指数
	TSecurityFtdcIndexType	LowIndex;
	///最新指数
	TSecurityFtdcIndexType	LastIndex;
	///参与计算相应指数的成交金额（元）
	TSecurityFtdcMoneyType	TurnOver;
	///参与计算相应指数的交易数量（手）
	TSecurityFtdcLargeVolumeType	TotalVolume;
	///行情类别
	TSecurityFtdcMDStreamIDType	MDStreamID;
};

///Level2行情用户信息
struct CSecurityFtdcL2UserInfoField
{
	///经纪公司代码
	TSecurityFtdcBrokerIDType	BrokerID;
	///用户代码
	TSecurityFtdcUserIDType	UserID;
	///用户名称
	TSecurityFtdcUserNameType	UserName;
	///密码
	TSecurityFtdcPasswordType	Password;
	///行情数据等级
	TSecurityFtdcDataLevelType	DataLevel;
	///股票最大订阅数量
	TSecurityFtdcVolumeType	MaxStockCount;
	///指数最大订阅数量
	TSecurityFtdcVolumeType	MaxIndexCount;
};

///UDP组播组信息
struct CSecurityFtdcMulticastGroupInfoField
{
	///组播组IP地址
	TSecurityFtdcIPAddressType	GroupIP;
	///组播组IP端口
	TSecurityFtdcIPPortType	GroupPort;
	///源地址
	TSecurityFtdcIPAddressType	SourceIP;
};

///Level2逐笔委托
struct CSecurityFtdcL2OrderField
{
	///委托组
	TSecurityFtdcGroupIDType	OrderGroupID;
	///委托序号
	TSecurityFtdcGroupNoType	OrderIndex;
	///委托时间（秒）
	TSecurityFtdcTimeType	OrderTime;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///委托价格
	TSecurityFtdcPriceType	Price;
	///委托数量
	TSecurityFtdcLargeVolumeType	Volume;
	///报单类型
	TSecurityFtdcOrderKindType	OrderKind;
	///功能码
	TSecurityFtdcFunctionCodeType	FunctionCode;
	///行情类别
	TSecurityFtdcMDStreamIDType	MDStreamID;
};

///Level2逐笔成交
struct CSecurityFtdcL2TradeField
{
	///成交组
	TSecurityFtdcGroupIDType	TradeGroupID;
	///成交序号
	TSecurityFtdcGroupNoType	TradeIndex;
	///买方委托序号
	TSecurityFtdcGroupNoType	BuyIndex;
	///卖方委托序号
	TSecurityFtdcGroupNoType	SellIndex;
	///成交时间（秒）
	TSecurityFtdcTimeType	TradeTime;
	///交易所代码
	TSecurityFtdcExchangeIDType	ExchangeID;
	///合约代码
	TSecurityFtdcInstrumentIDType	InstrumentID;
	///成交价格
	TSecurityFtdcPriceType	Price;
	///成交数量
	TSecurityFtdcLargeVolumeType	Volume;
	///报单类型
	TSecurityFtdcOrderKindType	OrderKind;
	///功能码
	TSecurityFtdcFunctionCodeType	FunctionCode;
	///内外盘标志
	TSecurityFtdcOrderBSFlagType	OrderBSFlag;
	///行情类别
	TSecurityFtdcMDStreamIDType	MDStreamID;
};

///Level2行情新增静态属性
struct CSecurityFtdcL2NewStaticField
{
	///行情类别
	TSecurityFtdcMDStreamIDType	MDStreamID;
	///合约状态
	TSecurityFtdcInstrumentStatusType	InstrumentStatus;
	///昨净值估值
	TSecurityFtdcPriceType	PreIOPV;
	///市盈率一
	TSecurityFtdcRatioType	PERatio1;
	///市盈率二
	TSecurityFtdcRatioType	PERatio2;
	///涨停价
	TSecurityFtdcPriceType	UpperLimitPrice;
	///跌停价
	TSecurityFtdcPriceType	LowerLimitPrice;
	///权证溢价率
	TSecurityFtdcRatioType	WarrantPremiumRatio;
	///权证执行总数量
	TSecurityFtdcLargeVolumeType	TotalWarrantExecQty;
};

///Level2行情升跌信息
struct CSecurityFtdcL2PriceDiffField
{
	///升跌一
	TSecurityFtdcPriceType	PriceDiff1;
	///升跌二
	TSecurityFtdcPriceType	PriceDiff2;
};

///Level2ETF申购信息
struct CSecurityFtdcL2ETFBuyInfoField
{
	///ETF申购笔数
	TSecurityFtdcLargeVolumeType	ETFBuyNumber;
	///ETF申购数量
	TSecurityFtdcLargeVolumeType	ETFBuyAmount;
	///ETF申购金额
	TSecurityFtdcMoneyType	ETFBuyMoney;
};

///Level2ETF赎回信息
struct CSecurityFtdcL2ETFSellInfoField
{
	///ETF赎回笔数
	TSecurityFtdcLargeVolumeType	ETFSellNumber;
	///ETF赎回数量
	TSecurityFtdcLargeVolumeType	ETFSellAmount;
	///ETF赎回金额
	TSecurityFtdcMoneyType	ETFSellMoney;
};

///Level2买入信息
struct CSecurityFtdcL2BuyInfoField
{
	///买入撤单笔数
	TSecurityFtdcLargeVolumeType	WithdrawBuyNumber;
	///买入撤单数量
	TSecurityFtdcLargeVolumeType	WithdrawBuyAmount;
	///买入撤单金额
	TSecurityFtdcMoneyType	WithdrawBuyMoney;
	///买入总笔数
	TSecurityFtdcLargeVolumeType	TotalBidNumber;
	///买入委托成交最大等待时间
	TSecurityFtdcLargeVolumeType	BidTradeMaxDuration;
	///买方委托价位数
	TSecurityFtdcLargeVolumeType	NumBidOrders;
};

///Level2卖出信息
struct CSecurityFtdcL2SellInfoField
{
	///卖出撤单笔数
	TSecurityFtdcLargeVolumeType	WithdrawSellNumber;
	///卖出撤单数量
	TSecurityFtdcLargeVolumeType	WithdrawSellAmount;
	///卖出撤单金额
	TSecurityFtdcMoneyType	WithdrawSellMoney;
	///卖出总笔数
	TSecurityFtdcLargeVolumeType	TotalOfferNumber;
	///卖出委托成交最大等待时间
	TSecurityFtdcLargeVolumeType	OfferTradeMaxDuration;
	///卖方委托价位数
	TSecurityFtdcLargeVolumeType	NumOfferOrders;
};


#pragma pack(pop)
_LTS_NS_END_

#endif
