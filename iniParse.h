#pragma once

#include <string>

using std::string;

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

	public:
		iniParse(string fileName);

		void reloadFile();
};