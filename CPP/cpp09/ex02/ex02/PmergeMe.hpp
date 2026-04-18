
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
	void	run();
	void	runVector();
	void	runDeque();

	template <typename Container>
	void    printContainer(const Container& c) const;
};

/**========================以下为算法类模板函数的具体实现========================**/

		   /*Ford Johnson algo*/
template <typename Container>
void	PmergeMe::fordJohnsonSort(Container& c)  {
	typename Container::size_type size = c.size();
	//递归出口=>终止条件是0-1个元素，天然有序
	if (size <= 1)
		return;
	bool	hasLeftOver = false;
	int		leftOverVal = 0;
	//先处理奇数长度的leftover
	if (size % 2 == 1) {
		hasLeftOver = true;
		leftOverVal = c.back();
	}
	std::vector<PmergeMe::Pair> vp = makePair(c);
	Container aChain;
	for(std::vector<Pair>::size_type i = 0; i < vp.size(); ++i)
		aChain.push_back(vp[i].large);
	if(aChain.size() <= 2)
		std::sort(aChain.begin(), aChain.end());
	else
		this->fordJohnsonSort(aChain);
	std::vector<Pair> orderedPair;
	orderedPair.reserve(vp.size());
	typename Container::const_iterator opIt = aChain.begin();
	while (opIt != aChain.end()) {
		int currentLarge = *opIt;
		std::vector<Pair>::const_iterator vpIt = vp.begin();
		while (vpIt != vp.end()) {
			if (vpIt->large == currentLarge) {
				orderedPair.push_back(*vpIt);
				break;
			}
			++vpIt;
		}
		++opIt;
	}
	Container mainChain;
	if( !orderedPair.empty())
		mainChain.push_back(orderedPair[0].small);
	for(typename Container::const_iterator it = aChain.begin(); it != aChain.end(); ++it)
		mainChain.push_back(*it);
	insertJacobsthal(mainChain, orderedPair);
	if (hasLeftOver)
		insertLeftOver(mainChain, leftOverVal);
	c = mainChain;
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
