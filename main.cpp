#include <iostream>
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
    bar2.close=2;

    vector<Bar> bars = {bar1, bar2};

    bars[1].close;
    bars.at(1);

    strat::smaCross(bars, 0);


    return 0;
}