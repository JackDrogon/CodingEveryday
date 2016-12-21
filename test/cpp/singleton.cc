#include <iostream>
using namespace std;

class Singleton {
public:
	static Singleton *Instance() {
		if (!instance) {
			instance = new Singleton;
		}

		return instance;
	}

	~Singleton() { cout << "Singleton dtor" << endl; }

protected:
	Singleton() {}

private:
	struct GC {
			~GC() { if(instance) { cout << "Delete Singleton" << endl; delete instance; } }
	};

	static GC gc;
	static Singleton *instance;
};

Singleton *Singleton::instance = NULL;
// FIXME: Singleton::GC gc; => error, why ?
Singleton::GC Singleton::gc;

int main()
{
	Singleton *s = Singleton::Instance();

	// delete t;

	return 0;
}
