#include <iostream>
#include <memory>
using namespace std;

class Point2
{
public:
	Point2() : X(0), Y(0)
	{
		cout << "Point2::Point2(), (" << X << "," << Y << ")" << endl;
	}
	Point2(int x, int y) : X(x), Y(y)
	{
		cout << "Point2::Point2(int x, int y), (" << X << "," << Y
		     << ")" << endl;
	}
	~Point2()
	{
		cout << "Point2::~Point2(), (" << X << "," << Y << ")" << endl;
	}

public:
	shared_ptr<Point2> Add(const Point2 *rhs)
	{
		X += rhs->X;
		Y += rhs->Y;
		return shared_ptr<Point2>(this);
	}

private:
	int X;
	int Y;
};

void TestPoint2Add()
{
	cout << endl
	     << "TestPoint2Add() >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
	shared_ptr<Point2> p1(new Point2(2, 2));
	shared_ptr<Point2> p2(new Point2(3, 3));

	p2.swap(p1->Add(p2.get()));
}

int main() { TestPoint2Add(); }
