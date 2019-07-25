#include <iostream>
using namespace std;
#if 0
class Date
{
  public:
    Date(int year = 1999,int month = 10,int day = 8)
      :_year(year)
      ,_month(month)
      ,_day(day)
    {}

    friend void Time(Date );
  private:
    int _year;
    int _month;
    int _day;
    static int s;
};

void Time(Date d)
{
  d._year = 1;
  d.s = 2;
}
#endif

class Date
{
  public:
    Date(int year = 100,int month = 10,int day = 10)
      :_year(year)
      ,_month(month)
      ,_day(day)
    {}

    class Inside 
    {
      public:
        Inside(int iyear = 1,int imonth = 1,int iday = 1)
        {
          _iyear = iyear;
          _imonth = imonth;
          _iday = iday;
        }

        void Print(Date d)
        {
          cout << "year:" << d._year << "month:" << d._month << "day:" << d._day<< endl;  
        }
      private:
        int _iyear;
        int _imonth;
        int _iday;
    };

  private:
    int _year;
    int _month;
    int _day;
};

int main()
{
  Date::Inside i;
  Date d;
  
  i.Print(d);
  return 0;
}
