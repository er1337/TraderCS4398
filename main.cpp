#include <iostream>

//temporary includes
#include <vector>
#include "Bar.h"
#include "smaCross.h"
#include "menus.h"

using namespace std;

int main() {
    #ifdef WINDOWS
        std::system("title Trader");
    #endif



    Bar bar1;
    bar1.close=1;
    Bar bar2;
    bar2.close=1;
    Bar bar3;
    bar3.close=2;
    Bar bar4;
    bar4.close=1;
    Bar bar5;
    bar5.close=1;

    vector<Bar> bars = {bar1,bar2,bar3,bar4,bar5};
    vector<strat::signal_t> smaCrossSignals;
    smaCrossSignals = strat::smaCross(bars, 2); //must call with at least 1
    for(auto i : smaCrossSignals) cout << i << endl;

    return 0;
}