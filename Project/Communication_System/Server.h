#ifndef __COMMUNICATION_SYSTEM_SERVER_H__
#define __COMMUNICATION_SYSTEM_SERVER_H__ 

#include <string>
#include "Common.h"
using namespace std;

class Server 
{
public:
  //无参构造函数
  Server();

  //初始化服务器
  void Init();

  //关闭服务器
  void Close();

  //启动服务器
  void Start();

private:
  //广播消息给所有客户端
  int SendBroadcastMessage(int clientfd);

  //服务器段 serverAddr信息
  struct sockaddr_in serverAddr;
 
  //创建监听的套接字
  int listener;

  //epoll_create创建后的返回值
  int epfd;

  //客户端列表
  list<int> clients_list;
};

#endif
