#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
  int fd;
  int ret;
  ret = mkfifo("myfifo2",0666);
  if(ret == -1)
  {
    perror("mkfifo error");
  }

  printf("before open\n");
  fd = open("myfifo1",O_RDWR);
  if(fd<0)
  {
    perror("open error");
  }
  printf("after open\n");
  char buf[1024];
  printf("before read\n");
  read(fd,buf,sizeof(buf));
  printf("after read\n");
  return 0;
}
