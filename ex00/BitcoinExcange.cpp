#include "BitcoinExchange.hpp"

bool	BitcoinExchange::ValidateInputTxtFile(std::string &fileName)
{
	std::ifstream file(fileName.c_str());
	std::string line;
	int year, month, day;

	if (!file.is_open())
	{
		std::cerr << "[ERROR] Can not open Inputfile" << std::endl;
		return false;
	}
	getline(file, line);
	if (line != "date | value")
	{
		std::cerr << "[ERROR] Invalid Title" << std::endl;
        return false;
	}
	if (line.eof())
	{
		std::cerr << "Error : file empty" << std::endl;
		return false;
	}
	while (getline(file, line))
	{
		std::istringstream iss(line);
		if (std::getline(iss date, '|') && std::getline(formats, valueStr)) {
    	// 앞뒤 공백 제거 (trim)
		date.erase(date.find_last_not_of(" \t\n\r\f\v") + 1);
		valueStr.erase(0, valueStr.find_first_not_of(" \t\n\r\f\v"));
		if ()
		}	
	}
}
bool	BitcoinExchange::ValidateCsvFile()
{
	std::ifstream dataBase("data.csv");
	std::string line;
	if (!dataBase.is_open()) 
	{
		std::cerr << "[ERROR] Can not open data.csv" << std::endl;
		return false;
	}
	if (!getline(dataBase, line))
	{
		std::cerr << "[ERROR] Empty file" << std::endl; 
		return false;
	}

    if (line != "date,exchange_rate")
    {
        std::cerr << "[ERROR] Invalid Title" << std::endl;
        return false;
    }

    while (getline(dataBase, line)) 
    {
		std::stringstream ss(line);
        csvToMap(ss);
    }
	return true;

}

void BitcoinExchange::csvToMap(std::stringstream &line)
{
	bool isKey = true;
	std::string key;
	std::string token;
	double		value;
	std::map<std::string, double> temp;
	

	while (getline(line, token, ',')) 
	{
		if (isKey)
		{
			key = token;
			isKey = false;
		}
		else
		{
			value = atof(token.c_str());
			isKey = true;
		}

	}
	this -> info.insert(std::make_pair(key, value));
};
