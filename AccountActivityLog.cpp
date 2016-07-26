#include "AccountActivityLog.h"



AccountActivityLog::AccountActivityLog() {}
AccountActivityLog::AccountActivityLog(string filename) :
	_filename(filename)
{}
AccountActivityLog::~AccountActivityLog() 
{
	closeLog();
}

void AccountActivityLog::appendLog(string value)
{
	_log.open(_filename, ios::app);
	_log << value;
	_log.close();
}

vector<string> AccountActivityLog::getLog()
{
	vector<string> temp;
	string line = "";
	_log.open(_filename, fstream::in | fstream::out);
	if (_log.is_open())
	{
		while (getline(_log, line))
		{
			temp.push_back(line);
		}
	}
	_log.close();
	return temp;
}

