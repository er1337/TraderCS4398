parser: driver.o processCSV.o
	g++ -std=c++11 processCSV.o driver.o -o parser
driver.o: driver.cpp processCSV.h
	g++ -std=c++11 -c driver.cpp
processCSV.o: processCSV.cpp processCSV.h Bar.h
	g++ -std=c++11 -c processCSV.cpp
