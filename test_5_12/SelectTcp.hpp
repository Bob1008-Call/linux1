#pragma once 
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <sys/select.h>

class Server 
{
public:
  Server(const int& port_)
    :port(port_)
  {}

  void InitServer()
  {
    listen_sock = socket(AF_INET,SOCK_STREAM,0);
    if(listen_sock < 0)
    {
      std::cerr << "socket error" << std::endl;
      exit(2);
    }

    int opt = 1;
    setsockopt(listen_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(port);

    if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local)) < 0)
    {
      std::cerr << "bind error" << std::endl;
      exit(3);
    }
    
    if(listen(listen_sock,5) < 0)
    {
      std::cerr << "bind error" << std::endl;
      exit(4);
    }
  }

  void Start()
  {
    while(1)
    {
      fd_set rfds;
      FD_ZERO(&rfds);
      FD_SET(listen_sock,&rfds);
      int maxfd = listen_sock;
      struct timeval timeout = {5,0};

      switch(select(maxfd+1,&rfds,NULL,NULL,&timeout))
      {
        case -1:
          std::cerr << "select error" << std::endl;
          break;
        case 0:
          std::cout << "time out .." << std::endl;
          break;
        default:
          {

          }
          break;
      }
    } 
  }
  ~Server()
  {

  }
private:
  int listen_sock;
  int port;
};

