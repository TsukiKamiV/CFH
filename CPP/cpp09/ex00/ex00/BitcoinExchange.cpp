
#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _data(other._data) {}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other)
		this->_data = other._data;
	return *this;
}
BitcoinExchange::~BitcoinExchange() {}

void	BitcoinExchange::loadDataBase(const std::string& filename) {
	//open data.csv and load into ifstream
	std::ifstream dataBase;
	if (filename.empty())
		throw std::runtime_error("Error: empty database file");
	dataBase.open(filename.c_str());
	if (!(dataBase.is_open()))
		throw std::runtime_error("Error: cannot open database file");
	//append string
	std::string line;
	std::string::size_type comma;
	std::string key;
	std::string valueString;
	const char *start;
	char *end;
	double value;
	
	while (std::getline(dataBase, line)) {
		comma = line.find(',');
		//std::string::npos = no position，
		//find()的语义是：如果找到了参数字符，返回字符的位置（0， 1， 2，...)
		//				如果没找到，返回std::string::npos （值是-1)
		if (comma == std::string::npos)
			continue;
		key = line.substr(0, comma);
		valueString = line.substr(comma + 1);
		/**
		 * strtod 解析完数字后，把 end 设置成“解析停止的位置”（也就是指向第一个“不能作为数字一部分”的字符）。
		 *	•	如果整段字符串都是合法数字（例如 "12.34"），那么 end 会指向字符串结尾的 '\0'（终止符）。
		 	•	如果字符串是 "12.34abc"，那么 end 会指向 'a'。
			•	如果字符串根本不能解析出数字（例如 "abc"），那么 end 会等于输入指针（也就是 valueString.c_str() 的起始位置）。
		 */
		value = std::strtod(valueString.c_str(), &end);
		start = valueString.c_str();
		//end == start表示一个字符都没解析成功
		//如果停止位置不是字符串的末尾（后面还有别的字符），则这一行不是合法字符串，跳过
		if (end == start || *end != '\0')
			continue;
		this->_data.insert(std::make_pair(key, value));
	}
}

/**
 *@brief 	用 lower_bound 找到第一个不小于输入日期的位置；
 			如果精确命中就用它，
 			否则回退一步，得到最接近但不大于输入日期的那一天。
 *
 *⭐️(std::map<std::string, double>::const iterator it)
 *		当迭代器指向 map 中的一个元素时，它实际上指向的是一个 std::pair<const Key, T>。
 *		- it->first：访问key，在这里是std::string类型的日期
 *		- it->second:访问value，指汇率
 *
 * ⭐️(lower_bound (key): map container特有的查找函数，它返回一个迭代器，指向第一个key >= 参数key的元素
 * （而相对应的，find()只能实现精确匹配，不符合题目要求）
 *			👉如果数据库中只有2011-01-01和2011-01-03，而要查找的是2011-01-02，find()会返回失败，而lower_bound(date)会返回2011-01-03的迭代器，让使用者通过“回退(fallback)操作找到最近的有效日期（题目要求: closest lower date)”
 *	 👉如果存在key ->指向它；如果不存在->指向“第一个比它大的key"； 如果所有key都小于参数->返回end()
 */
double	BitcoinExchange::getExchangeRate(const std::string &date) const {
	std::map<std::string, double>::const_iterator it;
	//找到第一个key >= date的位置
	it = this->_data.lower_bound(date);
	//如果找到精确对应的日期
	if (it != this->_data.end() && it->first == date)
		return it->second;
	//如果比所有日期都早（非法）
	if (it == this->_data.begin())
		throw std::runtime_error("Error: no earlier date available");
	//lower_bound指向的是“第一个更大的” ➡️ 比最晚的日期还晚（并且不是第一个日期）就回退到最晚日期
	if (it == this->_data.end() || it->first != date)
		//fallback(回退）到”最后一个小于date的日期“
		--it;
	return it->second;
}

static void trimWhiteSpace(std::string &line) {
	std::string::size_type	begin = 0;
	std::string::size_type	end;
	
	while (begin < line.length() && (line[begin] == ' ' || line[begin] == '\t'))
		begin++;
	if (begin == line.length()) {
		line.clear();
		return ;
	}
	end = line.length() - 1;
	while (end > begin && (line[end] == ' ' || line[end] == '\t'))
		end--;
	line = line.substr(begin, end - begin + 1);
}

/**年份数是闰年的条件：
  * 1️⃣ 能被400整除
  * 2️⃣ 能被4整除但不能被100整除
 */
static bool	isLeapYear(const int year) {
	if (year % 400 == 0)
		return true;
	if (year % 100 == 0)
		return false;
	if (year % 4 == 0)
		return true;
	return false;
}

static bool	isValidDate(const std::string &date) {
	if (date.length() != 10)
		return false;
	size_t	dashCount = std::count(date.begin(), date.end(), '-');
	if (dashCount != 2)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	for (int i = 0; i < date.length(); i++) {
		if (i != 4 && i != 7) {
			if (!std::isdigit(static_cast<unsigned char>(date[i])))
				return false;
		}
	}
	std::string yearStr = date.substr(0, 4);
	std::string monStr = date.substr(5, 2);
	std::string dayStr = date.substr(8, 2);
	int	year = std::atoi(yearStr.c_str());
	int	mon = std::atoi(monStr.c_str());
	int	day = std::atoi(dayStr.c_str());
	if (mon < 1 || mon > 12)
		return false;
	if (day < 1)
		return false;
	if (mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12)
		return (day <= 31);
	if (mon == 4 || mon == 6 || mon == 9 || mon == 11)
		return (day <= 30);
	if (mon == 2) {
		if (isLeapYear(year)) {
			return (day <= 29);
		}
		else
			return (day <= 28);
	}
	return true;
}

void BitcoinExchange::parseInput(const std::string& input) const {
	std::ifstream ifs;
	if (input.empty())
		throw std::runtime_error("Error: input file empty");
	ifs.open(input.c_str());
	if (!(ifs.is_open()))
		throw std::runtime_error("Error: could not open file");
	
	std::string line;
	std::string::size_type pipe;
	std::string date;
	double value;
	const char	*start;
	char		*end;
	bool	isFirstLine = true;
	
	while (std::getline(ifs, line)) {
		trimWhiteSpace(line);
		if (isFirstLine && line == "date | value") {
			isFirstLine = false;
			continue;
		}
		size_t	pipeCount = std::count(line.begin(), line.end(), '|');
		if (pipeCount != 1) {
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		pipe = line.find('|');
		if (pipe == std::string::npos) {
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (pipe == 0) {
			std::cout << "Error: bad input" << std::endl;
			continue;
		}
		else if (pipe + 1 >= line.length()) {
			std::cout << "Error: bad input => " << line.substr(0, pipe) << std::endl;
			continue;
		}
		date = line.substr(0, pipe - 1);
		if (!(isValidDate(date))) {
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}
		std::string valueString = line.substr(pipe + 1);
		start = valueString.c_str();
		value = std::strtod(start, &end);
		if (value < 0) {
			std::cout << "Error: not a positive number" << std::endl;
			continue;
		}
		if (end == start || *end != '\0') {
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}
		
		if (value > 1000) {
			std::cout << "Error: too large a number" << std::endl;
			continue;
		}
		try {
			double rate;
			double result;
			
			rate = this->getExchangeRate(date);
			result = rate * value;
			std::cout << date << " => " << result << std::endl;
		}
		catch (const std::exception &e) {
			std::cout << e.what() << " => " << date << std::endl;
		}
	}
}
