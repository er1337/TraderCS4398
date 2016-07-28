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
	static int _idIncrement;
	int _id;
	float _balance;
	float _initBalance;

private:
	AccountActivityLog* _log;
	string _name;
	map<string, Stock> _stocks;

	bool stockExists(string symbol);
public:
	Account();
	Account(string, float, map<string, Stock>);
	//~Account();

	float getBalance() { return _balance; }
	float getInitBalance() const { return _initBalance;	}
	void set_initBalance(float _initBalance) { Account::_initBalance = _initBalance; }

	map<string, Stock> getStocks() { return _stocks; }
	string getName() { return _name; }
	void setName(string name) { _name = name; }
	void setBalance(float balance) { _balance = balance; }
	void addStock(Stock stock);
	bool removeStock(Stock stock);
	Stock* getStock(string symbol);
	int getId() { return _id; }
};


