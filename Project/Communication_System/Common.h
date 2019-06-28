#ifndef __COMMUNICATION_SYSTEM_COMMON_H__
#define __COMMUNICATION_SYSTEM_COMMON_H__ 

#include <iostream>
#include <list>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

//默认服务器IP地址
#define SERVER_IP "127.0.0.1"

//服务器端口号
#define SERVER_PORT 8080

//epoll支持的最大句柄数
#define EPOLL_SIZE 5000

//缓冲区大小
#define BUFF_SIZE 0XFFFF

//新用户登陆
#define SERVER_WELCOME "Welcome to our system! Your chat ID is: Client #%d"

//其他用户收到消息的格式
#define SERVER_MESSAGE "ClientID %d say >> %s"

//私聊用户收到的格式
#define SERVER_PRIVATE_MESSAGE "Client %d say to you privately >> %s"

//私聊不在线用户反馈给当前用户的格式
#define SERVER_PRIVATE_ERROR_MESSAGE "Client %d is not int the chatroom ~ "

//退出系统
#define EXIT "EXIT"

//聊天室只有唯一的客户端
#define CAUTION "There is only one int the chatroom! "

/*
typedef union epoll_data {
    void *ptr;
    int fd;
    uint32_t u32;
    uint64_t u64;
}epoll_data_t;

struct epoll_event {
    uint32_t events; // Epoll events 
    epoll_data_t data; // User data variable 
};
*/
//注册新的 fd 到 epoll 中
//参数 enable_et 表示是否使用 ET 模式，如果为 True 则启用
static void addfd(int epollfd,int fd,bool enable_et)
{
  struct epoll_event ev;
  ev.data.fd = fd;
  ev.events = EPOLLIN;
  if(enable_et)
  {
    ev.events = EPOLLIN | EPOLLET;
  }
  epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
  //设置socket为非阻塞模式
  //套接字立刻返回，不管I/O是否完成，该函数所在的线程继续运行
  fcntl(fd,F_SETFL,fcntl(fd,F_GETFD,0) | O_NONBLOCK);
  printf("fd added to epoll!\n\n");
}

struct Msg
{
  int type;  //如果为1，则代表为私聊
  int fromID;//消息从哪个客户端来
  int toID;  //消息到哪个客户端去
  char content[BUFF_SIZE];//每条消息的内容用字符数组来存储
};

#endif
