#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define maxsize 1024

typedef struct 
{
    char ch[maxsize];
    int len;
}seqstring;

seqstring *create();
void print(seqstring *);
int index_kmp(seqstring *,seqstring *,int *);
void get_next(seqstring *,int *);

int main()
{
    printf("请输入目标串:");
    seqstring *t = create();
    printf("请输入模式串:");
    seqstring *p = create();
    int next[maxsize];
    get_next(p,next);
    int flag = index_kmp(t,p,next);
    if(flag != -1) printf("返回第一次匹配成功的位置(首字母位序):%d\n",flag);
    printf("next数组内容:");
    for(int i = 0;i < p->len;i++)
    {
        printf("%d",next[i]);
        if (i < p->len-1) printf(",");
    }
    return 0;
}

seqstring *create()
{
    seqstring *str = (seqstring *)malloc(sizeof(seqstring));
    scanf("%s",&str->ch);
    str->len = strlen(str->ch);
    return str;
}

void print(seqstring *str)
{
    printf("%s\n",str->ch);
}

int index_kmp(seqstring *t,seqstring *p,int *next)
{
    int i = 0,j = 0,n = 0;
    while (i < t->len && j < p->len)
    {
        if(j == -1 || t->ch[i] == p->ch[j])
        {
            i++;
            j++;
        }
        else j = next[j];
        n++;
    }
    if (j >= p->len) 
    {
        printf("匹配成功！比较次数为:%d\n",n);
        return i-p->len;
    }
    else
    {
        printf("匹配失败！比较次数为:%d\n",n);
        return -1;
    }
}

void get_next(seqstring *p,int *next)
{
    int i = 0,j = -1;
    next[0] = -1;
    while (i < p->len-1)
    {
        if (j == -1 || p->ch[i] == p->ch[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else j = next[j];
    }
}