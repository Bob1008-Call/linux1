#include <iostream>
using namespace std;
class Base
{
public:
        void SetBase(int pri, int pro, int pub)
        {
               _priB = pri;
               _proB = pro;
               _pubB = pub;
        }
        void Print()
        {
               cout << "_priB = " << _priB << endl;
               cout << "_proB = " << _proB << endl;
               cout << "_pubB = " << _pubB << endl;
        }
        //三个不同类的成员变量 12个字节
private:
        int _priB;
protected:
        int _proB;
public:
        int _pubB;
};
//子类或者派生类
class Dertived : public Base
{
        //测试成员变量和成员函数
public:
        void SetDerived(int pri, int pro, int pub)
        {
               _pubB = pub;
               _proB = pro;
        }
private:
        int _priD;
public:
        int _pubD;
protected:
        int _proD;
};
class C : public Dertived
{
public:
        void TestFunc()
        {
               _proB = 10;
        }
};
int main()
{
        cout << sizeof(Dertived) << endl;//输出为12，证明是继承
        Dertived d;
        d.SetBase(10, 20, 30);
        d.Print();
        getchar();
        return 0;
}
