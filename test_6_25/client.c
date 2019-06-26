#include "tcpsocket.h"
#define CHECK_RET(q) if((q) < 0){return -1;}

int main()
{
  int lstfd = Socket();
  CHECK_RET(lstfd);
  CHECK_RET(Connect(lstfd,"192.168.9.166",9000));
  while(1)
  {
    char buf[1024] = {0};
    scanf("%s",buf);
    Send(lstfd,buf,strlen(buf));
    Recv(lstfd,buf,1024);
    printf("server say:%s\n",buf);
    memset(buf,0x00,strlen(buf));
  }
  Close(lstfd);
  return 0;
}
