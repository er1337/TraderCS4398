//
// Created by eric on 7/26/16.
//

#ifndef TRADERCS4398_STRATEGYRUNNER_H
#define TRADERCS4398_STRATEGYRUNNER_H

//delete this after I get the real account class
class Account{
public:
    float initialBalance, equity;
};


//throw everything into one file and one definition #yolo
class StrategyRunner{
private:
    Account a;
    float commission;
public:
    StrategyRunner(){}

    void marketOrder(signal_t){

    }
    void setA(const Account &a) {
        StrategyRunner::a = a;
    }

    void setCommission(float commission) {
        StrategyRunner::commission = commission;
    }

};


#endif //TRADERCS4398_STRATEGYRUNNER_H
