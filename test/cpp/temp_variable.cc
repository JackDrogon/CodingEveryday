#include <iostream>
using namespace std;

class Temp {
public:
	Temp(int t) : t_(t) {}
	~Temp() { cout << t_ << endl; }
private:
	int t_;
};

int main()
{
	cout << "---------- Begin ----------" << endl;

	Temp(1);
	Temp(2);

	cout << "---------- End ----------" << endl;

	return 0;
}
