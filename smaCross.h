//
// Strategy: Buy when source price crosses above simple moving average
//

#ifndef TRADERCS4398_SMACROSS_H
#define TRADERCS4398_SMACROSS_H

#include <vector>
#include "Bar.h"        //include the Bar struct. Bad practice to include in a header file?
#include "sma.h"        //todo: make SMA function

#include <iostream>
#include <algorithm>

enum signal_t {SELL = -1, BUY = 1, HOLD = 0, ERR = -2};
enum ohlc_t {open=Bar.open, high=Bar.high, low=Bar.low, close=Bar.close};   //close most often used

//  Function smaCross
//  series: the entire vector of Bars, each bar containing 1 unit of price data
//  source: which price point to base calculations on: open, high, low, or close
//  length: how far back the SMA looks when calculating average


signal_t smaCross(const std::vector<Bar>& series, ohlc_t source, int length){
    // ... if the SMA length is 50 bars, we can't begin calculation until the 50th bar
    // ... so some code goes here to start the for loop at some length
    // ... if two parameters are given, the longest length will be the one to consider
    int longestLength = length;

    using std::begin; using std::end; using std::next;
    std::for_each(next(begin(series), longestLength), end(series), [](auto&& i) {
         });       //use at() for debugging, but operator [] is faster

    return ERR;
}

#endif //TRADERCS4398_SMACROSS_H
