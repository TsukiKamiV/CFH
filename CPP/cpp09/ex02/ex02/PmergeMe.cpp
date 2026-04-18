
#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {
	this->_sequence = NULL;
	this->_size = 0;
}
PmergeMe::PmergeMe(int argc, char **argv) {
	int i;
	int value;
	
	this->_size = argc - 1;
	this->_sequence = new int[this->_size];
	i = 1;
	while (i < argc) {
		value = std::strtol(argv[i], NULL, 10);
		this->_sequence[i - 1] = value;
		i++;
	}
}
PmergeMe::PmergeMe(const PmergeMe &other) {
	size_t i;
	this->_size = other._size;
	if (this->_size > 0)
		this->_sequence = new int[this->_size];
	else
		this->_sequence = NULL;
	i = 0;
	while (i < this->_size) {
		this->_sequence[i] = other._sequence[i];
		i++;
	}
}
PmergeMe& PmergeMe::operator=(const PmergeMe &other) {
	size_t	i;
	
	if (this != &other)
	{
		delete[] this->_sequence;
		this->_size = other._size;
		if (this->_size > 0)
			this->_sequence = new int[this->_size];
		else
			this->_sequence = NULL;
		i = 0;
		while (i < this->_size)
		{
			this->_sequence[i] = other._sequence[i];
			i++;
		}
	}
	return (*this);
}
PmergeMe::~PmergeMe() {
	delete[] this->_sequence;
}

void	PmergeMe::print() const {
	//this->printOne(this->_vect, "std::vector<int>");
	//this->printOne(this->_deque, "std::deque<int>");
}

void	PmergeMe::run() {
	std::cout << "After: ";
	this->runVector();
	this->runDeque();
}

void	PmergeMe::runVector() {
	std::vector<int> vect;
	struct timeval start;
	struct timeval end;
	long long elapsedUS;
	gettimeofday(&start, NULL);
	vect.reserve(this->_size);
	for (size_t i = 0; i < this->_size; ++i)
		vect.push_back(this->_sequence[i]);
	this->fordJohnsonSort(vect);
	gettimeofday(&end, NULL);
	elapsedUS = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
	printContainer(vect);
	std::cout << "Time to process a range of " << vect.size() << " elements with std::vector<int>: " << elapsedUS << " us" << std::endl;
}

void	PmergeMe::runDeque() {
	std::deque<int> deq;
	struct timeval start;
	struct timeval end;
	long long elapsedUS;
	gettimeofday(&start, NULL);
	for (size_t i = 0; i < this->_size; ++i)
		deq.push_back(this->_sequence[i]);
	this->fordJohnsonSort(deq);
	gettimeofday(&end, NULL);
	elapsedUS = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
	//std::cout << "After: ";
	//printContainer(deq);
	std::cout << "Time to process a range of " << deq.size() << " elements with std::deque<int>: " << elapsedUS << " us" << std::endl;
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
