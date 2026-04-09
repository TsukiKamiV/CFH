
#ifndef PmergeMe_hpp
#define PmergeMe_hpp

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <sys/time.h>

class PmergeMe {
	
private:
	int	* _sequence;
	size_t _size;
	std::vector<int>	_vect;
	std::deque<int>		_deque;
	
	struct Pair {
		int small;
		int large;
		int	id;
	};
	
	template <typename Container>
	std::vector<Pair>	makePair(const Container &c);
	
	template <typename Container>
	void	fordJohnsonSort(Container& c);
	
	template <typename Container>
	Container formMainChain(const std::vector<PmergeMe::Pair>&);
	
	template <typename Container>
	void	runOne(Container &c, const char *label, long long* elapsedUs);
	
	template <typename Container>
	void	printOne(Container &c, const char *label) const;
	
	template <typename Container>
	void	insertJacobsthal(Container &mainChain, const std::vector<Pair> &p);
	
	//template <typename Container>
	std::vector<size_t> smallChainOrder(const std::vector<Pair> &p);
	
	template <typename Container>
	void	insertLeftOver(Container &mainChain, int leftOverVal);
	
	static bool cmpPairLarge(const PmergeMe::Pair& lhs, const PmergeMe::Pair& rhs);
	
public:
	PmergeMe();
	PmergeMe(int, char **);
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();
	
	void	print() const;
	//void	printVector() const;
	//void	printDeque() const;
	void	run();
	//void	runVector();
	//void	runDeque();

	template <typename Container>
	void    printContainer(const Container& c) const;
};


template <typename Container>
void	PmergeMe::printOne(Container &c, const char *label) const {
	typename Container::const_iterator it = c.begin();
	typename Container::const_iterator end = c.end();
	std::cout << label << ": ";
	while (it != end) {
		std::cout << *it;
		++it;
		if (it != end)
			std::cout << " ";
	}
	std::cout << std::endl;
}

template <typename Container>
void	PmergeMe::runOne(Container &c, const char *label, long long* elapsedUs) {
	(void)label;
	struct timeval start;
	struct timeval end;
	//long long	elapsedUs;
	//printContainer(_vect);
	gettimeofday(&start, NULL);
	this->fordJohnsonSort(c);
	gettimeofday(&end, NULL);
	*elapsedUs = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
}

/**========================以下为算法类模板函数的具体实现========================**/

		   /*Ford Johnson algo*/
template <typename Container>
void	PmergeMe::fordJohnsonSort(Container& c)  {
	typename Container::size_type size = c.size();
	//std::cout << "Container size: " <<  c.size() << std::endl;
	if (size <= 1)
		return;
	bool	hasLeftOver = false;
	int		leftOverVal = 0;
	if (size % 2 == 1) {
		hasLeftOver = true;
		leftOverVal = c.back();
		//std::cout << "has leftover bool: " << hasLeftOver << ", Left over val: " << leftOverVal << std::endl;
	}
	std::vector<PmergeMe::Pair> vp = makePair(c);
	Container aChain;
	for(std::vector<Pair>::size_type i = 0; i < vp.size(); ++i)
		aChain.push_back(vp[i].large);
	if(aChain.size() <= 2)
		std::sort(aChain.begin(), aChain.end());
	else
		this->fordJohnsonSort(aChain);
	//std::sort(vp.begin(), vp.end(), static_cast<bool (*)(const Pair&, const Pair&)>(+[](const Pair& lhs, const Pair& rhs) {return lhs.large < rhs.large;}));
	std::sort(vp.begin(), vp.end(), cmpPairLarge);
	Container mainChain;
	if( !vp.empty())
		mainChain.push_back(vp[0].small);
	for(typename Container::iterator it = aChain.begin(); it != aChain.end(); ++it)
		mainChain.push_back(*it);
	
	//formMainChain<Container> => 显式提供返回类型，让模板函数在接收参数阶段就知道要返回的Container类型
	//编译器只有在“模板参数出现在函数参数类型里”时，才可以自动推导。
	//Container mainChain = formMainChain<Container>(vp);
	//printContainer(mainChain);
	//if (mainChain.size() <= 2)
	//	std::sort(mainChain.begin(), mainChain.end());
	//else
	//	this->fordJohnsonSort(mainChain);
	insertJacobsthal(mainChain, vp);
	if (hasLeftOver)
		insertLeftOver(mainChain, leftOverVal);
	c = mainChain;
	//printContainer(mainChain);
}

               /*MAKE PAIR*/
template <typename Container>
std::vector<PmergeMe::Pair> PmergeMe::makePair(const Container &c) {
	std::vector<Pair>	v;
	typename Container::const_iterator	it = c.begin();
	typename Container::size_type		size = c.size();
	typename Container::size_type		limit = size - (size % 2);
	int	x, y;
	Pair p;
	std::vector<Pair>::size_type pairID = 0;
	
	v.reserve(limit / 2);
	while (limit > 0) {
		//std::cout << "limit: " << limit << std::endl;
		x = *it;
		++it;
		y = *it;
		++it;
		p.small = std::min(x, y);
		p.large = std::max(x, y);
		p.id = pairID;
		++pairID;
		//std::cout << "small: " << p.small << ", large: " << p.large << std::endl;
		v.push_back(p);
		limit-=2;
	}
	return v;
}

               /*MAIN CHAIN*/
//在真正的FordJohnson算法里，b序列（small）的第一个数字（一定是整组的最小数）应该直接放在mainChain开头，而不是在jacobSthal阶段再插入
template <typename Container>
Container PmergeMe::formMainChain(const std::vector<PmergeMe::Pair>& pairs) {
	Container c;
	for(std::vector<Pair>::size_type i = 0; i < pairs.size(); ++i) {
		if(i == 0)
			c.push_back(pairs[i].small);
		c.push_back(pairs[i].large);
	}
	//PmergeMe::printContainer(c);
	return c;
}

template <typename Container>
void	PmergeMe::insertJacobsthal(Container &mainChain, const std::vector<Pair> &p) {
	std::vector<size_t> order = this->smallChainOrder(p);
	std::vector<size_t>::iterator oIt = order.begin();
	size_t	idx;
	int		a, b;
	while (oIt != order.end()) {
		idx = *oIt;
		a = p[idx].large;
		b = p[idx].small;
		
		typename Container::iterator posA = std::lower_bound(mainChain.begin(), mainChain.end(), a);
		typename Container::iterator pos = std::lower_bound(mainChain.begin(), posA, b);
		mainChain.insert(pos, b);
		++oIt;
	}
	//for (std::vector<Pair>::size_type i = 1; i < p.size(); ++i) {
	//	typename Container::iterator posA = std::lower_bound(mainChain.begin(), //mainChain.end(), p[i].large);
	//	//typename Container::iterator posA = std::find(mainChain.begin(), //mainChain.end(), p[i].large);
	//	typename Container::iterator pos = std::lower_bound(mainChain.begin(), //posA, p[i].small);
	//	mainChain.insert(pos, p[i].small);
	//}
}

template <typename Container>
void	PmergeMe::insertLeftOver(Container &mainChain, int leftOverVal) {
	typename Container::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), leftOverVal);
	mainChain.insert(pos, leftOverVal);
}

/*[NOT USED]Container printer template function*/
template <typename Container>
void	PmergeMe::printContainer(const Container& c) const {
	typename Container::const_iterator it = c.begin();
	typename Container::const_iterator end = c.end();
	while (it != end) {
		std::cout << *it;
		++it;
		if (it != end)
			std::cout << " ";
	}
	std::cout << std::endl;
}

#endif
