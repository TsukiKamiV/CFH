
#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(int argc, char **argv) {
	int i;
	int value;
	
	i = 1;
	while (i < argc) {
		value = std::strtol(argv[i], NULL, 10);
		this->_vect.push_back(value);
		i++;
	}
	this->_deque.assign(this->_vect.begin(), this->_vect.end());
}
PmergeMe::PmergeMe(const PmergeMe &other) {
	*this = other;
}
PmergeMe& PmergeMe::operator=(const PmergeMe &other) {
	if (this != &other) {
		*this = other;
	}
	return *this;
}
PmergeMe::~PmergeMe() {}

void	PmergeMe::print() const {
	this->printOne(this->_vect, "std::vector<int>");
	this->printOne(this->_deque, "std::deque<int>");
}

void	PmergeMe::run() {
	long long vectUs;
	long long dequeUs;
	this->runOne(this->_vect, "std::vector<int>", &vectUs);
	this->runOne(this->_deque, "std::deque<int>", &dequeUs);
	std::cout << "After: ";
	printContainer(this->_vect);
	std::cout << "Time to process a range of " << this->_vect.size() << " elements with std::vector<int>: " << vectUs << " us" << std::endl;
	std::cout << "Time to process a range of " << this->_deque.size() << " elements with std::deque<int>: " << dequeUs << " us" << std::endl;
}

std::vector<size_t> PmergeMe::smallChainOrder(const std::vector<Pair> &p) {
	std::vector<size_t> order;
	//batchEnd => 本批要插入的最大b编号 (hight boundary)
	//
	size_t	m, t_prev, t, batchEnd, j, k;
	m = p.size();
	if (m <= 1)
		return order;
	order.reserve(m - 1);
	t_prev = 1;
	k = 2;
	while (1) {
		t = (static_cast<size_t>(1) << k) - t_prev;
		batchEnd = std::min(t, m);
		j = batchEnd;
		while (j > t_prev) {
			order.push_back(j - 1);
			--j;
		}
		if(batchEnd == m)
			break;
		t_prev = t;
		++k;
	}
	return (order);
}

bool PmergeMe::cmpPairLarge(const PmergeMe::Pair& lhs, const PmergeMe::Pair& rhs)
{
	return lhs.large < rhs.large;
}






























//void	PmergeMe::runVector() {
//	struct timeval start;
//	struct timeval end;
//	long long	elapsedUs;
//	//printContainer(_vect);
//	gettimeofday(&start, NULL);
//	gettimeofday(&end, NULL);
//	elapsedUs = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
//	std::cout << "Time to process a range of " << this->_vect.size() << " elements with std::vector<int> : " << elapsedUs << " us" //<< std::endl;
//	fordJohnsonSort(_vect);
//}
//
//void	PmergeMe::runDeque() {
//	struct timeval start;
//	struct timeval end;
//	long long elapsedUs;
//	gettimeofday(&start, NULL);
//	gettimeofday(&end, NULL);
//	elapsedUs = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
//	std::cout << "Time to process a range of " << this->_deque.size() << " elements with std::deque<int> : " << elapsedUs << " us" //<< std::endl;
//}

//void	PmergeMe::printVector() const {
//	std::vector<int>::const_iterator it = this->_vect.begin();
//	std::vector<int>::const_iterator end = this->_vect.end();
//	std::cout << "Vector: ";
//	while (it != end) {
//		std::cout << *it;
//		++it;
//		if (it != end)
//			std::cout << " ";
//	}
//	std::cout << std::endl;
//
//}
//
//void	PmergeMe::printDeque() const {
//	std::deque<int>::const_iterator it = this->_deque.begin();
//	std::deque<int>::const_iterator end = this->_deque.end();
//	std::cout << "Deque: ";
//	while (it != end) {
//		std::cout << *it;
//		++it;
//		if (it != end)
//			std::cout << " ";
//	}
//	std::cout << std::endl;
//}
