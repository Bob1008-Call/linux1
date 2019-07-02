#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <jsoncpp/json/json.h>

int main()
{
  Json::Value root;
  Json::StreamWriterBuilder wb;
  std::ostringstream os;

  root["name"] = "zhangsan";
  root["age"] = 26;
  root["lang"] = "c++";

  std::unique_ptr<Json::StreamWriter> jsonWriter(wb.newStreamWriter());
  jsonWriter->write(root,&os);
  std::string s = os.str();

  std::cout<< s << std::endl;
  return 0;
}
