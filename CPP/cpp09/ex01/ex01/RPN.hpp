
#ifndef RPN_hpp
#define RPN_hpp


/**
 *@brief  什么是 Reverse Polish Notation（RPN）
 
 Reverse Polish Notation（逆波兰表示法） 的核心规则只有一句话：
 
 操作符写在操作数之后（后缀表示法，postfix）。
 *
 *  Polish notation（前缀）的规则
 *  在 前缀表达式（prefix / Polish） 中：
 *  操作符总是出现在它的所有操作数之前。
 *  并且每个操作符的 操作数数量是固定的（比如 + 和 * 都是二元操作符，需要两个操作数）。
 */

/**
 *⭐️算法（极其重要）⭐️：
 
 从左到右扫描 token：
 1.	如果是 数字 → 压栈
 2.	如果是 操作符：
 •	从栈中 弹出两个数
 •	⚠️ 先弹出的是右操作数
 •	计算
 •	把结果压回栈
 */

#include <iostream>
#include <stack>
#include <sstream>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <cctype>

class RPN {
	
public:
	RPN();
	RPN(const RPN &other);
	RPN& operator=(const RPN &other);
	~RPN();

	int		evaluate(const std::string &param);
	
private:
	std::stack<int>	_stack;
};





#endif
