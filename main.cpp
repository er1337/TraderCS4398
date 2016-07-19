#include <iostream>
#include <vector>
#include "Bar.h"
#include "smaCross.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    Bar bar1;
    bar1.close=1;
    Bar bar2;
    bar2.close=2;

    vector<Bar> bars = {bar1, bar2};

    strat::smaCross(bars, 0);


    return 0;
}