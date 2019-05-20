#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
using namespace std;

void* thread_function(void* arg);

char message[] = "hello world";
int main()
{
  pthread_t t;
  int i = 0;
  int res;

  while(1)
  {
    res = pthread_create(&t,NULL,thread_function,(void*)message);
    i++;
    if(res != 0)
    {
      cout<<"线程个数："<<i<<endl;
      perror("Thread create:errno:");
      return 0;
    }
  }
  return 0;
}

void* thread_function(void* arg)
{
  printf("thread_function is runing.Argument is %s\n",(char*)arg);
}
