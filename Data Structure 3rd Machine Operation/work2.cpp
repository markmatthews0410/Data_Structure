#include<stdio.h>
#include<stdlib.h>

#define maxsize 1024

typedef struct node
{
    int data;
    struct node *next;
}linklist;

linklist *create();
void listdelete(linklist *,linklist *,linklist *);
void print(linklist *);

int main()
{
    linklist *heada,*headb,*headc;
    heada = create();
    headb = create();
    headc = create();
    printf("*********************删除之前的3个表分别为:*********************\n");
    print(heada);
    print(headb);
    print(headc);
    listdelete(heada,headb,headc);
    printf("********************删除之后的LA表为:***********************\n");
    print(heada);
    return 0;
}

linklist *create()
{
    linklist *head = (linklist *)malloc(sizeof(linklist));
    if(head == NULL) exit(1);
    head->next = NULL;
    linklist *p = head;
    while(1)
    {
        linklist *node = (linklist *)malloc(sizeof(linklist));
        if(node == NULL) exit(1);
        scanf("%d",&node->data);
        node->next = NULL;
        if(node->data == -1)
        {
            free(node);
            break;
        }
        p->next = node;
        p = p->next;
    }
    return head;
}

void print(linklist *head)
{
    linklist *p = head->next;
    while (p != NULL)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

void listdelete(linklist *la,linklist *lb,linklist *lc)
{
    int same[maxsize];
    linklist *pa = la->next,*qa = la;
    linklist *pb,*pc;
    int flag1,flag2;
    while(pa != NULL)
    {
        flag1 = 0;
        flag2 = 0;
        pb = lb->next;
        pc = lc->next;
        while(pb != NULL)
        {
            if(pb->data == pa->data)
            {
                flag1 = 1;
                break;
            }
            pb = pb->next;
        }
        while(pc != NULL)
        {
            if(pc->data == pa->data)
            {
                flag2 = 1;
                break;
            }
            pc = pc->next;
        }
        if(flag1 == 1 && flag2 == 1)
        {
            linklist *temp = pa;
            pa = pa->next;
            qa->next = pa;
            free(temp);
        }
        else
        {
            pa = pa->next;
            qa = qa->next;
        }
    }
}