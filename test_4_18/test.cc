#include <iostream>
using namespace std;
//class Base
//{
//public:
//  int a;
//  virtual void A(){ std::cout<<"Base::A"<<std::endl; }
//  virtual void B(){ std::cout<<"Base::B"<<std::endl; }
//  virtual void C(){ std::cout<<"Base::C"<<std::endl; }
//};
//
//int main()
//{
//  std::cout<<sizeof(Base)<<std::endl;
//  return 0;
//}

//
//class Date
//{
//public:
//  Date(int year = 2019,int month = 1,int day = 1)
//  {
//    _year = year;
//    _month = month;
//    _day = day;
//  }
//
//  bool operator==(const Date& d)
//  {
//    return d._year == _year 
//        && d._month == _month 
//        && d._day == _day;
//  }
//
//  Date& operator=(const Date& d)
//  {
//    if(this != &d)
//    {
//      _year = d._year;
//      _month = d._month;
//      _day = d._day;
//    }
//    return *this;
//  }
//
//private:
//  int _year;
//  int _month;
//  int _day;
//};
//
class A
{
public:
  A(int a)
    :_a(a)
  {}

private:
  int _a;
};
 
class B
{
public:
  B(int a ,int ref )
    :_a(a)
    ,_ref(ref)
    ,_n(10)
  {}

private:
  A _a;
  int& _ref;
  const int _n;
};

class Count
{
public:
  Count(){++_count;}

  Count(const Count& C){++_count;}

  static int GetCount(){return _count;}
private:
  static int _count;
};

int Count::_count = 0;


class Date 
{
public:
  Date(int year = 2019,int month = 1,int day = 1)
     :_year(year)
     ,_month(month)
     ,_day(day)
  {}

  static void Print(Date* d)
  {
    d->Add();
  }

  void Add()
  {
    _year++;
    _month++;
    _day++;
  }

  friend ostream& operator<<(ostream&,const Date&);

private:
  int _year;
  int _month;
  int _day;
};

ostream& operator<<(ostream& os,const Date& d)
{
  os << d._year<<" " <<d._month <<' '<<d._day;
  return os;
}

int main()
{
  Date d;
  d.Print(&d);
  return 0;
}
