
#ifndef Header_h
#define Header_h

#include <iostream>
#include <algorithm>
#include <stdexcept>

/**
 *@brief STL : 容器(Container) + 迭代器(iterator) + 算法(algorithm)
 *1. 容器(container)：会自己管理一堆元素的“智能数组”
 *  常见的顺序容器有：
 *  std::vector<int>：动态数组，内存连续，支持随机访问(array[i])
 *  std::list<int>：双向链表，不连续，但插入/删除中间元素很方便
 *  std::deque<int>：两端都能高效push/pop的“双端队列”
 *2. 迭代器(iterator)：指向容器元素的指针
 *	比较典型的使用方式：
 *	container.begin()：指向第一个元素的迭代器
 *	container.end()：指向尾后位置（“最后一个元素的下一个位置”）的迭代器，不存东西，只用于比较结束
 *	所以一个典型循环是：
 *	for (std::vector<int>::iterator it = v.begin(); it != it.end(); ++it)
 *3. 算法(algorithm)
 *	STL提供了一堆“跟容器无关的算法函数”， 放在<algorithm>里，比如：
 *	std::find[it_begin, it_end, value): 在[it_begin, it_end]范围里找value，返回指向第一次出现的迭代器；如果找不到，返回it_end
 *	关键点：算法只关心迭代器，不关心你是vector还是list
 *	这就是easyfind要做的事：给它一个“容器 + 要找的值”， 内部用std::find去找
 */

/**
 *@return typename T::iterator
 *这里返回值用迭代器而不是指针，是因为题目要求使用的STL容器种类太多，有的使用连续内存（如vector<int>)，可以用指针逐个访问，但一些容器内部内存非连续（如deque<int>)，就不能用指针访问了，因此必须引入迭代器这个“容器专属指针”，对内实现会根据容器类型不同而不同
 *迭代器内部的运行原理虽根据容器的性质而不同，但它们的接口一样，这是迭代器的精髓
 *
 *@param std::find()
 *来自<algorithm> 原型：
 *template <class InputIterator, class T>
 *InputIterator find(InputIterator first, InputIterator last, const T& value);
 *意思是：在区间[first, last)中，查找第一个满足*it == value的元素。
 *	找到则返回指向该元素的迭代器；
 *	找不到就返回last。
 *可以用于所有满足InputIterator的迭代器（包括自定义迭代器的自定义容器和流迭代器(istream_iterator)
 */

template <typename T>
//这里的typename必须写，目的是告诉编译器：这是一个类型
typename T::iterator easyfind(T &container, int value) {
	typename T::iterator it = std::find(container.begin(), container.end(), value);
	if (it == container.end())
		throw std::runtime_error("easyfind: value not found");
	return it;
}

template <typename T>
typename T::const_iterator	easyfind(T const &container, int value) {
	typename T::const_iterator it = std::find(container.begin(), container.end(), value);
	if (it == container.end())
		throw std::runtime_error("easyfind: value not found");
	return it;
}

#endif
