#include "BitcoinExchange.hpp"

bool	BitcoinExchange::ValidateCsvFile()
{
	std::ifstream dataBase("data.csv");
	std::string line;
	if (!dataBase) 
	{
		std::cout << "[ERROR] Can not open data.csv" << std::endl;
		return false;
	}
	if (std::getline(dataBase, line))
	{
		std::cout << "[ERROR] Empty file" << std::endl; 
		return false;
	}

	while(std::getline(dataBase, line))
	{
		if (line != "date,exchange_rate")
		{
			std::cerr << "[ERROR] Invalid Title" << std::endl;
			return false;
		}
	}


}