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
    Account& account;
    float commission = 0;
    int numShares = 0, numTrades = 0;
    bool isLong = false;
    bool isShort = false;
    float shortEntryPrice = 0;
    float equity;
    float maxDrawDown = 0;
    float maxPeakBalance = 0;
    float lowestLowSincePeak = 0;
    float lowestLow = 0;
    float currentLow=0;
    vector<Bar> priceSeries;
    vector<signal_t> orderSignals;
    bool printOutput = true;

    // todo: bool to long, short, or both
public:
    StrategyRunner(Account& a, const vector<Bar> ps, const vector<signal_t> os, const float fee, bool po=true):
            account(a), priceSeries(ps), orderSignals(os), commission(fee),
            maxPeakBalance(a.getBalance()), lowestLowSincePeak(a.getBalance()), lowestLow(a.getBalance()),
            printOutput(po){}

    float getEquity() const {
        return equity;
    }
    float getNumTrades() const {
        return numTrades;
    }
    int getNumShares() const {
        return numShares;
    }
    void setAccount(const Account &a) {
        account = a;
        // or use this->account = a ?
    }

    void setCommission(float comm) {
        commission = comm;
    }

    //todo: make it work better with Account class and Stock class
    void marketOrder(signal_t signal, float orderPrice){ // try seperate fuctions

        if(!isLong && signal == BUY){
//            if(isShort){
//                float shortExitDifference = shortEntryPrice - orderPrice;
//                float shortTotal = shortExitDifference * numShares;
//                numShares = 0;
//                account.setBalance(account.getBalance() + shortTotal);
//            }

            //Take fee out first
            account.setBalance(account.getBalance()-commission);

            numShares = account.getBalance() / orderPrice; //integer division to round down
            float totalPrice = numShares * orderPrice;
            account.setBalance(account.getBalance() - totalPrice);  //do it locally faster if its just going to run all at once
            isLong = true;

            equity = account.getBalance() + totalPrice;
            if(printOutput) cout << "BUY "<<"\tat\t"<< orderPrice<<"\tequity="<<equity<<endl;
        }
        else if(signal == SELL){
            if(isLong){
                isLong = false;
                float sellTotal = numShares * orderPrice;
                numShares = 0;
                account.setBalance(account.getBalance() + sellTotal - commission);
                equity = account.getBalance();
                if(printOutput) cout << "SELL "<<"\tat\t"<< orderPrice<<"\tequity="<<equity<<endl;

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

        //Compute peak equity and max drawdown
        if(account.getBalance() > maxPeakBalance){
            maxPeakBalance = account.getBalance();
        }
        if(!isLong && !isShort && account.getBalance() < lowestLow){
            lowestLow = account.getBalance();
        }
        if(account.getBalance() < maxPeakBalance) currentLow = account.getBalance();
        float currentDrawDown = maxPeakBalance - currentLow;
        maxDrawDown = maxPeakBalance - lowestLow;
        if(currentDrawDown > maxDrawDown) maxDrawDown = currentDrawDown;

        ++numTrades;
    }

    void runStrategy(bool po=true){
        printOutput=po;

        equity = account.getBalance();
        if(priceSeries.size() != orderSignals.size())
            {cout << "size mismatch"; exit(1);} //todo: better error handling

        for(int i = 0; i < priceSeries.size(); i++)
            if(orderSignals[i] != ERR)
                if(orderSignals[i] == BUY || orderSignals[i]==SELL)
                    marketOrder(orderSignals[i], priceSeries[i].close);

        //now close any open positions after its done
        if(isLong) marketOrder(SELL, priceSeries[priceSeries.size()-1].close);
//        else if(isShort){
//            //close short
//            float shortExitDifference = shortEntryPrice - priceSeries[priceSeries.size()-1].close;
//            float shortTotal = shortExitDifference * numShares;
//            numShares = 0;
//            account.setBalance(account.getBalance() + shortTotal);
//        }
        //todo: separate print function
        if (printOutput) {
            cout << "\n\n===============================" <<endl;
            cout << "Initial Balance: "<< account.getInitBalance() <<endl;
            cout << "Final Balance: "<< account.getBalance() <<endl;
            cout << "Peak Balance: "<< maxPeakBalance <<endl;
            cout << "Lowest Balance: "<< lowestLow <<endl;
            cout << "Max Drawdown: "<< maxDrawDown <<endl;
            cout << "Profit %: "<< int((account.getBalance() / account.getInitBalance())*100)-100 <<endl;
        }

    }

};


#endif //TRADERCS4398_STRATEGYRUNNER_H
