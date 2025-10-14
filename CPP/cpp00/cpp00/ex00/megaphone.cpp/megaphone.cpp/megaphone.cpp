#include <iostream>
#include <cctype>
#include <string>

/**
 * "::"作用域解析运算符（scope resolution operator),
 * namespace_name::identifier
 * 它的作用是告诉编译器：“去某个作用域里找这个名字”。
 * std::cout  ：从 std 命名空间里取出 cout 对象。
 * std::string ：从 std 命名空间里取出 string 类。
 * std::toupper ：从 std 命名空间里取出 toupper 函数。
 *******************************************
 * "<<"
 * 叫做 流插入运算符（insertion operator）。
 * 在这里表示“把右边的东西插入到左边的输出流里”。
 * 所以 std::cout << "Hello"; 的意思就是“把字符串 Hello 输出到标准输出流（屏幕）”。
 * *****************************************
 * std::endl
 * 是一个特殊的 操纵符（manipulator），相当于对输出流做一次操作。
 * 作用：
 *   1输出一个换行符（相当于 '\n'）。
 *   2刷新缓冲区（flush） —— 确保缓冲区里的内容立刻写到屏幕上。
 */
int	main(int ac, char *av[])
{
	if (ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	for (int i = 1; i < ac; i++)
	{
		std::string str = av[i];
		//从 std::string 这个类作用域里，取出 size_type 这个类型。
		//调用 str.length() 时，编译器会自动在 std::string 类的作用域里去找 length()，因为 str 是这个类的实例（instance)。
		for (std::string::size_type j = 0; j < str.length(); ++j)
		{
			//unsigned char uch = static_cast<unsigned char>(str[j]);
			//toupper的参数必须是unsigned char 或EOF
			/**最常见的强制类型转换方式，可以做数值类型之间的转换、指针向上/向下转型（继承层次中），但不做危险的转换。
			 *int a = 65;
			 *char c = static_cast<char>(a); // int -> char
			 *toupper原型：int std::toupper(int ch);
			*/
			//char upper = static_cast<char>(std::toupper(uch));
			std::cout << static_cast<char>(std::toupper(static_cast<unsigned char>(str[j])));
		}
		if (i + 1 != ac)
			std::cout << " ";
	}
	std::cout << std::endl;
	return (0);
}
