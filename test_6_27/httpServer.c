#include "tcpsocket.h" 
#define CHECK_RET(q) if((q) < 0) {return -1;}
int main()
{
  int sockfd = Socket();
  CHECK_RET(sockfd);
  CHECK_RET((Bind(sockfd,"192.168.9.166",9000)));
  CHECK_RET(Listen(sockfd));
  while(1)
  {
    char* ip;
    uint16_t port;
    int newfd = Accept(sockfd,ip,&port);
    if(newfd < 0)
    {
      continue;
    }
    printf("connect %s\n",ip);
    char buf[1024] = {0};
    Recv(sockfd,buf,sizeof(buf));
    printf("Recv:%s\n",buf);
    Close(newfd);
  }
  Close(sockfd);
  return 0;
}

