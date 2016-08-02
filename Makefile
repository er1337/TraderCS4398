Algorithmic_Trader: main.o processCSV.o Account.o AccountActivityLog.o Stock.o
	g++ -std=c++11 Stock.o AccountActivityLog.o Account.o processCSV.o main.o -o Algorithmic_Trader
main.o: main.cpp Bar.h smaCross.h Menus.h processCSV.h StrategyRunner.h
	g++ -std=c++11 -c main.cpp
processCSV.o: processCSV.cpp processCSV.h
	g++ -std=c++11 -c processCSV.cpp
Account.o: Account.cpp Account.h
	g++ -std=c++11 -c Account.cpp
AccountActivityLog.o: AccountActivityLog.cpp AccountActivityLog.h
	g++ -std=c++11 -c AccountActivityLog.cpp
Stock.o: Stock.cpp Stock.h
	g++ -std=c++11 -c Stock.cpp
