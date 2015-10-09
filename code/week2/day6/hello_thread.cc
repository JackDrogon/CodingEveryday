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

	std::thread t2{BackgroudTask()};
	t2.join();

	return 0;
}
