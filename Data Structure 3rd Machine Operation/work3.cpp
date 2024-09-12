#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxsize 1024

typedef char datatype;
typedef struct stack
{
    datatype data[maxsize];
    int top;
}seqstack;

seqstack *initstack();
void deletedata(seqstack *,datatype);
void push(seqstack *,datatype);
datatype pop(seqstack *);
void print(seqstack *);
int emptys(seqstack *);

int main()
{
    seqstack *s;
    datatype m;
    printf("***********************请输入m:***********************\n");
    scanf("%c",&m);
    printf("***********************请初始化栈s:***********************\n");
    s = initstack();
    scanf("%s",&s->data);
    s->top = strlen(s->data)-1;
    printf("***********************输出栈s:***********************\n");
    print(s);
    deletedata(s,m);
    printf("********************输出删除m之后的栈s:***********************\n");
    print(s);
    return 0;
}

seqstack *initstack()
{
    seqstack *s = (seqstack *)malloc(sizeof(seqstack));
    s->top = -1;
    return s; 
}

void push(seqstack *s,datatype m)
{
    if (s->top == maxsize-1)
    {
        printf("栈满\n");
        return;
    }
    s->data[++s->top] = m;
}

datatype pop(seqstack *s)
{
    if (s->top == -1)
    {
        printf("栈空\n");
        return -1;
    }
    return s->data[s->top--];
}

int emptys(seqstack *s)
{
    return s->top == -1;
}

void print(seqstack *s)
{
    if (emptys(s))
    {
        printf("栈空\n");
        return;
    }
    for (int i = 0; i <= s->top; i++)
    {
        printf("%c ",s->data[i]);
    }
    printf("\n");
}

void deletedata(seqstack *s,datatype m)
{
    seqstack *temp = initstack();
    while(!emptys(s))
    {
        datatype current = pop(s);
        if(current != m)
        {
            push(temp,current);
        }
    }
    while(!emptys(temp))
    {
        push(s,pop(temp));
    }
    free(temp);
}