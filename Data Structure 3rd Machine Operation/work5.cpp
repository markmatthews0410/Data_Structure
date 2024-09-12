#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxsize 100

typedef struct 
{
    char str[maxsize];
    int len;
}seqsrtring;

void strput(seqsrtring *);
void strdelete(seqsrtring *,int,int);

int main()
{
    seqsrtring *s;
    int i, m;
    s = (seqsrtring *)malloc(sizeof(seqsrtring));
    printf("*********************请输入字符串*********************\n");
    gets(s->str);
    s->len = strlen(s->str);
    printf("*********************输入的字符串显示如下*********************\n");
    strput(s);
    printf("****************输入字符串的长度为:%d\n",s->len);
    printf("*********************请输入删除字符的开始位置********************\n");
    scanf("%d",&i);
    printf("*********************请输入要删除的字符个数*********************\n");
    scanf("%d",&m);
    strdelete(s,i,m);
    printf("*****************删除子串后的字符串为*****************\n");
    strput(s);
    return 0;
}

void strput(seqsrtring *s)
{
    puts(s->str);
}

void strdelete(seqsrtring *s, int i, int m)//首字符从1开始
{
    int n = i-1;
    if(i-1+m >= s->len)
    {
        for(int j = i-1;j < s->len;j++)
        {
            s->str[j] = '\0';
        }
    }
    else
    {
        for(int j = i-1;j < s->len;j++)
        {
            s->str[j] = s->str[j+m];
        }
    }
    s->len = strlen(s->str);
}