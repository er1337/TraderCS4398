#pragma once
//Wesley Myres//
#include <string>
#include <map>

#include "Stock.h"
#include "AccountActivityLog.h"

using namespace std;

class Account
{

private:
	float _balance;
	AccountActivityLog* _log;
	string _name;
	map<string, Stock> _stocks;

	bool stockExists(string symbol);
public:
	Account();
	Account(string, float, map<string, Stock>);
	~Account();

	float getBalance() { return _balance; }
	map<string, Stock> getStocks() { return _stocks; }
	string getName() { return _name; }
	void setName(string name) { _name = name; }
	void setBalance(float balance) { _balance = balance;  }
	void addStock(Stock stock);
	bool removeStock(Stock stock);
	Stock* getStock(string symbol);
};


