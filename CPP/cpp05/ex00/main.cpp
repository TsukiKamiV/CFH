#include "Bureaucrat.hpp"
/**
 *C++的异常机制：stack unwinding (栈展开）：
 *1️⃣ 检测到 throw
 	当 min.decrementGrade(); 抛出异常时，立即终止当前函数（decrementGrade()），开始寻找匹配的 catch 块。
 *2️⃣ 沿调用栈逐层回退（stack unwinding）
	 •	程序沿函数调用链向上回溯；
	 •	每离开一层函数，就会对该函数中创建的所有局部对象调用析构函数；
 	•	直到找到匹配的 catch 块。
 *================================
步骤         动作                                                                                    输出
 1            创建 Alice                                                              Constructor called for Alice with grade
 2            Alice 提升等级两次                                                Alice, bureaucrat grade …
 3            创建 Min                                                                Constructor called for Min with grade
 4            Min 调用 decrementGrade() 抛异常                     抛出异常开始栈展开
 5            栈展开 → 调用 Min 的析构函数                            Destructor called for Min
 6            栈展开 → 调用 Alice 的析构函数                          Destructor called for Alice
 7            找到 catch 块，进入                                             Caught exception: Grade too low
 8            main 结束                                                             Program ended with exit code: 0
 */
int main() {
	try {
		Bureaucrat a("Alice", 2);
		a.incrementGrade();
		std::cout << a << std::endl;
		a.incrementGrade();
	} catch (const std::exception &e) {
		std::cout << "[Alice]: " << e.what() << std::endl;
	}
	
	try {
		Bureaucrat b("Bob", 150);
		b.decrementGrade();
		std::cout << b << std::endl;
	} catch (const std::exception &e) {
		std::cout << "[Bob]: " << e.what() << std::endl;
	}
	
	try {
		Bureaucrat c("Carl", -3);
		std::cout << c << std::endl;
	} catch (const std::exception &e) {
		std::cout << "[Carl]: " << e.what() << std::endl;
	}
	return 0;
	//try {
	//	Bureaucrat b("Alice", 2);
	//	std::cout << b << std::endl;
	//	b.incrementGrade();
	//	std::cout << b << std::endl;
	//	//b.incrementGrade();
	//	//std::cout << b << std::endl;
	//	Bureaucrat min("Min", 150);
	//	std::cout << min << std::endl;
	//	min.decrementGrade();
	//}
	/**
	 *min 是在 main() 的 try 块中创建的局部对象。
	 当 min.decrementGrade() 抛出异常时：
	 •	先结束 main() 的 try 块；
	 •	在进入 catch 前，会销毁该块中已经构造的对象（min 和 b）；
	 •	所以先执行 ~Bureaucrat()；
	 •	最后才跳转到 catch 语句。
	 */
	//catch (const Bureaucrat::GradeTooHighException &e) {
	//	std::cout << "Caught exception: " << e.what() << std::endl;
	//}
	//catch (const Bureaucrat::GradeTooLowException &e) {
	//	std::cout << "Caught exception: " << e.what() << std::endl;
	//}
	//
	//catch (const std::exception &e) {
	//	std::cout << "Other error: " << e.what() << std::endl;
	//}
}
