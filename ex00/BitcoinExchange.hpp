#pragma once

#include <algorithm>
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <sstream>

class BitcoinExchange
{
	private:
		std::map<std::string, float> info;
		void	readUserInput();
		bool	ValidateInputTxtFile(std::string &fileName);
		bool	ValidateCsvFile();
		bool 	ValidateDate(int year, int month, int day);
		void	parse();
		void 	csvToMap(std::stringstream &line);
		void	calcaculate();
		void	printResult();

	
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange& operator=(const BitcoinExchange &other);
		~BitcoinExchange();
		
};