#include<stdlib.h> 
#include<stdio.h>

typedef char datatype;

typedef struct node {
	datatype data;
	struct node *next;
}linklist;

linklist *create();
void print(linklist *);
void invert(linklist *);
void freelist(linklist *);

int main()
{
	linklist *head; 
    printf("***************�봴������*****************\n");
    head=create(); 
    printf("***************���ԭ����*****************\n");
	print(head);
	invert(head);
	printf("************������ú������**************\n");
	print(head); 
	return 0;
}

linklist *create()
{
	linklist *head,*end;
	head = (linklist *)malloc(sizeof(linklist));
	if(head == NULL)
	{
		printf("�ڴ����ʧ��\n");
		exit(1);
	}
	head->next = NULL;
	end = head;
	printf("������Ԫ��(��#��β)��\n");
	while(1)
	{
		linklist *node = (linklist *)malloc(sizeof(linklist));
		if(node == NULL)
		{
			printf("�ڴ����ʧ��\n");
			exit(1);
		}
		scanf(" %c",&node->data);
		if(node->data =='#')
		{
			free(node);
			break;
		}
		end->next = node;
		end = node;
	}
	end->next = NULL;
	return head;
}

void print(linklist *head)
{
	linklist *node = head->next;
	while(node != NULL)
	{
		printf("%c ",node->data);
		node = node->next;
	}
	printf("\n");
}

void invert(linklist *head)//�û��� 
{
	linklist *p,*q,*r;
	p = head->next;
	q = p->next;
	p->next = NULL;
	while(q)
	{
		r = q->next;
		q->next = p;
		p = q;
		q = r;
	}
	head->next = p;
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
