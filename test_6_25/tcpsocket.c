#ifndef __M_TCP_H__
#define __M_TCP_H__
/*
 * int Socket();
 * int Bind(int sockfd,const char* ip,const uint16_t port);
 * int Listen(int sockfd);
 * int Connect(int sockfd,const char* ip,const uint16_t port);
 * int Accept(int sockfd,char *cliip,uint16_t *cliport);
 * 获取新客户端的socket，用于后续与客户端的通信，并且可以获取客户端的地址信息，并且返回新连接操作句柄
 * int Recv(int sockfd,char* buf,int len);接收数据放到buf中，
 * int Send(int sockfd,const char* data,int len);
 * int Close(int sockfd);
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CONN    10
int Socket()
{
  //int socket(int domain, int type, int protocol);
  int sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  if(sockfd < 0)
  {
    return -1;
  }
  return sockfd;
}

int Bind(int sockfd,const char* ip,uint16_t port)
{
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  //in_addr_t inet_addr(const char* cp)//将点分十进制字符串ip地址转换为32位网络字节序整数
  addr.sin_addr.s_addr = inet_addr(ip);

  //int bind(int sockfd,struct sockaddr *addr,socklen_t addrlen);
  socklen_t len = sizeof(struct sockaddr_in);
  int ret = bind(sockfd,(struct sockaddr*)&addr,len);
  if(ret < 0)
  {
    return -1;
  }
  return 0;
}

int Listen(int sockfd)
{
  int ret = listen(sockfd,MAX_CONN);
  if(ret < 0)
  {
    return -1;
  }
  return 0;
}

int Connect(int sockfd,const char* ip,uint16_t port)
{
  struct sockaddr_in ser_addr;
  ser_addr.sin_family = AF_INET;
  ser_addr.sin_port = htons(port);
  ser_addr.sin_addr.s_addr = inet_addr(ip);
  
  socklen_t len = sizeof(ser_addr);
  int ret = connect(sockfd,(struct sockaddr*)&ser_addr,len);
  if(ret < 0)
  {
    return -1;
  }
  return 0;
}

int Accept(int sockfd,char* cliip,uint16_t *cliport)
{
  struct sockaddr_in cliaddr;
  socklen_t len = sizeof(struct sockaddr_in);

  int newfd = accept(sockfd,(struct sockaddr*)&cliaddr,&len);
  if(newfd < 0)
  {
    return -1;
  }
  cliip = inet_ntoa(cliaddr.sin_addr);//将网络字节序的整数IP地址转换为点分十进制字符串ip地址
  *cliport = ntohs(cliaddr.sin_port);
  return newfd;
}

int Recv(int sockfd,char* buf,int len)
{
  int ret = recv(sockfd,buf,len,0);
  if(ret < 0)
  {
    printf("recv error\n");
    return -1;
  }
  else if(ret == 0)
  {
    printf("connect shutdown\n");
    return 0;
  }
  return ret;
}

int Send(int sockfd,char* buf,int len)
{
  int ret = send(sockfd,buf,len,0);
  if(ret < 0)
  {
    return -1;
  }
  return ret;
}
int Close(int sockfd)
{
  close(sockfd);
  return 0;
}
#endif

