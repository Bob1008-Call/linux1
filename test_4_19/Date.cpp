//class Date
//{
//public:
//  //Date()
//  //{
//  //  _year = 2019;
//  //  _month = 1;
//  //  _day = 1;
//  //}
//
//  Date(int year = 2019,int month = 1,int day = 1)
//  {
//    _year = year;
//    _month = month;
//    _day = day;
//  }
//
//private:
//  int _year;
//  int _month;
//  int _day;
//};
//
//int main()
//{
//  return 0;
//}
#include <iostream>
using namespace std;
class Time
{
public:
  Time()
  {
    cout<<"Time()"<<endl;
    _hour = 0;
    _minute = 0;
    _second = 0;
  }

private:
  int _hour;
  int _minute;
  int _second;
};

class Date
{
private:
  int _year;
  int _month;
  int _day;

  Time _t;
};

int main()
{
  Date d;
  return 0;
}
