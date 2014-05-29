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

		if(configLine[0] == ';')
			continue;
		else if(configLine[0] == '[')
		{
			sectionName = configLine.substr(1, configLine.length()-2);
			cout << "Znaleziono sekcje: " << sectionName << ".\n";
		}
		else
		{
			size_t found = configLine.find('=');
			if(found != configLine.npos)
			{
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
	string value = lineWithValue.substr(delimiterPos+1);
	cout << "Zapisze wartosc: " << value << " pod kluczem: " << key << ".\n";

	configuration.insert(pair<string,string>(key,value));	
}

string iniParse::makeKey(string propName)
{
	string ret = sectionName + "." + propName;

	return ret;
}

int iniParse::getValue(string section, string property, int defaultValue)
{
	string key = makeKey(section, property);

	int ret;

	try
	{
		//string tmp = configuration.at(key);
		ret = std::stoi(configuration.at(key));
		//ret = std::stoi(tmp);
	}
	catch(const std::out_of_range)
	{
		ret = defaultValue;
	}

	return ret;
}

string iniParse::makeKey(string section, string property)
{
	string ret = section + "." + property;

	return ret;
}