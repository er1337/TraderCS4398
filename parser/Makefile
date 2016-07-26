parser: driver.o processCSV.o
	g++ processCSV.o driver.o -o parser
driver.o: driver.cpp processCSV.h
	g++ -c driver.cpp
processCSV.o: processCSV.cpp processCSV.h
	g++ -c processCSV.cpp
