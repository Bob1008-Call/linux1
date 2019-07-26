#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
void* pthread_run1(void* arg)
{
  (void)arg;
  
  while(1)
  {
    cout << "I am thread1,ID" << pthread_self() << endl;
    sleep(1);
  }
}

void* pthread_run2(void* arg)
{
  (void)arg;
  while(1)
  {
    cout << "I am thread2 ID:" << pthread_self() << endl;
    sleep(1);
  }
}

int main()
{
  pthread_t tid1;

  pthread_create(&tid1,NULL,pthread_run1,NULL);

  cout << "I am main thread" << endl;

  pthread_join(tid1,NULL);
  return 0;
}
