#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
  int num;
  struct student* next;
  struct student* pre;
}LDstudent,*LDPstudent;

void InitLink(LDPstudent* head)
{
  *head = NULL;
  LDPstudent ptr = NULL;
  LDPstudent r = ptr;
  int n;
  int number;
  printf("please input num of student:\n");
  scanf("%d",&n);
  while(n--)
  {
    printf("please input curent number of student:\n");
    scanf("%d",&number);
    ptr = (LDPstudent)malloc(sizeof(LDstudent));
    ptr->num = number;

    ptr->next = NULL;
    if(*head == NULL)
    {
      ptr->pre = NULL;
      *head = ptr;
    }
    else 
    {
      ptr->pre = r;
      r->next = ptr;
    }
    r = ptr;
  }
}

void Print(LDstudent* ptr)
{
  LDPstudent p1 = ptr;
  printf("正序打印:");
  while(p1 != NULL)
  {
    printf("%d\t",p1->num);
    p1 = p1->next;
  }

  printf("\n");
  printf("逆序打印:");
  p1 = ptr;
  while(p1->next != NULL)
  {
    p1 = p1->next;
  }
  while(p1 != NULL)
  {
    printf("%d\t",p1->num);
    p1 = p1->pre;
  }
}

int main()
{
  LDPstudent head;
  InitLink(&head);
  Print(head);
}
