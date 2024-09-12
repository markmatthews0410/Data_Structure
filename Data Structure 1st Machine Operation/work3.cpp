#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct node{
    datatype data;
    struct node *next;
}linklist;

linklist *create();
void print(linklist *);
linklist *mergelist(linklist *, linklist *);
void freelist(linklist *);

int main(void){
    linklist *La, *Lb, *Lc;
    printf("****************�봴������ La******************\n");
    La = create();
    printf("****************�봴������ Lb******************\n");
    Lb = create();
    printf("***************�����ʾ���� La*****************\n");
    print(La);
    printf("***************�����ʾ���� Lb*****************\n");
    print(Lb);
    Lc = mergelist(La, Lb);
    printf("*****�����ʾLa���Lb��鲢�ݼ�������� Lc*****\n");
    print(Lc);
    freelist(La);
    freelist(Lb);
    freelist(Lc);
    return 0;
}//����ʱ�临�Ӷ�Ϊ O(n)

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
}//��������A��B��ʱ�临�Ӷ�Ϊ O(n)

void print(linklist *L)
{
	linklist *p;
	p = L->next;
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

linklist *mergelist(linklist *La, linklist *Lb)
{
	linklist *head = (linklist *)malloc(sizeof(linklist));
	if(head == NULL)
	{
		printf("�ڴ����ʧ��\n");
		exit(1);
	}
	head->next = NULL;
	linklist *p,*q,*temp;
	p = La->next;
	q = Lb->next;
	while(p && q)
	{
		if(p->data < q->data)
		{
			temp = p->next;
			p->next = head->next;
			head->next = p;
			p = temp;
		}
		else
		{
			temp = q->next;
			q->next = head->next;
			head->next = q;
			q = temp;
		}
	}
	while(p)
	{
		temp = p->next;
		p->next = head->next;
		head->next = p;
		p = temp;
	}
	while(q)
	{
		temp = q->next;
		q->next = head->next;
		head->next = q;
		q = temp;
	}
	return head;
}//�ϲ�����A��B��ʱ�临�Ӷ�Ϊ O(n)
