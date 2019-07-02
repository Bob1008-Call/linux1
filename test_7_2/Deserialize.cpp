#include <iostream>
#include <sstream>
#include <memory>
#include <string>
#include <jsoncpp/json/json.h>

void ParseJson(std::string& s)
{
  std::string errs;
  Json::Value root;
  Json::CharReaderBuilder readerBuilder;
  std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
  bool res = jsonReader->parse(s.data(),s.data()+s.size())
}
