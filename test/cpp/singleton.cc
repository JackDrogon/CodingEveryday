#include <iostream>
using namespace std;

class Singleton {
	Singleton() {}


	static Singleton *instance;

public:
	~Singleton() { cout << "Singleton dtor" << endl; }

	struct GC {
			~GC() { if(instance) { cout << "Delete Singleton" << endl; delete instance; } }
	};

private:
	static GC gc;

public:
	static Singleton *Instance() {
		if (!instance) {
			instance = new Singleton;
		}

		return instance;
	}

};

Singleton *Singleton::instance = NULL;
Singleton::GC gc;

int main()
{
	Singleton *s = Singleton::Instance();

	// delete t;

	return 0;
}
