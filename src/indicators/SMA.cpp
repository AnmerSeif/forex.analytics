#include "../../include/indicators/Indicator.h"

INDICATOR(SMA15_SMA50)(const std::vector<Candlestick>& candlesticks, int* startIndex)
{
  std::vector<double> indicatorData = std::vector<double>();

  int outBeginIdx;
  int outNbElement;
  int optInTimePeriod1 = 15;
  int optInTimePeriod2 = 50;

  if (candlesticks.size() < optInTimePeriod1 ||
      candlesticks.size() < optInTimePeriod2) {
        return indicatorData;
  }

  //Initialize all required parameters
  this->PrepareParameters(candlesticks);

  //Perform the RSI calculation
  TA_SMA(
    this->startIdx,
    this->endIdx,
    this->inClose,
    optInTimePeriod1,
    &outBeginIdx,
    &outNbElement,
    this->outReal);

  TA_SMA(
    this->startIdx,
    this->endIdx,
    this->inClose,
    optInTimePeriod2,
    &outBeginIdx,
    &outNbElement,
    this->outReal2);

  //Put the result into indicator data vector in RsiModel
  for (int i = 0; i < outNbElement; i++) {
    indicatorData.push_back(outReal[i] - outReal2[i]);
  }

  *startIndex = outBeginIdx;

  //Cleanup all required parameters
  this->Clean();

  return indicatorData;
}
