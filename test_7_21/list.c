#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct student
{
  int num;
  struct student* next;
}Lstudent,*LPstudent;

void InitLink(LPstudent* head)
{
  Lstudent *ptr,*r;
  *head = NULL;
  int n;
  int number; 
  printf("please input number of student: \n");
  scanf("%d",&n);
  while(n--)
  {
    printf("please input curent number of student:\n");
    scanf("%d",&number);
    ptr = (LPstudent)malloc(sizeof(Lstudent));
    ptr->num = number;
    ptr->next = NULL;
    if(*head == NULL)
      *head = ptr;
    else 
      r->next = ptr;

    r = ptr;
  }
  ptr->next = *head;
}

void Print_Link(Lstudent* ptr)
{
  while(ptr != NULL)
  {
    printf("%d\n",ptr->num);
    ptr = ptr->next;
    sleep(1);
  }
}

int main()
{
  LPstudent head;
  InitLink(&head);
  Print_Link(head);
  return 0;
}
