#include "StrategyRunner.h"

#ifndef TRADERCS4398_PARAMETEROPTIMIZE_H
#define TRADERCS4398_PARAMETEROPTIMIZE_H

//Going to loop through all possible outcomes and show best results
void parameterOptimize(Account& a, const vector<Bar> ps, const float fee=0){
    vector<signal_t> signalSeries;
    cout << a.getInitBalance() << endl;
    cout << "Sma Price Cross \n";
    cout << "i\tmoney\ttrades\n";
    int end = ps.size()/2;
    int bestI;
    int bestNumTrades = 0;
    float bestProfitPerTrades = 0,
          bestProft = 0;
    for(int i=2; i<ps.size()/2; ++i){
        a.setBalance(a.getInitBalance());
        signalSeries = strat::smaCross(ps, i);
        StrategyRunner sr(a, ps, signalSeries, fee);
        sr.runStrategy(false);
        if(a.getBalance() > a.getInitBalance()) {
            cout << i << "\t" << a.getBalance() << "\t" << sr.getNumTrades() << endl;
            float profitpertrades = a.getBalance() / sr.getNumTrades();
            if(profitpertrades > bestProfitPerTrades){
                bestProfitPerTrades = profitpertrades;
                bestI = i;
                bestProft = a.getBalance();
                bestNumTrades = sr.getNumTrades();
            }
        }
        if(i%(end/10)==0) cout << (int)(((float)i/(float)end)*100) << "%" << endl;
    }
    cout << "done" << endl;
    cout << "Best value: "<<bestI << " gave profit $" << bestProft << " with "<< bestNumTrades << " trades.\n";

}

#endif //TRADERCS4398_PARAMETEROPTIMIZE_H
