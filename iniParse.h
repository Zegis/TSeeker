#pragma once

#include <string>
#include <map>

using std::string;
using std::map;
using std::pair;

class iniParse
{
	private:

		void read();

		string makeKey(string propName);

		string makeKey(string section, string property);

		string fileName;

		string sectionName;

		void trimm(string *s);

		void StoreValue(string lineWithValue, size_t delimiterPos);

		map<string, string> configuration;

	public:
		iniParse(string fileName);

		void reloadFile();

		int getValue(string section, string property, int defaultValue);
};