#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <jsoncpp/json/json.h>

void ParseJson(std::string& s)
{
  int a = 0;
  std::string errs;
  Json::Value root;
  Json::CharReaderBuilder readerBuilder;
  std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
  bool res = jsonReader->parse(s.data(),s.data()+s.size(),&root,&errs);
  if(!res || !errs.empty())
  {
    std::cerr << "json parse error: " << errs << std::endl;
    return;
  }
  std::cout << "name:" << root["name"].asString() << std::endl;
  std::cout << "age:" << root["age"].asString() << std::endl;
  std::cout << "Lang:" << root["Lang"].asString() << std::endl;
}

int main()
{
  std::string s = "{\"age\":26,\"lang\":\"c++\",\"name\":\"zhangsan\"}";
  std::cout << s << std::endl;
  ParseJson(s);
  return 0;
}

