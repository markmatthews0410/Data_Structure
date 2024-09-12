#include<stdio.h>
#include<stdlib.h>

#define maxsize 1024

typedef char datatype;

typedef struct{
	datatype data[maxsize];
	int last;//last表示有效数据 
}sequenlist;

sequenlist *creat();
void print(sequenlist *);
void invert(sequenlist *);

int main(void)
{
	sequenlist *L;
	printf("***************请创建顺序表*****************\n");
	L = creat();
	printf("****************输出顺序表******************\n");
	print(L);
	invert(L);
	printf("************输出逆置后的顺序表**************\n");
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
		printf("内存分配失败\n");
		exit(1);
	}
    L->last = -1;
    printf("请输入元素(以#结尾)：\n");
    while(1)
    {
    	if(i >= maxsize)
    	{
    		printf("顺序表已满，不能继续添加元素\n");
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
		printf("顺序表为空\n");
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

