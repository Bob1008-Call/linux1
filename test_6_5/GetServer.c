#include "common.h"
#include <time.h>

#define MAXLINE 1024
#define LISTENQ 5

int Socket(int family,int type,int protocol)
{
  int n;
  if((n = socket(family,type,protocol)) < 0)
  {
    perror("socket error");
  }
  return (n);
}

int Bind(int fd,struct sockaddr* addr,socklen_t size)
{
  int n;
  if((n = bind(fd,addr,size)) < 0)
  {
    perror("bind error");
  }
  return n;
}

int Listen(int family,int max)
{
  int n;
  if((n = listen(family,max)) < 0)
  {
    perror("listen error");
  }
  return n;
}

int Accept(int fd,struct sockaddr* cli_addr,socklen_t* addrlen)
{
  int n;
  if((n = accept(fd,cli_addr,addrlen) < 0))
  {
    perror("accept error");
  }
  return n;
}

int main()
{
  int listen_fd,connect_fd;
  struct sockaddr_in server_addr;
  char buff[MAXLINE];
  time_t ticks;

  listen_fd = Socket(AF_INET,SOCK_STREAM,0);

  bzero(&server_addr,sizeof(server_addr));

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(13);

  Bind(listen_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
  Listen(listen_fd,LISTENQ);

  for(;;)
  {
    connect_fd = Accept(listen_fd,(struct sockaddr*)NULL,NULL);
    ticks = time(NULL);
    snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
    write(connect_fd,buff,strlen(buff));
    close(connect_fd);
  }
  
  return 0;
}
