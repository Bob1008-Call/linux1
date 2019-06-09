class B {
public:
 int _b;
};

class D :virtual public B
{
public:
 int _d;
};

int main()
{
 B b;
 D d;
 cout << sizeof(b) << endl;
 cout << sizeof(D) << endl;
 d._d = 1;
 d._b = 2;
 return 0;
}
