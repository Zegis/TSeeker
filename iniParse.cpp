#include "iniParse.h"

#include <iostream>
#include <fstream>

using std::cout;

iniParse::iniParse(string filename)
{
	fileName = filename;

	read();
}

void iniParse::read()
{
	cout << "Czytam plik konfiguracyjny: " << fileName << "\n";

	std::fstream file(fileName);

	string configLine;

	while(std::getline(file, configLine))
	{
		trimm(&configLine);
		cout << "Czytam linijke: " << configLine << ".\n";

		size_t found;

		if(configLine[0] == ';')
			continue;
		else if(configLine[0] == '[')
		{
			sectionName = configLine.substr(1, configLine.length()-2);
			cout << "Znaleziono sekcje: " << sectionName << ".\n";
		}
		else
		{
			found = configLine.find('=');
			if(found != configLine.npos)
			{
				cout << "Delimiter na pozycji: " << found;
				StoreValue(configLine, found);
			}
		}
	}

}

void iniParse::trimm(string *s)
{
	size_t found = s->find_first_not_of(" \t");

	if(found != s->npos)
		*s = s->substr(found);

	found = s->find_last_not_of(" \t");

	if(found != s->npos)
		*s = s->substr(0, found+1);
}

void iniParse::StoreValue(string lineWithValue, size_t delimiterPos)
{
	string key = makeKey(lineWithValue.substr(0,delimiterPos));
	cout << "Zapisze wartosc: " << lineWithValue.substr(delimiterPos+1) << " pod kluczem: " << key << ".\n";
}

string iniParse::makeKey(string propName)
{
	string ret = sectionName + "." + propName;

	return ret;
}

string iniParse::makeKey(string section, string property)
{
	string ret = section + "." + property;

	return ret;
}