#pragma once

#include <algorithm>
#include <map>
#include <iostream>
#include <string>
#include <sstream>
class BitcoinExchange
{
	private:
		std::map<std::string, float> info;
		void	readUserInput();
		bool	ValidateInputTxtFile();
		bool	ValidateCsvFile();
		void	parse();
		void	calcaculate();
		void	printResult();

	
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange& operator=(const BitcoinExchange &other);
		~BitcoinExchange();
		
};