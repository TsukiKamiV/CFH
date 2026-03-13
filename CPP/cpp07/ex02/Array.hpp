
#ifndef array_hpp
#define array_hpp

#include <iostream>

template <typename T>
class Array {
private:
	size_t	_size;
	T		*_data;
public:
	Array();//constructor with no parameter: creates an empty array
	Array(unsigned int n);//constructor with an unsigned int n as a parameter, creates an array of n elements initialized by default
	//The code should be able to do [ int* a = new int()], then display *a.
	Array(const Array &other);
	Array &operator=(const Array &other);
	~Array();
	
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	size_t	size() const;
};

template <typename T>
Array<T>::Array() : _size(0), _data(NULL)  {}

template <typename T>
Array<T>::Array(unsigned int n) : _size(n) {
	_data = new T[n]();
}

template <typename T>
Array<T>::Array(const Array &other) : _size(other._size) {
	_data = new T[_size];
	for (unsigned int i = 0; i < _size; i++)
		_data[i] = other._data[i];
}

//In both cases, modifying either the original array or its copy after copying mustn't affect the other array.
template <typename T>
Array<T>& Array<T>::operator=(const Array &other) {
	if (this != &other) {
		delete[] this->_data;
		this->_data = NULL;
		
		this->_size = other._size;
		if (this->_size > 0) {
			this->_data = new T[this->_size];
			for (unsigned int i = 0; i < this->_size; i++)
				this->_data[i] = other._data[i];
		}
	}
	return *this;
}

template <typename T>
Array<T>::~Array() {
	delete[] this->_data;
}

//返回类型：T& =>可修改引用
template <typename T>
T& Array<T>::operator[](size_t index) {
	if (index >= this->_size)
		throw std::out_of_range("Index out of bounds");
	return this->_data[index];
}

//返回类型：const T&（只读引用）
template <typename T>
const T& Array<T>::operator[](size_t index) const {
	if (index >= this->_size)
		throw std::out_of_range("Index out of bounds");
	return this->_data[index];
}

template <typename T>
size_t	Array<T>::size() const {
	return this->_size;
}

template <typename T>
void	printArray(const Array<T> &arr, const std::string &name) {
	std::cout << name << " (size=" << arr.size() << "): ";
	for(size_t i = 0; i < arr.size(); i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

#endif
