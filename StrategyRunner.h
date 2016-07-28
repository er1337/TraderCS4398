#ifndef TRADERCS4398_STRATEGYRUNNER_H
#define TRADERCS4398_STRATEGYRUNNER_H

#include <vector>
#include "enums.h"
#include "Bar.h"
#include "Account.h"

using std::vector;

//throw everything into one file and one definition #yolo
class StrategyRunner{
private:
    Account account;
    float commission = 0;
    int numShares = 0;
    bool isLong = false;
    bool isShort = false;
    float shortEntryPrice = 0;
    float equity;
    vector<Bar> priceSeries;
    vector<signal_t> orderSignals;

    // todo: bool to long, short, or both
public:
    StrategyRunner(Account & a, const vector<Bar> ps, const vector<signal_t> os, const float fee):
            account(a), priceSeries(ps), orderSignals(os), commission(fee) {}

    //todo: make it work better with Account class and Stock class
    void marketOrder(signal_t signal, float orderPrice){
        //todo: consider commission

        if(isLong == false && signal == BUY){
//            if(isShort){
//                float shortExitDifference = shortEntryPrice - orderPrice;
//                float shortTotal = shortExitDifference * numShares;
//                numShares = 0;
//                account.setBalance(account.getBalance() + shortTotal);
//            }
            numShares = account.getBalance() / orderPrice; //integer division to round down
            float totalPrice = numShares * orderPrice;
            account.setBalance(account.getBalance() - totalPrice);  //do it locally faster if its just going to run all at once
            isLong = true;

            equity = account.getBalance() + totalPrice;
            cout << "BUY "<< numShares<<"\tat\t"<< orderPrice<<"\tequity="<<equity<<endl;
        }
        else if(signal == SELL){
            if(isLong){
                isLong = false;
                float sellTotal = numShares * orderPrice;
                numShares = 0;
                account.setBalance(account.getBalance() + sellTotal);
                equity = account.getBalance();
                cout << "SELL "<<"\tat\t"<< orderPrice<<"\tequity="<<equity<<endl;

            }
//            float balance = account.getBalance();
//            numShares = balance / orderPrice; //integer division to round down
//            float totalPrice = numShares * orderPrice;
//            account.setBalance(balance - totalPrice);
//
//            isShort = true;
//            shortEntryPrice = orderPrice;
        }
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
    void runStrategy(){
        equity = account.getBalance();
        if(priceSeries.size() != orderSignals.size())
            {cout << "size mismatch"; exit(1);} //todo: better error handling

        for(int i = 0; i < priceSeries.size(); i++)
            if(orderSignals[i] != ERR)
                if(orderSignals[i] == BUY || orderSignals[i]==SELL)
                    marketOrder(orderSignals[i], priceSeries[i].close);

        //now close any open positions after its done
        if(isLong){
            //close long
            float sellTotal = numShares * priceSeries[priceSeries.size()-1].close;
            numShares = 0;
            account.setBalance(account.getBalance() + sellTotal);
        }
//        else if(isShort){
//            //close short
//            float shortExitDifference = shortEntryPrice - priceSeries[priceSeries.size()-1].close;
//            float shortTotal = shortExitDifference * numShares;
//            numShares = 0;
//            account.setBalance(account.getBalance() + shortTotal);
//        }

        cout << "\n\n===============================" <<endl;
        cout << "Initial Balance: "<< account.getInitBalance() <<endl;
        cout << "Final Balance: "<< account.getBalance() <<endl;
        cout << "Profit %: "<< int((account.getBalance() / account.getInitBalance())*100) <<endl;

    }

};


#endif //TRADERCS4398_STRATEGYRUNNER_H
