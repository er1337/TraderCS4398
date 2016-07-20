//
// Strategy: Buy when source price crosses above simple moving average
//

#ifndef TRADERCS4398_SMACROSS_H
#define TRADERCS4398_SMACROSS_H

#include <vector>
#include "Bar.h"
//#include "sma.h"        //todo: make SMA function

#include <iostream>
#include <algorithm>
namespace strat {

    enum signal_t {
        SELL = -1, BUY = 1, HOLD = 0, ERR = -2
    };
    enum ohlc_t {
        open, high, low, close
    };

    //  Function smaCross
    //  series: the entire vector of Bars, each bar containing 1 unit of price data
    //  length: how far back the SMA looks when calculating average
    //  returns:  BUY when source crosses above sma, SELL when below, else hold

    signal_t smaCross(const std::vector<Bar>& series, int length) {
        // ... if the SMA length is 50 bars, we can't begin calculation until the 50th bar
        // ... so some code goes here to start the for loop at some length
        // ... if 2+ parameters are given, the longest length will be the one to consider
        int longestLength = length;

        //using std::begin; using std::end; using std::next;
        //std::for_each(next(begin(series), longestLength), end(series), [](auto&& i) {
        //     });

        for(std::vector<Bar>::const_iterator i = (series.begin()+longestLength); i != series.end(); ++i){
            std::cout << i->close;
        }

        return ERR;
    }
}



#endif //TRADERCS4398_SMACROSS_H
