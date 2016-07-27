//
// Strategy: Buy when source price crosses above simple moving average
//

#ifndef TRADERCS4398_SMACROSS_H
#define TRADERCS4398_SMACROSS_H

#include <vector>
#include "Bar.h"
#include "signal_t.h"
#include "indicator.h"
#include <iostream>
#include <cassert>
#include <vector>
using std::vector;
namespace strat {


    //  Function smaCross
    //  series: the entire vector of Bars, each bar containing 1 unit of price data
    //  length: how far back the SMA looks when calculating average
    //  returns:  BUY when source crosses above sma, SELL when below, else hold

    vector<signal_t> smaCross(const std::vector<Bar>& series, int length=1) {
        assert(length>0);
        // ... if the SMA length is 50 bars, we can't begin calculation until the 50th bar
        // ... so some code goes here to start the for loop at that length
        // ... if 2+ parameters are given, the longest length will be the one to consider
        int longestLength = length;

        //using std::begin; using std::end; using std::next;
        //std::for_each(next(begin(series), longestLength), end(series), [](auto&& i) {
        //     });
		
		//can use auto?

        vector<signal_t> signals; //will hold series of corresponding trade signals for input series

        for(auto i=series.begin(); i != series.end(); ++i) {
            if (i - series.begin() < longestLength) signals.push_back(ERR);
            else {
                float sma = indicator::sma(series, i, length);
                if (i->close > sma) signals.push_back(BUY);
                else if (i->close < sma) signals.push_back(SELL);
                else signals.push_back(HOLD);
            }
        }
        return signals;

    }
}



#endif //TRADERCS4398_SMACROSS_H
