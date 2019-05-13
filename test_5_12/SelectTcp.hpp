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

#define DEFAULT_FD -1

class Server 
{
public:
  Server(const int& port_)
    :port(port_)
  {}

  void InitServer()
  {
    fd_array = new int[sizeof(fd_set)*8];
    for(auto i = 0;i < sizeof(fd_set)*8;++i)
    {
      fd_array[i] = DEFAULT_FD;
    }
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

  int AddAllFd(int fds[],fd_set& rfds)
  {
    int max = fds[0];
    for(auto i =0;i < size;++i)
    {
      if(fds[i] == DEFAULT_FD)
      {
        continue;
      }
      FD_SET(fds[i],&rfds);
      if(max < fds[i])
      {
        max = fds[i];
      }
    }
    return max;
  }

  bool Addfd(int fd,int fds[])
  {
    if(size < sizeof(fd_set)*8)
    {
      fds[size] = fd;
      size++;
      return true;
    }
    return false;
  }
  void DelFd(int index,int fds[])
  {
    size--;
    fds[index] = fds[size];
    fds[size-1] = DEFAULT_FD;
  }

  void Start()
  {
    fd_array[0] = listen_sock;
    size = 1;
    while(1)
    {
      fd_set rfds;
      FD_ZERO(&rfds);

      int maxfd = AddAllFd(fd_array,rfds);

      FD_SET(listen_sock,&rfds);
      struct timeval timeout = {20,0};

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
            for(auto i = 0;i < size; ++i)
            {
              if(i == 0 && FD_ISSET(listen_sock,&rfds))
              {
                std::cout << "get a new connect..."<<std::endl;
                struct sockaddr_in peer;
                socklen_t len = sizeof(peer);
                int sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
                if(sock < 0)
                {
                  std::cerr << "accept error" <<std::endl;
                  continue;
                }
                if(!Addfd(sock,fd_array))
                {
                  std::cout << "sock full" << std::endl;
                  close(sock);
                }
              }
              else if(FD_ISSET(fd_array[i],&rfds))
              {
                char buf[10240];
                ssize_t s = recv(fd_array[i],buf,sizeof(buf)-1,0);
                close(fd_array[i]);
                DelFd(i,fd_array);
                std::cout<< "echo HTTP response Done!"<< std::endl;
                if(s > 0)
                {
                  buf[s] = 0;
                  std::cout << buf << std::endl;
                  const std::string echo_http = "HTTP/1.0 200 OK\r\n\r\n<html>hello select!</html>\r\n";
                  send(fd_array[i],echo_http.c_str(),echo_http.size(),0);
                  
                }
                else if(s == 0)
                {
                  std::cout << "client quit..." << std::endl;
                  close(fd_array[i]);
                  DelFd(i,fd_array);
                }
                else 
                {
                  std::cerr << "recv error"<< std::endl;
                }
              }
            } 
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
  int *fd_array;
  int size;
};

