#pragma once

#include <string> 

using namespace std;

class Stock
{
private: 
	string _name;
	string _symbol;
	int _volume;
public:
	Stock();
	Stock(string, string, int);
	~Stock();

	string getName() { return _name; }
	string getSymbol() { return _symbol; }
	int getVolume() { return _volume; }

	void setName(string name) { _name = name; }
	void setSymbol(string symbol) { _symbol = symbol; }
	void setVolume(int volume) { _volume = volume; }
	void addVolume(int value) { _volume += value; }
	bool subtractVolume(int value);
};
