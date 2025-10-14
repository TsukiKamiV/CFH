#include "Zombie.hpp"
int main() {
	/**
	 *  栈（stack）对象：Zombie z1
	 *	生命周期：进入作用域时构造；离开作用域自动析构（不需要也不允许 delete）。
	 *  所有权：由当前作用域“拥有”，无法把“对象本体”安全地返回（可以返回拷贝，不能返回指向局部对象的指针/引用）。
	 *  异常安全：异常抛出时也会自动析构（RAII）。
	 *  性能：创建和销毁非常快，无需堆分配。
	 *  用法适配：像 randomChump("...") 这种“临时用一下就结束”的场景就该用栈对象
	 */
	randomChump("Foo the stack zombie");
	
	/**
	 * 堆（heap）对象：Zombie* p = newZombie
	 * 生命周期：由你决定；必须手动 delete，否则内存泄漏。
	 * 所有权：可以把指针传出当前作用域，由调用者负责销毁。
	 * 异常安全：如果中途异常，容易漏 delete（要小心在复杂逻辑里及时释放）。
	 * 性能：有分配/释放开销（new/delete）。
	 * 用法适配：当你需要“把对象活得更久/跨作用域传递”时用堆对象
	 */
	Zombie* z2 = newZombie("Bar the heap zombie");
	z2->announce();
	delete z2;
	
	return 0;
}
