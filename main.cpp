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
    bar2.close=2;
    Bar bar3;
    bar2.close=3;
    Bar bar4;
    bar2.close=4;
    Bar bar5;
    bar2.close=5;

    vector<Bar> bars = {bar1, bar2, bar3, bar4, bar5};

    bars[1].close;
    bars.at(1);

    strat::smaCross(bars, 0);


    return 0;
}