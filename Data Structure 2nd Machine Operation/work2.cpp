#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef char datatype;
typedef struct node
{
    datatype data;
    struct node *next;
}linklist;

linklist *create();
void resolve(linklist *,linklist *,linklist *,linklist *);
void print1(linklist *);
void print2(linklist *);

int main()
{
    linklist *head,*letter,*digit,*other;
    head = create();
    printf("***************原链表为***************\n");
    print1(head);
    letter = (linklist *)malloc(sizeof(linklist));//建立3个空循环链表
    letter->next = letter;
    digit = (linklist *)malloc(sizeof(linklist));
    digit->next = digit;
    other = (linklist *)malloc(sizeof(linklist));
    other->next = other; 
    resolve(head,letter,digit,other);
    printf("***************分解后的字母链表为***************\n");
    print2(letter);
    printf("***************分解后的数字链表为***************\n");
    print2(digit);
    printf("***************分解后的其他字符链表为***************\n");
    print2(other);
    return 0;
}

linklist *create()
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
		char c;
		scanf("%c",&c);
		if(c == '\n')
		{
			free(node);
			break;
		}
		node->data = c;
		end->next = node;
		end = node;
	}
	end->next = NULL;
	return head;
}

void resolve(linklist *head,linklist *letter,linklist *digit,linklist *other)
{
	linklist *p = head->next,*end1 = letter,*end2 = digit,*end3 = other;
	while(p != NULL)
	{
		if(isalpha(p->data))
		{
			end1->next = p;
			end1 = end1->next;
		}
		else if(isdigit(p->data))
		{
			end2->next = p;
			end2 = end2->next;
		}
		else
		{
			end3->next = p;
			end3 = end3->next;
		}
		p = p->next;
	}
	head->next = NULL;
	end1->next = letter;
	end2->next = digit;
	end3->next = other;
}

void print1(linklist *head)
{
	linklist *p = head->next;
	while(p != NULL)
	{
		printf("%c",p->data);
		p = p->next;
	}
	printf("\n");
}

void print2(linklist *head)
{
	linklist *p = head->next;
	while(p != head)
	{
		printf("%c",p->data);
		p = p->next;
	}
	printf("\n");
}