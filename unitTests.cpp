// Should be compiled as a standalone executable,
// which can be run with no arguments to run all tests.
// I didn't include testing of getter functions, because I think
//  the getters will be used to test the setters and other methods anyway
//
// Compile with: g++ -std=c++11 unitTests.cpp Account.cpp AccountActivityLog.cpp processCSV.cpp Stock.cpp -o unitTests

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "indicator.h"
#include "smaCross.h"
#include "Stock.h"
#include "Account.h"
#include "Account.h"
#include "processCSV.h"
#include "StrategyRunner.h"

// Here's most of what we can test
/*
Indicators:
  sma -, ema

Strategies:
    smaCross

Stock:
    subtractVolume -

Account:
    addStock -, removeStock - (use stockExists to test)

processCSV:
    setPath -, setDelimiter -, setIgnoreHeader -

StrategyRunner:
    marketOrder - (use getEquity and getNumShares to test)
*/

TEST_CASE("sma"){
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


    // call sma with (input series, iterator pointing to end of calculation window, sma length)
    // sma length 10 = (1+2+3...+10) / 10 = 5.5
    REQUIRE(indicator::sma(testSeries, testSeries.cbegin()+(10-1), 10) == 5.5);

}

TEST_CASE("ema") {
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


    // call ema with (input series, iterator pointing to end of calculation window, ema length)
    // ema length 10 = (1+2+3...+10) / 10 = 5.5

    REQUIRE(indicator::ema(testSeries, 5).at(9) == 8.0f);
}



TEST_CASE("subtract volume") {
    Stock testVolume;
    // testing the case that volume is smaller than value, which should return true.
    testVolume.setVolume(10);
    REQUIRE(testVolume.subtractVolume(5) == true);

    // testing the case that volume is equal to the value, which should return true.
    testVolume.setVolume(10);
    REQUIRE(testVolume.subtractVolume(10) == true);

    // testing the case that volume is larger than value, which should return false.
    testVolume.setVolume(10);
    REQUIRE(testVolume.subtractVolume(20) == false);
}

TEST_CASE("add stock") {
    Account testAccount;
    Stock testStock("stock", "symbol", 5);
    testAccount.addStock(testStock);
    REQUIRE(testAccount.getStock("symbol")->getSymbol() == testStock.getSymbol());
}
TEST_CASE("remove stock") {
    Account testAccount;
    Stock testStock("stock", "symbol", 5);
    testAccount.addStock(testStock);
    testAccount.removeStock(testStock);
    //REQUIRE(testAccount.getStock("symbol")->getSymbol() == NULL);

    REQUIRE(testAccount.removeStock(testStock) == NULL);
}

TEST_CASE("set path") {
    // path not set
    processCSV testCSV;
    REQUIRE(testCSV.getPath() == "not-set");



    // path set
    string path = "test";
    testCSV.setPath(path);
    REQUIRE(testCSV.getPath() == "test");
}

TEST_CASE("set delimiter") {
    // delimiter set
    processCSV testCSV;
    REQUIRE(testCSV.getDelimiter() == ',');



    // delimiter set
    char delimiter = '-';
    testCSV.setDelimiter(delimiter);
    REQUIRE(testCSV.getDelimiter() == '-');
}

TEST_CASE("set ignore header") {
    // ignore header set
    processCSV testCSV;
    REQUIRE(testCSV.getIgnoreHeader() == true);

    // ignore header not set
    bool ignore = false;
    testCSV.setIgnoreHeader(ignore);
    REQUIRE(testCSV.getIgnoreHeader() == false);
}

TEST_CASE("market order") {
    vector<signal_t> testSignal = {BUY};
    vector<Bar> testBar = {{"1",1,1,1,10,0}};
    Account testAccount;
    float balance = 100;
    float junk = 0;
    testAccount.setBalance(balance);
    StrategyRunner testRunner(testAccount, testBar, testSignal, junk);


    // buy case
    testRunner.marketOrder(BUY, 10);
    REQUIRE(testRunner.getNumShares() == 10);

    // sell case
    testRunner.marketOrder(SELL, 10);
    REQUIRE(testRunner.getNumShares() == 0);

    // hold case
    testRunner.marketOrder(HOLD, 0);
    REQUIRE(testRunner.getNumShares() == 0);
}