#include "StrategyRunner.h"

#ifndef TRADERCS4398_PARAMETEROPTIMIZE_H
#define TRADERCS4398_PARAMETEROPTIMIZE_H
#include <iomanip>

//Going to loop through all possible outcomes and show best results
void parameterOptimize(Account& a, const vector<Bar> ps, const float fee=0){
    vector<signal_t> signalSeries;
    float initBalance = a.getInitBalance();
    cout << initBalance << endl;
    cout << "Double EMA Cross \n";
    cout << "i\tmoney\ttrades\n";
    int end = ps.size()/2;
    int bestI, bestK;
    int bestNumTrades = 0;
    float bestProfitPerTrades = 0,
          bestProft = 0;
    int upperBound = ps.size()/2;
    for(int i=2; i<upperBound; ++i){
      int kUpperBound = 0.9*i;
      //for(int k=2; k<i-10; ++k){
      for(int k=2; k<i-10; k+=20){
        a.setBalance(a.getInitBalance());
        signalSeries = strat::doubleEmaCross(ps, k, i);
        StrategyRunner sr(a, ps, signalSeries, fee);
        sr.runStrategy(false);
        if(a.getBalance() > initBalance) {
            cout << i << "," << k << setw(10) << a.getBalance() << setw(10) << sr.getNumTrades() << endl;
            float profitpertrades = a.getBalance() / sr.getNumTrades();
            if(profitpertrades > bestProfitPerTrades){
                bestProfitPerTrades = profitpertrades;
                bestI = i;
                bestK = k;
                bestProft = a.getBalance();
                bestNumTrades = sr.getNumTrades();
            }
        }
      }
      if(i%(end/10)==0) cout << (int)(((float)i/(float)end)*100) << "%" << endl;
    }
    cout << "done" << endl;
    cout << "Best i: "<<bestI <<" k: "<<bestK << " gave profit $" << bestProft << " with "<< bestNumTrades << " trades.\n";

}

#endif //TRADERCS4398_PARAMETEROPTIMIZE_H
