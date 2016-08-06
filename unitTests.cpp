// Should be compiled as a standalone executable,
// which can be run with no arguments to run all tests.
// I didn't include testing of getter functions, because I think
//  the getters will be used to test the setters and other methods anyway
//
// Compile with: g++ -std=c++11 unitTests.cpp -o unitTests

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "indicator.h"
#include "smaCross.h"
#include "Stock.h"
#include "Account.h"
#include "Account.h"
#include "processCSV.h"

// Here's most of what we can test
/*
Indicators:
  sma, ema

Strategies:
    smaCross

Stock:
    subtractVolume

Account:
    addStock, removeStock (use stockExists to test)

processCSV:
    setPath, setDelimiter, setIgnoreHeader, size, returnBarVector

StrategyRunner:
    marketOrder (use getEquity and getNumShares to test)
*/

TEST_CASE("indicator values"){
    //setup vector of 10 Bars (date, o, h, l, c, vol)
    vector<Bar> testSeries = {
            {"1",1,1,1,1,0},
            {"2",2,2,2,2,0},
            {"3",3,3,3,3,0},
            {"4",4,4,4,4,0},
            {"5",5,5,5,5,0},
            {"6",6,6,6,6,0},
            {"7",7,7,7,7,0},
            {"8",8,8,8,8,0},
            {"9",9,9,9,9,0},
            {"10",10,10,10,10,0},
    };
    for(auto i : testSeries) cout << i.close;

    // call sma with (input series, iterator pointing to end of calculation window, sma length)
    // sma length 10 = (1+2+3...+10) / 10 = 5.5
    REQUIRE(indicator::sma(testSeries, testSeries.cbegin()+(10-1), 10) == 5.5);

}