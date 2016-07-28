//Wesley Myres//
#include "Stock.h"


Stock::Stock() {}

Stock::Stock(string name, string symbol, int volume) :
	_name(name),
	_symbol(symbol),
	_volume(volume)
{}

bool Stock::subtractVolume(int value)
{
	if (_volume < value)
		return false;
	else
		_volume -= value;
	return true;
}

//Stock::~Stock() {}
