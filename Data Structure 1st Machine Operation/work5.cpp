#include<stdlib.h> 
#include<stdio.h> 

typedef struct node {
	int coef; 
	int exp; 
	struct node *next;
}linklist;

linklist *create(); 
void print(linklist *); 
void SumofPoly(linklist *,linklist *);
void freelist(linklist *);

int main() 
{
	linklist *A,*B; 
	printf("**************请输入原多项式A链表为*****************\n"); 
	A = create(); 
	printf("**************请输入原多项式B链表为*****************\n"); 
	B = create(); 
	printf("**************显示原多项式A链表为*****************\n"); 
	print(A); 
	printf("**************显示原多项式B链表为*****************\n"); 
	print(B); 
	SumofPoly(A, B);//调用多项式求和的函数 
	printf("**************显示求和运算之后的多项式A链表为*****************\n"); 
	print(A); 
	printf("**************显示求和运算之后的多项式B链表为*****************\n"); 
	print(B);
	freelist(A);
	freelist(B); 
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
    printf("请输入系数和指数，以0 0结束：\n");
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

void SumofPoly(linklist *A,linklist *B)
{
	linklist *pa,*qa,*pb,*qb;
	pa = A->next;
	qa = A;
	pb = B->next;
	qb = B;
	while(pa && pb)
	{
		if(pa->exp < pb->exp)
		{
			qa = pa;
			pa = pa->next;
		}
		else if(pa->exp > pb->exp)
		{
			linklist *temp = pb->next;
			pb->next = pa;
			qa->next = pb;
			qb->next = temp;
			qa = pb;
			pb = temp;
		}
		else if(pa->exp == pb->exp)
		{
			pa->coef = pa->coef+pb->coef;
			if(pa->coef == 0)
			{
				linklist *temp = pa;
				pa = pa->next;
				qa->next = pa;
				free(temp);
			}
			else
			{
				qa = pa;
			    pa = pa->next;
			}
			linklist *temp = pb;
			pb = pb->next;
			qb->next = pb;
			free(temp);
		}
	}
	while(pb)
	{
		qa->next = pb;
		qa = pb;
		pb = pb->next;
	}
	qb->next = NULL;
}
