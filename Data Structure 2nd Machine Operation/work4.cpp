#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxsize 256

typedef struct 
{
    char ch[maxsize];
    int len;
}seqstring;

seqstring *makestr();
int index(seqstring *,seqstring *);

int main()
{
    seqstring *t,*p;
    int tag;
    printf("********请输入目标串：");
    t = makestr();
    printf("********请输入模式串：");
    p = makestr();
    tag = index(t,p);
    if(tag != 0)
    {
        printf("返回第一次匹配成功的位置（首字母所在下标）：%d",tag);
    }
    return 0;
}

seqstring *makestr()
{
    seqstring *str;
    str = (seqstring *)malloc(sizeof(seqstring));
    scanf("%s",str->ch);
    str->len = strlen(str->ch);
    return str;
}

int index(seqstring *t,seqstring *p)
{
    int i = 1,j = 1,n = 0;
    while(i <= t->len && j <= p->len)
    {
        if(t->ch[i-1] == p->ch[j-1])
        {
            i++;
            j++;
        }
        else
        {
            i = i-j+2;
            j = 1;
        }
        n++;
    }
    if(j > p->len) 
    {
        printf("匹配成功！比较次数为:%d\n",n);
        return (i-p->len);
    }
    else
    {
        printf("匹配失败！比较次数为:%d",n);
        return 0;
    }
}