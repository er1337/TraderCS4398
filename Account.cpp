//Wesley Myres//
#include "Account.h"

int Account::_idIncrement = 1;

Account::Account() {}
Account::Account(string name, float balance, map<string, Stock> stocks)	:
	_name(name),
	_balance(balance),
	_stocks(stocks)
{
	_id = ++_idIncrement;
	_log = new AccountActivityLog(_idIncrement + "_log.txt");
}
Account::~Account() 
{
	delete _log;
}

bool Account::stockExists(string symbol)
{
	map<string, Stock>::const_iterator it = _stocks.find(symbol);
	return it != _stocks.end();
}

void Account::addStock(Stock stock)
{

	if (!stockExists(stock.getSymbol()))
		_stocks[stock.getSymbol()] = stock;
	else
		_stocks[stock.getSymbol()].addVolume(stock.getVolume());
}

Stock* Account::getStock(string symbol)
{
	if (!stockExists(symbol))
		return NULL;
	else
		return &_stocks[symbol];
}

bool Account::removeStock(Stock stock)
{
	if (!stockExists(stock.getSymbol()))
		return false;
	else 
		return _stocks[stock.getSymbol()].subtractVolume(stock.getVolume());
}
