// Buy when fast average crosses above slow average

#ifndef TRADERCS4398_DOUBLESMACROSS_H
#define TRADERCS4398_DOUBLESMACROSS_H
namespace strat {
    vector <signal_t> doubleSmaCross(const std::vector <Bar> &source, unsigned fastLen = 1, unsigned slowLen =2) {
        assert(fastLen > 0);
        assert(slowLen > 0);
        assert(fastLen < slowLen);

        int longestLength = slowLen;

        vector <signal_t> signals;
        signals.reserve(source.size() + 1);

        for (auto i = source.begin(); i != source.end(); ++i) {
            if (i - source.begin() < longestLength-1) signals.push_back(ERR); //test speed of moving this out
            else {
                float slowSma = indicator::sma(source, i, slowLen);
                float fastSma = indicator::sma(source, i, fastLen);

                if (fastSma > slowSma) signals.push_back(BUY);
                else if (fastSma < slowSma) signals.push_back(SELL);
                else if (fastSma == slowSma) signals.push_back(HOLD);
                else signals.push_back(ERR); //Should never be reached. Compare speed of omitting instead.
            }
        }
        return signals;

    }
}

#endif //TRADERCS4398_DOUBLESMACROSS_H
