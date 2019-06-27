#ifndef __M_TCP_H__
#define __M_TCP_H__ 
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAX_CONN 10
int Socket();
int Bind(int sockfd,const char* ip,uint16_t port);
int Listen(int sockfd);
int Connect(int sockfd,const char* ip,uint16_t port);
int Accept(int sockfd,char* cliip,uint16_t* port);
int Recv(int sockfd,char* buf,int len);
int Send(int sockfd,char* buf,int len);
int Close(int sockfd);
#endif
