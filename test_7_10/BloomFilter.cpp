#include "BitMap.hpp"
#include "Common.h"
#include <string>

template<class T,class Fun1 = _Fun1<T>,
                 class Fun2 = _Fun2<T>,
                 class Fun3 = _Fun3<T>,
                 class Fun4 = _Fun4<T>,
                 class Fun5 = _Fun5<T>>
class BloomFilter
{
  public:
    BloomFilter(size_t size)
      :_bm(size)
      ,_capacity(size)
    {}

    void Insert(const T& key)
    {
      size_t idx1 = Fun1()(key) % _capacity;
      _bm.Set(idx1);
      size_t idx2 = Fun2()(key) % _capacity;
      _bm.Set(idx2);
      size_t idx3 = Fun3()(key) % _capacity;
      _bm.Set(idx3);
      size_t idx4 = Fun4()(key) % _capacity;
      _bm.Set(idx4);
      size_t idx5 = Fun5()(key) % _capacity;
      _bm.Set(idx5);
      cout << idx1 << "" << idx2 << "" << idx3 << "" << idx4 << "" << idx5 << ""  << endl;
    }

    bool Find(const T& key)
    {
      size_t idx1 = Fun1()(key) % _capacity;
      size_t idx2 = Fun2()(key) % _capacity;
      size_t idx3 = Fun3()(key) % _capacity;
      size_t idx4 = Fun4()(key) % _capacity;
      size_t idx5 = Fun5()(key) % _capacity;
      if(!_bm.Test(idx1))
        return false;
      if(!_bm.Test(idx2))
        return false;
      if(!_bm.Test(idx3))
        return false;
      if(!_bm.Test(idx4))
        return false;
      if(!_bm.Test(idx5))
        return false;
      cout << idx1 << "" << idx2 << "" << idx3 << "" << idx4 << "" << idx5 << ""  << endl;
    }
  private:
    BitMap _bm;
    size_t _capacity;
};

void FunTest()
{
    BloomFilter<string> bf(100);
    bf.Insert("圆通");
    bf.Insert("韵达");
    bf.Insert("天天");
    bf.Insert("汇通");
    bf.Insert("中通");
    cout<<bf.Find("天天")<<endl;
    cout << bf.Find("邮政")<<endl;
}

int main()
{
  FunTest();
  return 0;
}
