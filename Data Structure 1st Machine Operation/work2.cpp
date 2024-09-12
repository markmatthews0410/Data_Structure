#include<stdio.h>
#include<stdlib.h>

#define maxsize 1024

typedef char datatype;

typedef struct{
	datatype data[maxsize];
	int last;//last��ʾ��Ч���� 
}sequenlist;

sequenlist *creat();
void print(sequenlist *);
void invert(sequenlist *);

int main(void)
{
	sequenlist *L;
	printf("***************�봴��˳���*****************\n");
	L = creat();
	printf("****************���˳���******************\n");
	print(L);
	invert(L);
	printf("************������ú��˳���**************\n");
	print(L); 
	free(L);
	return 0;
}

sequenlist *creat()
{
	int i = 0;
	sequenlist *L = (sequenlist *)malloc(sizeof(sequenlist));
	if(L == NULL)
	{
		printf("�ڴ����ʧ��\n");
		exit(1);
	}
    L->last = -1;
    printf("������Ԫ��(��#��β)��\n");
    while(1)
    {
    	if(i >= maxsize)
    	{
    		printf("˳������������ܼ������Ԫ��\n");
    		break;
		}
    	scanf(" %c",&L->data[i]);
    	if(L->data[i] == '#')
    	{
    		L->data[i] = '\0';
    		break;
		}
    	L->last++;
    	i++;
	}
    return L;
}

void print(sequenlist *L)
{
	if(L->last == -1)
	{
		printf("˳���Ϊ��\n");
		return;
	}
	for(int i = 0;i <= L->last;i++)
	{
		printf("%c ",L->data[i]);
	}
	printf("\n"); 
}

void invert(sequenlist *L)
{
	int left = 0,right = L->last;
	while(left < right)
	{
		datatype temp = L->data[left];
		L->data[left] = L->data[right];
		L->data[right] = temp;
		left++;
	    right--;
	}
}

