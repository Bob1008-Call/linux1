#include <iostream>

using namespace std;

//int main()
//{
//  cout<<"hello world";
//  return 0;
//}
//
//#include <sys/types.h>
//#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>
//int main()
//{
//    pid_t id = fork();
//    if (id > 0)
//    {
//        // 父进程
//        printf("%d\n", getpid());
//        sleep(5);
//    }
//    else if (id == 0)
//    {
//        // 子进程
//        printf("%d\n", getpid());
//        sleep(10);
//    }
//    else
//    {
//        perror("fork");
//    }
//    return 0;
//}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <linux/wait.h>
int main(int argc,char **argv)
{
    int i=0;
    pid_t pid=fork();
    if(pid==-1) return 0;
    else if(pid==0)
    {
            printf("son pid is %d\n",getpid());
            while(1)
            {
                    printf("son---i=%d\n",i);
                    i++;
                    sleep(1);
                    if(i==5)
                    break;
            }
            printf("son is over!\n");
    }else if(pid>0)
    {
            printf("parent pid is %d\n",getpid());
            while(1) sleep(100);
    }
    return 0;
}

