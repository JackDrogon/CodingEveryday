#include <iostream>
using namespace std;
class Point3 : public enable_shared_from_this<Point3>  
{  
public:  
    Point3() :  X(0), Y(0) { cout << "Point3::Point3(), (" << X << "," << Y << ")" << endl; }  
    Point3(int x, int y) :  X(x), Y(y) { cout << "Point3::Point3(int x, int y), (" << X << "," << Y << ")" << endl; }  
    ~Point3() { cout << "Point3::~Point3(), (" << X << "," << Y << ")" << endl; }  
       
public:  
    shared_ptr<Point3> Add(const Point3* rhs) { X += rhs->X; Y += rhs->Y; return shared_from_this();}  
   
private:  
    int X;  
    int Y;  
};  
   
void TestPoint3Add()  
{  
    cout << endl << "TestPoint3Add() >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;  
    shared_ptr<Point3> p1( new Point3(2,2) );  
    shared_ptr<Point3> p2( new Point3(3,3) );  
       
    p2.swap( p1->Add(p2.get()) );  
}  

int main() { TestPoint3Add(); }
