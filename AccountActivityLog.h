#pragma once
//Wesley Myres//
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class AccountActivityLog
{
private:
	string _filename;
	fstream _log;
public:
	AccountActivityLog();
	AccountActivityLog(string filename);
	~AccountActivityLog();
	void openLog(string filename);
	void closeLog();
	vector<string> getLog();
	void appendLog(string value);
	void setFilename(string filename) { _filename = filename; }
};

