cmake_minimum_required(VERSION 3.5)
project(TraderCS4398)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Bar.h
    main.cpp
    smaCross.h indicator.h
    smaCross.h Menus.h StrategyRunner.h enums.h
    Account.h AccountActivityLog.h Stock.h
    processCSV.cpp Account.cpp Stock.cpp AccountActivityLog.cpp)

add_executable(TraderCS4398 ${SOURCE_FILES})