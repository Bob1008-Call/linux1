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
