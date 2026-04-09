
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "BitcoinExchange.hpp"

/**
 *@brief ‼️THE PROGRAM NAME MUST BE BTC
 *
 *项目要求：用一份“历史比特币价格数据库(csv)去回答另一份文件里提出的“查询请求”(input.txt)
 *[database.csv]: 结构化数据文件，此处表示“某一天，比特币的价格是多少”
 *		- csv: comma-seperated-values
 *本程序主要按以下三步完成：
 *	1️⃣ 加载事实库(csv database) （把database里面的data -> exchange_rate放进内存里的std::map）
 *	2️⃣ 逐条读取查询(input.txt) （input里的内容是：某一天 ｜ 某个比特币数量）
 *	3️⃣ 用事实库回答查询：
 *		针对每一行input:
 *		(1) 用日期去database(map)里查询价格；
 *		(2) 如果那天没有价格 ==> 用 【最近但不晚于那一天】的价格
 *		(3) 计算 “value * exchange_rate"
 *		(4) 输出结果
 */

int main(int argc, const char * argv[]) {
	try {
		if (argc != 2)
			throw std::runtime_error("Error: wrong argument number");
		BitcoinExchange btc;
		btc.loadDataBase("/Users/luyao/Projects/local/cpp09/ex00/ex00/data.csv");
		btc.parseInput(argv[1]);
		return 0;
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
