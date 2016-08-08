#ifndef TRADERCS4398_INDICATOR_H
#define TRADERCS4398_INDICATOR_H
#include "Bar.h"
#include <vector>
#include <cassert>

namespace indicator{
    using std::vector;
    // Returns simple moving average based on close
    float sma(const vector<Bar> &series, vector<Bar>::const_iterator end, int length = 1) {
        if (length == 1) return end->close;  //moving average of length 1 always same as original price
        assert(length <= (end - series.begin())+1);

        float sum = 0;
		//replace with auto?
        for(vector<Bar>::const_iterator i = end; i != (end - length); --i){
            sum += i->close;
        }
        return sum /  length;
    }

    // Returns series of exponential moving averages based on close
    vector<float> ema(const std::vector<Bar> &source, int length = 1) {

        vector<float> emaSeries;
        emaSeries.reserve(source.size()+1);

        if (length == 1) for(auto i : source) emaSeries.push_back(i.close);
        else {
            for (int i = 0; i < length - 1; ++i) emaSeries.push_back(-1);

            //seed with close
            //emaSeries.push_back((source.begin() + emaSeries.size())->close);
            //seed with sma
            emaSeries.push_back(sma(source, source.begin()+length-1, length));

            float k = 2.0/(length+1);
            for (auto i = source.begin() + length; i != source.end(); ++i)
                emaSeries.push_back((i->close * k) + (*(emaSeries.end() - 1) * (1 - k)));
        }
        return emaSeries;
    }
    
    //
}

#endif //TRADERCS4398_INDICATOR_H
