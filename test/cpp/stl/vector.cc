#include <iostream>
#include <vector>

using namespace std;

int main()
{
	// vector<int> ivec1(); cpp解析问题，此处不应该不能嵌套定义函数吗？
	vector<int> ivec1{};
	cout << "size = " << ivec1.size() << endl;
	cout << "capacity = " << ivec1.capacity() << endl;
	cout << "========================================" << endl;

	vector<int> ivec2(3, 9);
	cout << "size = " << ivec2.size() << endl;
	cout << "capacity = " << ivec2.capacity() << endl;
	cout << "========================================" << endl;

	return 0;
}
