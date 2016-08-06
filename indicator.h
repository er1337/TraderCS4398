#ifndef TRADERCS4398_INDICATOR_H
#define TRADERCS4398_INDICATOR_H
#include "Bar.h"
#include <vector>
namespace indicator{
    // Returns simple moving average based on close
    float sma(const std::vector<Bar> &series, std::vector<Bar>::const_iterator end, int length = 1) {
        //todo: error if length > begin + end
        if (length == 1) return end->close;  //moving average of length 1 always same as original price

        float sum = 0;
		//replace with auto?
        for(std::vector<Bar>::const_iterator i = end; i != (end - length); --i){
            sum += i->close;
        }
        return sum /  length;
    }

    // Returns exponential moving average based on close
    //todo: implement this correctly
    // Returns simple moving average based on close
    static float ema(const std::vector<Bar> &series, std::vector<Bar>::const_iterator end, int length = 1) {
        if (length == 1) return end->close;  //moving average of length 1 always same as original price

        //float sma = sma(series, end, length);
        //replace with auto?
        for(std::vector<Bar>::const_iterator i = end; i != (end - length); --i){

        }
        return length;
    }
}

#endif //TRADERCS4398_INDICATOR_H
