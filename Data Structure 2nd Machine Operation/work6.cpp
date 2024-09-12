#include<stdlib.h> 
#include<stdio.h> 

typedef struct node {
	int coef; 
	int exp; 
	struct node *next;
}linklist;

linklist *create(); 
void print(linklist *); 
linklist *SumofPoly(linklist *,linklist *);
void freelist(linklist *);

int main() 
{
	linklist *A,*B,*C; 
	printf("**************请输入原多项式A链表为*****************\n"); 
	A = create(); 
	printf("**************请输入原多项式B链表为*****************\n"); 
	B = create(); 
	printf("**************显示原多项式A链表为*****************\n"); 
	print(A); 
	printf("**************显示原多项式B链表为*****************\n"); 
	print(B); 
	C = SumofPoly(A, B);
	printf("**************显示求和运算之后的多项式A链表为*****************\n"); 
	print(A); 
	printf("**************显示求和运算之后的多项式B链表为*****************\n"); 
	print(B);
    printf("**************显示求和运算之后的多项式C链表为*****************\n");
    print(C);
	freelist(A);
	freelist(B);
    freelist(C);
	return 0;
}

linklist *create()
{
	linklist *head,*rear;
	head = (linklist *)malloc(sizeof(linklist));
	if(head == NULL)
	{
		printf("内存分配失败\n");
		exit(1);
	}
	head->next = NULL;
	rear = head;
	int coef,exp;
    printf("请输入系数和指数,以0 0结束:\n");
    while (1){
        linklist *node = (linklist *)malloc(sizeof(linklist));
        if(node ==NULL)
        {
        	printf("内存分配失败\n");
		    exit(1);
		}
		scanf("%d %d",&coef,&exp);
		if(coef == 0 && exp == 0)
		{
			free(node);
			break;
		}
		node->coef = coef;
		node->exp = exp;
		rear->next = node;
		rear = node;
    }
    rear->next = NULL;
    return head;
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

void print(linklist *head)
{ 
	linklist *node = head->next;
	if(node == NULL)
	{
		printf("该表空");
	}
	while(node != NULL)
	{
		if(node->exp == 0)
		{
			printf("%d",node->coef);
		}
		else if(node->exp == 1 && node->coef == 1)
		{
			printf("x");
		}
		else if(node->coef == -1 && node->coef == 1)
		{
			printf("-x");
		}
		else if(node->coef == -1)
		{
			printf("-x^%d",node->exp);
		}
		else if(node->exp == 1)
		{
			printf("%dx",node->coef);
		}
		else if(node->coef == 1)
		{
			printf("x^%d",node->exp);
		}
		else
		{
			printf("%dx^%d",node->coef,node->exp);
		}
		node = node->next;
		if(node != NULL && node->coef > 0)
		{
			printf("+");
		}
	}
	printf("\n");
}

linklist *SumofPoly(linklist *A,linklist *B)
{
	linklist *pa,*pb,*pc;
    linklist *C = (linklist *)malloc(sizeof(linklist));
    if(C == NULL)
	{
		printf("内存分配失败\n");
		exit(1);
	}
    C->next = NULL;
	pa = A->next;
	pb = B->next;
    pc = C;
	while(pa && pb)
	{
		if(pa->exp < pb->exp)
		{
            linklist *node = (linklist *)malloc(sizeof(linklist));
            node->next = NULL;
            node->coef = pa->coef;
            node->exp = pa->exp;
            pc->next = node;
            pc = pc->next;
			pa = pa->next;
		}
		else if(pa->exp > pb->exp)
		{
			linklist *node = (linklist *)malloc(sizeof(linklist));
            node->next = NULL;
            node->coef = pb->coef;
            node->exp = pb->exp;
            pc->next = node;
            pc = pc->next;
            pb = pb->next;
		}
		else if(pa->exp == pb->exp)
		{
            linklist *node = (linklist *)malloc(sizeof(linklist));
            node->next = NULL;
			node->coef = pa->coef+pb->coef;
            node->exp = pa->exp;
			if(node->coef == 0) free(node);
			else
			{
				pc->next = node;
                pc = pc->next;
			}
			pa = pa->next;
			pb = pb->next;
		}
	}
    while(pa)
    {
        linklist *node = (linklist *)malloc(sizeof(linklist));
        node->next = NULL;
        node->coef = pa->coef;
        node->exp = pa->exp;
        pc->next = node;
        pc = pc->next;
        pa = pa->next;
    }
	while(pb)
	{
		linklist *node = (linklist *)malloc(sizeof(linklist));
		node->next = NULL;
		node->coef = pb->coef;
		node->exp = pb->exp;
		pc->next = node;
		pc = pc->next;
		pb = pb->next;
	}
    return C;
}