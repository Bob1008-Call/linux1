#include "tcpsocket.h"
#define CHECK_RET(q) if((q) < 0){return -1;}

int main()
{
  int lstfd = Socket();
  CHECK_RET(lstfd);
  CHECK_RET(Bind(lstfd,"192.168.9.166",9000));
  CHECK_RET(Listen(lstfd));
  while(1)
  {
    char* cliip;
    uint16_t cliport;
    int clifd = Accept(lstfd,cliip,&cliport);
    if(clifd < 0)
    {
      continue;
    }
    printf("new connect: [%s:%d]\n",cliip,cliport);
    while(1)
    {
      char buf[1024] = {0};
      Recv(clifd,buf,1024);
      printf("client say:%s\n",buf);
      memset(buf,0x00,1024);
      scanf("%s",buf);
      Send(clifd,buf,strlen(buf));
    }
    Close(lstfd);
  }
  return 0;
}
