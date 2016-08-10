//
// Created by eric on 8/7/16.
//

#ifndef TRADERCS4398_DOUBLEEMACROSS_H
#define TRADERCS4398_DOUBLEEMACROSS_H

#include <vector>
#include "Bar.h"
#include "enums.h"
#include "indicator.h"
#include <iostream>
#include <cassert>
using std::vector;
namespace strat {

    vector<signal_t> doubleEmaCross(const std::vector<Bar>& source, unsigned fastLen = 1, unsigned slowLen =2){
        assert(fastLen > 0);
        assert(slowLen > 0);
        assert(fastLen < slowLen);

        vector<signal_t> signals;
        signals.reserve(source.size()+1);

        int longestLength = slowLen;


        vector<float> slowEma = indicator::ema(source, slowLen);
        vector<float> fastEma = indicator::ema(source, fastLen);

        assert(slowEma.size() == fastEma.size());
        assert(slowEma.size() == source.size());

        for(int i=0; i<longestLength-1; ++i) signals.push_back(ERR);
        for(int i = longestLength-1; i<source.size(); ++i){
            if(fastEma[i]==-1 || slowEma[i]==-1) exit(-1);
            if(fastEma.at(i) > slowEma.at(i)) signals.push_back(BUY);
            else if(fastEma.at(i) < slowEma.at(i)) signals.push_back(SELL);
            else if(fastEma.at(i) == slowEma.at(i)) signals.push_back(HOLD);
            //else signals.push_back(ERR);
            else std::cout<<"err2\n ";
        }
        return signals;

    }
}

#endif //TRADERCS4398_DOUBLEEMACROSS_H
