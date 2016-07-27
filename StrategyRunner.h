#ifndef TRADERCS4398_STRATEGYRUNNER_H
#define TRADERCS4398_STRATEGYRUNNER_H

#include <vector>
#include "signal_t.h"
#include "Bar.h"

//delete this after I get the real account class
class Account{
public:
    float initialBalance, equity;
};


//throw everything into one file and one definition #yolo
class StrategyRunner{
    using std::vector;
private:
    Account account;
    float commission;
    vector<Bar>
public:
    StrategyRunner(){}

    void marketOrder(signal_t signal){
        if(signal == BUY){}
        else if(signal == SELL){}
        else if(signal == HOLD){}
        else {} //ERR

    }
    void setAccount(const Account &a) {
        StrategyRunner::account = a;
        // or use this->account = a ?
    }

    void setCommission(float commission) {
        StrategyRunner::commission = commission;
    }

};


#endif //TRADERCS4398_STRATEGYRUNNER_H
