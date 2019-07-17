#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
  fd = open("myfifo1",O_WRONLY);
  if(fd<0)
  {
    perror("open error");
  }
  printf("after open\n");

  char buf[1024] = "hello world";
  printf("before write\n");
  write(fd,buf,strlen(buf));
  printf("after write\n");
  return 0;
}
