
#ifndef MutantStack_h
#define MutantStack_h

#include <iostream>
#include <iterator>
#include <stack>

/**
 *@brief std::stack
 *是一个容器适配器(container adapter)，不是一个真正意义上的容器。
 *	也就是说：std::stack本身并不储存数据，它只是“包装”了一个底层容器，例如std::deque 或者std::vector
 *	它的默认底层容器是std::deque<T>
 *作用：把这个底层容器的操作先制成只有“栈”的行为：
 *		push(),   pop(),    top(),   empty(),   size()
 *		（只暴露以上操作，其他全部隐藏）
 *std::stack的核心设计思想：
 * - 必须保证后进先出（LIFO）
 * - 用户不能访问任意元素
 * - 用户不能遍历
 * - 用户不能插入中间位置
 */

template <typename T>
class MutantStack : public std::stack<T> {
	//‼️MutantStack类的目的：‼️
	//在不破坏std::stack的前提下，强制暴露底层容器，使其能够被遍历
public:
	MutantStack();
	MutantStack(const MutantStack& other);
	MutantStack& operator=(const MutantStack& other);
	~MutantStack();
	
	/**
	 *typedef typename std::stack<T>::container_type::iterator iterator; => 整句意思：
	 *	把 std::stack<T>::container_type::iterator 这个类型 起一个简短名字叫 iterator。
	 *std::stack<T>::container_type::iterator：
	 *	让基类std::stack的底层容器的类型成为iterator（而不是原本默认的std::deque)
	 *⭐️为什么必须要写typename?
	 *	- T是模板函数
	 *	- std::stack<T>::container_type是一个依赖模板参数的“依赖类型”；
	 *	- std::stack<T>::container_type::iterator对编译器来说，一开始不知道这是“类型”还是“静态成员/变量"
	 *	❕C++ 语法规定：
	 *	｜只要是“依赖于模板参数的类型名”，前面必须加typename告诉编译器“这是一个类型”
	 */
	
	typedef typename std::stack<T>::container_type::iterator iterator;
	typedef typename std::stack<T>::container_type::const_iterator const_iterator;
	/**
	 * 在std::stack的定义里，有一个protected成员 protected: Container c;
	 * 这两个函数的作用就是：
	 * 	“把底层容器的begin() / end()暴露出来，让MutantStack这个类有了自己的begin() / end()，可以像vector一样被遍历
	 */
	iterator begin() {return this->c.begin();}
	iterator end() {return this->c.end();}
	
	const_iterator begin() const {return this->c.begin();}
	const_iterator end() const {return this->c.end();}
};

template <typename T>
MutantStack<T>::MutantStack() {}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack<T>& other) : std::stack<T>(other) {}

template <typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack<T>& other) {
	if (this != &other)
		std::stack<T>::operator=(other);
	return *this;
}

template <typename T>
MutantStack<T>::~MutantStack() {}

/**
 *std::stack.top() ➡️ 访问栈顶元素
 *返回栈顶元素的引用，但不移除它
 */

/**
 *std::stack.pop() ➡️ 移除栈顶元素
 *删除栈顶元素，但不返回被删除的内容
 *pop()在空栈上调用是undefined behavior
 */

#endif
