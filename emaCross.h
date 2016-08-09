//
// Created by eric on 8/6/16.
//

#ifndef TRADERCS4398_EMACROSS_H
#define TRADERCS4398_EMACROSS_H

#include <vector>
#include "Bar.h"
#include "enums.h"
#include "indicator.h"
#include <iostream>
#include <cassert>
using std::vector;
namespace strat {

    vector<signal_t> emaCross(const std::vector<Bar>& source, int length=1) {
        assert(length>0);
        vector<signal_t> signals; //will hold series of corresponding trade signals for input series
        signals.reserve(source.size()+1);

        for(auto i=source.begin(); i != source.begin()+length-1; ++i) signals.push_back(ERR);

        vector<float> emaSeries = indicator::ema(source, length);
        for(int i = length-1; i<source.size(); ++i){
            if(source.at(i).close > emaSeries.at(i)) signals.push_back(BUY);
            else if(source.at(i).close < emaSeries.at(i)) signals.push_back(SELL);
            else if(source.at(i).close == emaSeries.at(i)) signals.push_back(HOLD);
            else signals.push_back(ERR);
        }
        return signals;

    }
}

#endif //TRADERCS4398_EMACROSS_H
