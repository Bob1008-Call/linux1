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

#define SPEECH_FILE "temp_file/demo.wav"
#define PLAY_FILE "temp_file/play.mp3"
#define CMD_ETC "command.etc"

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
      std::cout<<std::endl<<"正在识别...."<<std::endl;
      std::map<std::string,std::string> options;
      options["dev_pid"] = "1536";
      options["lan"] = "ZH";

      std::string file_content;
      aip::get_file_content(SPEECH_FILE,&file_content);
      

      Json::Value result = client->recognize(file_content,"wav",16000,options);
      err_code = result["err_no"].asInt();
      if(err_code == 0)
      {
        message = result["result"][0].asString();
      }
      else 
      {
        message="识别错误...";
      }
    }

    //语音合成text to 
    void TTS(std::string message)
    {
      std::ofstream ofile;
      std::string file_ret;
      std::map<std::string,std::string> options;
      options["spd"] = "5";
      options["per"] = "0";
      
      ofile.open(PLAY_FILE,std::ios::out | std::ios::binary);

      Json::Value result = client->text2audio(message,options,file_ret);
      if(!file_ret.empty())
      {
        ofile << file_ret;
      }
      else 
      {
        std::cout << "error:" << result.toStyledString();
      }
      ofile.close();
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
      std::string response;
      Json::Value obj;
      Json::CharReaderBuilder crBuilder;
      int code = this->client.post(url,nullptr,data,nullptr,&response);
      if(code != CURLcode::CURLE_OK)
      {
        obj[aip::CURL_ERROR_CODE]=code;
        return obj;
      }
      std::string error;
      std::unique_ptr<Json::CharReader> reader(crBuilder.newCharReader());
      reader->parse(response.data(),response.data()+response.size(),&obj,&error);
      return obj;
    }

    std::string Talk(std::string& message)
    {
      Json::Value root;
      Json::Value item1;
      Json::Value item2;
      root["reqType"] = 0;
      item1["text"] = message;
      item2["inputText"] = item1;
      item1.clear();
      root["perception"] = item2;
      item2.clear();
      item2["apikey"] = api_key;
      item2["userId"] = user_id;
      root["userInfo"] = item2;
      item2.clear();

      Json::Value ret = PostRequest(root);
      Json::Value _result = ret["results"];
      Json::Value values = _result[0]["values"];
      std::cout<< "Robot" << values["text"].asString() << std::endl;
      return values["text"].asString();
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
      char buffer[256];
      std::ifstream in(CMD_ETC);
      if(!in.is_open())
      {
        std::cerr << "open file error" << std::endl;
        exit(1);
      }
      std::string sep=":";
      while(in.getline(buffer,sizeof(buffer)))
      {
        std::string str = buffer;
        std::size_t pos = str.find(sep);
        if(std::string::npos == pos)
        {
          std::cerr << "Load Etc Error" << std::endl;
          exit(2);
        }
        std::string k = str.substr(0,pos);
        std::string v = str.substr(pos+sep.size());
        k += "。";
        command_set.insert(std::make_pair(k,v));
      }
      std::cout << "Load command etc ... done" << std::endl;
      in.close();
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
