#include<stdio.h> 
#include<stdlib.h>

typedef int datatype; 

typedef struct node{
	datatype data;
	struct node *next; 
}linklist;

linklist *create(); 
void print(linklist *);
void DelRedundant(linklist *); 
void freelist(linklist *); 

int main()
{
	linklist *head;
	head = create(); 
	printf("****************ԭ������������****************\n"); 
	print(head); 
	DelRedundant(head);
	printf("****************ȥ�غ����������****************\n"); 
	print(head);
	freelist(head);
	return 0;
}

linklist *create()
{
	linklist *head,*rear;
	head = (linklist *)malloc(sizeof(linklist));
	if(head == NULL)
	{
		printf("�ڴ����ʧ��\n");
		exit(1);
	}
	head->next = NULL;
	rear = head;
	int n;
	printf("�����������ȣ�");
	scanf("%d",&n); 
	printf("���������������������ݣ�\n");
	for(int i = 0;i < n;i++)
	{
		linklist *node = (linklist *)malloc(sizeof(linklist));
		scanf("%d",&node->data);
		node->next = NULL;
		rear->next = node;
		rear = node;
	}
	return head;
}

void print(linklist *head)
{
	linklist *p;
	p = head->next;
	while(p)
	{
		printf("%d ",p->data);
		p = p->next;
	}
	printf("\n");
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

void  DelRedundant(linklist *head) 
{
	linklist *p,*q;
	q = head->next;
	p = q->next;
	while(p)
	{
		if(p->data == q->data)
		{
			q->next = p->next;
			linklist *temp = p;
			p = q->next;
			free(temp);
		}
		else
		{
			q = q->next;
			p = p->next;
		}
	}
}//ʱ�临�Ӷ�Ϊ O(n)
