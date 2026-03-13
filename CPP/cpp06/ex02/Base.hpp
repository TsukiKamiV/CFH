
#ifndef Base_hpp
#define Base_hpp

#include <string>

class Base {
public:
	virtual ~Base();
	/**
	 *1. 为什么 Base 要有一个虚析构函数:
	 *	•	一旦有虚函数，编译器就会为类生成一个 vtable（虚函数表）。
	 	•	这张表会记录当前对象的真实类型（即派生类类型）。
	 	•	dynamic_cast 就依靠这张表在运行时判断对象到底是谁。
	 *	同时，虚析构函数还能确保：
	 *	Base* base = new A;
		delete base; // ✅ 自动调用 A::~A() + Base::~Base() <= 如果没有虚析构函数，这句 delete base 		就是 未定义行为（UB）。
	 */
};

#endif
