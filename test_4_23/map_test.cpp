#include <map>
#include <iostream>
using namespace std;

int main()
{
  map<string,string> stringmap;
  map<string,string>::const_iterator it;
  stringmap["孙悟空"] = "齐天大圣";
  stringmap["猪八戒"] = "天蓬元帅";
  it = stringmap.find("猪八戒");
  cout<<stringmap.find("猪八戒")->second<<endl;
  return 0;
}


