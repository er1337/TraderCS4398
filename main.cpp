#include <iostream>
#include <vector>
#include "Bar.h"
#include "smaCross.h"
#include "Menus.h"
#include "processCSV.h"
#include "StrategyRunner.h"

using namespace std;

int main() {
    #ifdef WINDOWS
        std::system("title Trader");
    #endif


    Menus menusystem;
    menuAction_t menuAction = menusystem.runMenuMain();

    string infile; char delimiter; bool ignoreHeader;
    menusystem.getCSVparameters(infile, delimiter, ignoreHeader);

    processCSV parser;
    parser.setPath(infile);
    parser.setDelimiter(delimiter);
    parser.setIgnoreHeader(ignoreHeader);
    vector<Bar> series;
    series = parser.returnBarVector();

    int strategychoice; float commission; int movingavglength;
    menusystem.getStrategyParameters(strategychoice, movingavglength, commission);

    switch (menuAction){
        case runStrategy:
            cout << "running strategy...\n";
            //dont cram all this in here
            Stock s;
            map<string, Stock> m = {{"STOK", s}};
            Account a ("JP Morgan", 1000, m);
            vector<signal_t> orderSignals = strat::smaCross(series, movingavglength);

            StrategyRunner sr(&a, series, orderSignals, commission);
            sr.runStrategy();
//            cout << "\n\n\n===============================" <<endl;
//            cout << "Initial Balance: "<< a.getInitBalance() <<endl;
//            cout << "Final Balance: "<< a.getBalance() <<endl;
//            cout << "Profit %: "<< int((a.getBalance() / a.getInitBalance())*100) <<endl;
//            cin.get();
            break;
    }

    return 0;
}