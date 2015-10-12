#include <iostream>
#include <string>
#include <exception>
#include "Queue.hpp" // use special queue class
using namespace std;

int main()
{
	try {
		Queue<string> q;

		// insert three elements into the queue
		q.push("These ");
		q.push("are ");
		q.push("more than ");

		// pop two elements from the queue and print their value
		cout << q.pop();
		cout << q.pop();

		// push two new elements
		q.push("four ");
		q.push("words!");

		// skip one element
		q.pop();

		// pop two elements from the queue and print their value
		cout << q.pop();
		cout << q.pop() << endl;

		// print number of remaining elements
		cout << "number of elements in the queue: " << q.size() << endl;

		// read and print one element
		cout << q.pop() << endl;
	} catch (const exception &e) {
		cerr << "EXCEPTION: " << e.what() << endl;
	}
}
