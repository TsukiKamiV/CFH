
#ifndef iter_hpp
#define iter_hpp

#include <iostream>

//iter无法检测传入的array的长度，无法检查len是否超出长度范围
template <typename T, typename F>
void	iter(T *array, const size_t len, F func) {
	for (size_t i = 0; i < len; ++i)
		func(array[i]);
}

template <typename T>
void	print(const T &x) {
	std::cout << x << std::endl;
}

template <typename T>
void	square(T &x) {
	std::cout << x << " square is ";
	x = x * x;
	std::cout << x << std::endl;
}
//============== Iter for struct ===============//

struct Point {
	int	x;
	int	y;
};

std::ostream &operator<<(std::ostream &out, const Point p) {
	out << "(" << p.x << ", " << p.y << ")";
	return out;
}

//============== Iter for class ================//
class Whatever {
public:
	Whatever(int n = 0) : _n(n) {}
	int getValue() const {return _n;}
private:
	int	_n;
};

std::ostream &operator<<(std::ostream &out, const Whatever &other) {
	out << other.getValue();
	return out;
}

#endif
