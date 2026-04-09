
#ifndef BitcoinExchange_hpp
#define BitcoinExchange_hpp

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdexcept>
#include <algorithm>

class BitcoinExchange {
private:
	std::map<std::string, double> _data;
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange& operator=(const BitcoinExchange &other);
	~BitcoinExchange();
	
	void	loadDataBase(const std::string&);
	double	getExchangeRate(const std::string& date) const;
	void 	parseInput(const std::string&) const;
};

#endif
