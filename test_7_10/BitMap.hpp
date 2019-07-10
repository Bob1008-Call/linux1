#include <iostream>
#include <vector>
using namespace std;

class BitMap
{
  public:
    BitMap()
    {}

    BitMap(size_t size)
    {
      _table.resize((size >> 5) + 1);
    }

    void Set(int val)
    {
      size_t byteNo = val >> 5;
      size_t bitNo = val % 32;
      _table[byteNo] |= (1 << bitNo);
    }

    void Reset(int val)
    {
      size_t byteNo = val >> 5;
      size_t bitNo = val % 32;
      _table[byteNo] &= ~(1 << bitNo);
    }

    bool Test(int val)
    {
      size_t byteNo = val >> 5;
      size_t bitNo = val % 32;
      if((1 << bitNo) & _table[byteNo])
      {
        return true;
      }
      else 
      {
        return false;
      }
    }
  private:
    vector<int> _table;
};


