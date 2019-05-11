#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <fcntl.h>

void SetNoBlock(int fd)
{
  int fl = fcntl(fd,F_GETFL);
  if(fl < 0)
  {
    perror("fcntl");
    return;
  }
  fcntl(fd,F_SETFL,fl | O_NONBLOCK);
}

int main()
{
  SetNoBlock(0);
  char buf[1024];
  while(1)
  {
    ssize_t s = read(0,buf,sizeof(buf)-1);
    if(s > 0)
    {
      buf[s] = 0;
      std::cout<<buf<<std::endl;
    }
    else 
    {
      std::cout<<"default..."<<std::endl;
    }
    sleep(2);
  }
  return 0;
}
