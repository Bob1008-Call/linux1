#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

//void *thread01(void *pt)
//{
//  for(int i = 0;i < 5;++i)
//  {
//    std::cout<< "thread01 is working" <<std::endl;
//    sleep(1);
//  }  
//}
//
//void *thread02(void *pt)
//{
//  for(int i = 0;i < 5;++i)
//  {
//    std::cout<< "thread02 is working" <<std::endl;
//    sleep(1);
//  }
//}
//
//int main()
//{
//  pthread_t t1;
//  void* ret;
//  pthread_create(&t1,NULL,thread01,NULL);
//  pthread_join(t1,&ret);
//  return 0;
//}
//
int num = 100;
void *thread01(void* pt)
{
  while(num > 0)
  {
    std::cout<<num<<std::endl;
    sleep(1);
    num--;
  }
}

void *thread02(void* pt)
{
  while(num > 0)
  {
    std::cout<<num<<std::endl;
    sleep(1);
    num--;
  }
}

int main()
{
  pthread_t t1,t2;
  void* ret1;
  void* ret2;
  pthread_create(&t1,NULL,thread01,NULL);
  pthread_create(&t2,NULL,thread02,NULL);
  pthread_join(t1,&ret1);
  pthread_join(t2,&ret2);
  return 0;
}
