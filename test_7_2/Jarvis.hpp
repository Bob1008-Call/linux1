#ifndef _JARVIS_
#define _JARVIS_ 

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unordered_map>
#include "speech.h"
#include "base/http.h"

//访问百度语言识别类
class SpeechRec
{
};

//图灵机器人交互类
class InterRobot 
{
  private:
    //注册图灵账号对应的url
    std::string url = "openapi.tuling123.com/openapi/api/v";
    //所注册的图灵账号对应的apikey
    std::string api_key = "";
    //用户id
    std::string user_id = "";
    //使用百度语音
    aip::HttpClient client;
  public:
    InterRobot()
    {}
};

//完成核心逻辑
class Jarvis
{};

#endif
