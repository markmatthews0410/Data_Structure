#include<stdio.h>
#include<stdlib.h>

typedef int datatype;
typedef struct node{
	datatype data;
	struct node *next;
}linklist;

linklist *creat();
void print(linklist *);
void deletenode(linklist *,datatype,datatype);
void freelist(linklist *);

int main()
{
	linklist *head;
	int min,max;
	head = creat();
	printf("原链表为：\n");
	print(head);
	printf("\n");
	puts("***************请为min输入一个整数******************");
	scanf("%d",&min);
	puts("***************请为max输入一个整数******************");
	scanf("%d",&max);
	deletenode(head,min,max);
	printf("***********删除介于min和max之间的结点后的链表*********\n");
	print(head);
	return 0;
}

linklist *creat()
{
	linklist *head,*end;
	head = (linklist *)malloc(sizeof(linklist));
	if(head == NULL)
	{
		printf("内存分配失败\n");
		exit(1);
	}
	head->next = NULL;
	end = head;
	while (1)
	{
		linklist *node = (linklist *)malloc(sizeof(linklist));
		if(node == NULL)
		{
			printf("内存分配失败\n");
			exit(1);
		}
		scanf("%d",&node->data);
		char c = getchar();
		end->next = node;
		end = node;
		if(c == '\n')break;
	}
	end->next = NULL;
	return head;
}

void print(linklist *L)
{
	linklist *p;
	p = L->next;
	while(p)
	{
		printf("%d ",p->data);
		p = p->next;
	}
}

void deletenode(linklist *head,datatype min,datatype max)
{
	linklist *p,*q,*MIN,*MAX;
	p = head->next;
	q = head;
	while(p != NULL)
	{
		if(p->data > min)
		{
			MIN = q;
			break;
		}
		else if(p->data == min)
		{
			MIN = p;
			break;
		}
		else
		{
			p = p->next;
			q = q->next;
		}
	}
	if(p == NULL)
	{
		MIN = p;
		MAX = p;
		goto star;
	}
	while(p != NULL)
	{
		if(p->data >= max)
		{
			MAX = p;
			break;
		}
		else
		{
			p = p->next;
			q = q->next;
		}
	}
	if(p == NULL)
	{
		MAX = p;
	}
	MIN->next = MAX;
	star:;
}

void freelist(linklist *L)
{
	linklist *node = L;
    while (node) 
	{
        linklist *temp = node;
        node = node->next;
        free(temp);
    }
}
