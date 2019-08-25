#include <iostream>
using namespace std;
#include <string>
//
//class Person
//{
//public:
//	void Print()
//	{
//		cout << "name:" << _name << endl;
//		cout << "age:" << _age << endl;
//	}
//protected:
//	string _name = "Peter";
//	int _age = 18;
//};
//
//class Student: public Person
//{
//protected:
//	int _stuid;
//};
//
//class Teacher :public Person
//{
//protected:
//	int _jobid;
//};
//
//int main()
//{
//	Student s;
//	Teacher t;
//	cout << sizeof(Teacher) << endl;
//	cout << sizeof(Student) << endl;
//	s.Print();
//	t.Print();
//	getchar();
//	return 0;
//}
//#include <iostream>
//using namespace std;
//class Base
//{
//public:
//	void SetBase(int pri, int pro, int pub)
//	{
//		_priB = pri;
//		_proB = pro;
//		_pubB = pub;
//	}
//	void Print()
//	{
//		cout << "_priB = " << _priB << endl;
//		cout << "_proB = " << _proB << endl;
//		cout << "_pubB = " << _pubB << endl;
//	}
//	//三个不同类的成员变量 12个字节
//private:
//	int _priB;
//protected:
//	int _proB;
//public:
//	int _pubB;
//};
////子类或者派生类
//class Dertived : public Base
//{
//	//测试成员变量和成员函数
//public:
//	void SetDerived(int pri, int pro, int pub)
//	{
//		_pubB = pub;
//		_proB = pro;
//	}
//private:
//	int _priD;
//public:
//	int _pubD;
//protected:
//	int _proD;
//};
//class C : public Dertived
//{
//public:
//	void TestFunc()
//	{
//		_proB = 10;
//	}
//};
//int main()
//{
//	cout << sizeof(Dertived) << endl;//输出为12，证明是继承
//	Dertived d;
//	d.SetDerived(10, 20, 30);
//	getchar();
//	return 0;
//}

//class Base
//{
//public:
//	int _b;
//};
//
//class Derived : public Base
//{
//public:
//	int _b;
//};
//
//int main()
//{
//	Derived D;
//	Base B;
//	Base& rB = D;
//	Base *pB = &D;
//	
//	//Derived *pD = &B;错误语句
//	D._b = 1;
//	B._b = 2;
//	cout<<"size:"<<sizeof(D) << endl;
//	cout << D._b << endl;
//	cout << B._b << endl;
//	getchar();
//	return 0;
//}

//class Person
//{
//protected:
//	string _name;
//	int _num;
//};
//
//class student :public Person
//{
//public:
//	/*void Print()
//	{
//		cout << "姓名" << endl;
//	}*/
////protected:
//	int _num;
//};
//
//void test()
//{
//	student sobj;
//	Person pobj = sobj;//子类对象可以赋值给基类对象/指针/引用
//	Person* pp = &sobj;
//	Person& rp = sobj;
//
//	//sobj = pobj; 会出错：因为基类对象不能赋值给派生类对象
//
//	pp = &sobj;
//	student* ps1 = (student*)pp;
//	ps1->_num = 10;
//
//	pp = &pobj;
//	student* ps2 = (student*)pp;
//	ps2->_num = 10;
//}
//
//int main()
//{
//	test();
//	return 0;
//
//}

class Person
{
public:
	Person(const char* name = "Peter")
		:_name(name)
	{
		cout << "Person()" << endl;
	}

	Person(const Person& p)
		:_name(p._name)
	{
		cout << "Person(const Person& p)"<<endl;
	}

	Person& operator=(const Person& p)
	{
		cout << "Person operator=(const Person& p)" << endl;
		if (this != &p)
		{
			_name = p._name;
		}
		
		return *this;
	}

	~Person()
	{
		cout << "~Person()" << endl;
	}

protected:
	string _name;
};

class Student :public Person
{
public:
	Student(const char* name, int num)
		:Person(name)//1.这里必须显式调用
		, _num(num)
	{
		cout << "Student()" << endl;
	}

	Student(const Student& s)
		:Person(s)
		, _num(s._num)
	{
		cout << "Student(const Student& s)" << endl;
	}

	Student& operator=(const Student& s)
	{
		cout << "Student& operator=(const Student& s)" << endl;
		if (this != &s)
		{
			Person::operator=(s);//先调用基类的构造函数完成对基类的初始化
			_num = s._num;
		}

		return *this;
	}

	~Student()
	{
		cout << "~Student()" << endl;
	}
protected:
	int _num;
};

void test()
{
	Student s1("Jack", 18);
}

int main()
{
	test();
	return 0;
}
