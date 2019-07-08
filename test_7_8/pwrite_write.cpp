#include <unistd.h>
#include <iostream>
#include <memory.h>
#include <stdlib.h>
#include <fcntl.h>
using namespace std;

#define BUFFSIZE 20
char name[] = "HELLO WORLD";

void pwriteTest(int fd)
{
  char buf[BUFFSIZE];
  pwrite(fd,name,5,0);

  read(fd,buf,5);
  cout << buf << endl;
}

void writeTest(int fd)
{
  char buf[BUFFSIZE];
  write(fd,name,5);

  read(fd,buf,5);
  cout << buf << endl;
}

int main()
{
  int fd;
  fd = open("./write.txt",O_RDWR);
  //pwriteTest(fd);
  writeTest(fd);
  return 0;
}
