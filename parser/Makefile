parser: test_driver.o processCSV.o
	g++ processCSV.o test_driver.o -o parser
test_driver.o: test_driver.cpp processCSV.h
	g++ -c test_driver.cpp
processCSV.o: processCSV.cpp processCSV.h
	g++ -c processCSV.cpp
