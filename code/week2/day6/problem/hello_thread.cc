#include <iostream>
#include <thread>

using namespace std;

void hello()
{
	cout << "Hello CPP Thread!" << endl;
}

class BackgroudTask
{
public:
	void operator()() const
	{
		cout << "Hello Background Task!" << endl;
	}
};

int main()
{

	std::thread t1(hello);
	t1.join();

	std::thread t2(BackgroudTask);
	// 为什么此处join就是不成功，把BackgroundTask换成struct也不成功但是单独声明 BackgroundTask f就行了呢。看一下代码
	// 报错是member reference base type 'std::thread (BackgroudTask)' is not a structure or union
	
	// 如果你传递了一个临时变量，而不是一个命名的变量；C++编译器就会将其解析为一个函数声明，而不是一个对象的定义。
	// std::thread my_thread((background_task()));  // 1
	// std::thread my_thread{background_task()};    // 2
	t2.join();

	return 0;
}
