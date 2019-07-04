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
  private:
    std::string app_id = "1";
    std::string api_key= "";
    std::string secret_key = "";
    aip::Speech* client;

  public:
    SpeechRec()
    {
      client = new aip::Speech(app_id,api_key,secret_key);
    }

    //语音识别Automatic Speech Recognition
    void ASR(int& err_code,std::string& message)
    {

    }

    //语音合成text to speech 
    void TTS(std::string message)
    {
    }

    ~SpeechRec()
    {
      delete client;
      client = NULL;
    }
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
    //发起http请求
    //传入Json value 返回Json value
    Json::Value PostRequest(Json::Value data)
    {

    }

    std::string Talk(std::string& message)
    {

    }
    ~InterRobot()
    {}

};

//完成核心逻辑
class Jarvis
{
  private:
    SpeechRec sr;
    InterRobot robot;
    std::unordered_map<std::string,std::string> command_set;

  public:
    //加载命令执行配置文件
    Jarvis()
    {

    }

    //在linux中执行指定命令,采用popen
    bool Exec(std::string command,bool print)
    {

    }

    //判断消息是否是需要执行的命令，如果是命令，需要执行，而不需要焦黑图灵机器人进行对话
    bool MessageIsCommand(std::string _message,std::string& cmd)
    {

    }

    //使用arecond工具进行录音，并进行语音识别，语音转文本
    bool RecordAndASR(std::string &message)
    {
      
    }

    //使用百度语音合接口，文本转语音，在使用cvlc进行本地播放
    bool TTSAndPlay(std::string message)
    {}

    void Run()
    {
      bool ISQUIT = false;
      std::string message;
      while(!ISQUIT)
      {
        bool ret = RecordAndASR(message);//录音和识别
      }
    }
};

#endif
