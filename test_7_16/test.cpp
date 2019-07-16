#include <string>
#include <iostream>
using namespace std;
class Person
{
public:
	Person()
	{
		++_count;
	}

protected:
	string _name; 

public:
	static int _count;
};

int Person::_count = 0;

class Student :public Person
{
protected:
	int _stuNum;
};

class Graduate :public Student
{
protected:
	string _seminarCourse;
};

void test()
{
	Student s1;
	cout << "人数" << Person::_count << endl;
	Student s2;
	cout << "人数" << Person::_count << endl;
	Student s3;
	cout << "人数" << Person::_count << endl;
	Graduate s4;
	cout << "人数" << Person::_count << endl;
	Student::_count = 0;
	cout << "人数" << Person::_count << endl;
}
