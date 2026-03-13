
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <ctime>

/**
 *1️⃣ 多态与虚函数表 (vtable)                  只有含有虚函数的类，才能支持运行时类型识别 (dynamic_cast)
 *2️⃣ dynamic_cast 的工作机制               在运行时查询对象的真实类型（RTTI）
 *3️⃣ Base 析构函数必须为虚                  确保通过基类指针删除派生类对象时安全释放内存
 *4️⃣ 异常处理 (try/catch)                         在 dynamic_cast<Base&> 转换失败时会抛出 std::bad_cast 异常
 *5️⃣ 随机对象生成 (generate)                 工厂函数（factory function）思想：根据随机数返回不同的派生对象
 *6️⃣ 指针 vs 引用 dynamic_cast 区别     指针失败返回 NULL，引用失败抛异常
 */

Base	*generate(void);
void	identify(Base *p);
void	identify(Base& p);

int main(void) {
	std::srand(std::time(NULL));
	
	for (int i = 0; i < 5; i++) {
		Base* base = generate();
		std::cout << "\nTest" << i + 1 << ":" << std::endl;
		std::cout << "Identity by pointer: ";
		identify(base);
		std::cout << "Identify by reference: ";
		identify(*base);
		delete base;
	}
}

Base	*generate(void) {
	int	n = std::rand() % 3;
	switch (n) {
		case 0: return new A;
		case 1: return new B;
		default: return new C;
	}
}

void	identify(Base *p) {
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unkown" << std::endl;
}

void	identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
	} catch (...) {
		try {
			(void)dynamic_cast<B&>(p);
			std::cout << "B" << std::endl;
		} catch (...) {
			try {
				(void)dynamic_cast<C&>(p);
				std::cout << "C" << std::endl;
			} catch (...) {
				std::cout << "Unknown" << std::endl;
			}
		}
	}
}
