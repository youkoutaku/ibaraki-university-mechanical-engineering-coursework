#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *pt;
} NODE;

void InputData(int);
void DisplayList(void);
NODE *talloc(void);


NODE *head = NULL;

int main(void)
{
  char command[256];
  int  n;
  
  while(1) {
    printf("Input command: ");
    scanf("%s", command);

    if (command[0]=='i') {
      printf("\nInput data: ");
      scanf("%d", &n);
      InputData(n);
    }
    else if (command[0]=='d')
      DisplayList();
    else if (command[0]=='q')
      break;
  }
  return 0;
}

void InputData(int n)
{
    NODE *N, *p;
    
    N=talloc();
    N->data=n;

    if(head == NULL || head->data > n){
            N->pt = head; 
            head = N;
            return;
    }

    p=head;
    while(p!=NULL){
        if(p->pt == NULL || p->pt->data > n){
            break;
        }
        p = p->pt;    
    }

    N->pt = p->pt;
    p->pt = N;
}

void DisplayList(void)
{
  NODE *p=head;

  printf("List: ");
  
  while(p!=NULL) {
    printf("%d", p->data);
    if(p->pt!=NULL)
      printf("->");
    p=p->pt;
  }
  printf("\n");
}

NODE *talloc(void)
{
  NODE *p;
  
  p=(NODE *)malloc(sizeof(NODE));
  if (p==NULL) {
    fprintf(stderr,"Cannot allocate memory.\n");
    exit(1);
  }
  return(p);
}  