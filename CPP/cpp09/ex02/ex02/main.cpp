/**
 *要改：
 *1. isValidInput 不能正确检验positive integer sequence，long和atoi配合会失误；
 *2. 不应该允许输入0；
 *3. 没有检查“整串都是数字”
 *4. argc < 3还是从1开始？
 *5. 时间统计：时间应包含所有操作，不仅是排序部分，还包括数据管理部分。更合规的做法
 	每次测试容器时，都从原始输入重新构造该容器，并把“构造 + 排序”一起计时。
 	例如：
 	•	runVector() 内部自己从 argv 生成 vector
 	•	runDeque() 内部自己从 argv 生成 deque
 *6. Orthodox Canonical Form没有完整实现
 *7.强行避免有duplicate
 *
 */


#include <iostream>
#include <set>
#include <climits>
#include <cerrno>
#include <cstdlib>
#include "PmergeMe.hpp"

static bool isDigitString(const char *str) {
	int i = 0;
	if (str == NULL || str[0] == '\0' || str[0] == '0')
		return false;
	while (str[i] != '\0') {
		if (str[i] < '0' || str[i] > '9')
			return false;
		i++;
	}
	return true;
}

static bool parsePositiveInt(const char *str, int &value) {
	char *end;
	long num;
	
	if (!isDigitString(str))
		return false;
	errno = 0;
	end = NULL;
	num = std::strtol(str, &end, 10);
	if (errno == ERANGE || end == NULL || *end != '\0')
		return false;
	if (num <= 0 || num > INT_MAX)
		return false;
	value = static_cast<int>(num);
	return true;
}

static bool	checkParams(int argc, char *argv[]) {
	int	i = 1;
	int	value;
	std::set<int>	seen;
	
	if (argc < 2)
		return false;
	i = 1;
	while (i < argc) {
		if (!parsePositiveInt(argv[i], value))
			return false;
		if (seen.find(value) != seen.end())
			return false;
		seen.insert(value);
		i++;
	}
	return true;
}

int main(int argc, char *argv[]) {
	int	value;
	
	if (!checkParams(argc, argv)) {
		std::cerr << "Error" << std::endl;
		return 1;
	}
	std::cout << "Before: ";
	for (int i = 1; i < argc; i++) {
		parsePositiveInt(argv[i], value);
		std::cout << " " << value;
	}
	std::cout << std::endl;
	PmergeMe pm(argc, argv);
	pm.run();
	return 0;
}
