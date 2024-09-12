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
void print(seqstring *);
int symmetry(seqstring *);

int main()
{
    seqstring *str;
    printf("请初始化字符串:");
    str = makestr();
    if (symmetry(str)) printf("判定结果：该字符串\"%s\"是回文", str->ch); 
    else printf("判定结果：该字符串\"%s\"不是回文", str->ch); 
    return 0;
}

seqstring *makestr()
{
    seqstring *str = (seqstring *)malloc(sizeof(seqstring));
    scanf("%s",str->ch);
    str->len = strlen(str->ch);
    return str;
}

void print(seqstring *str)
{
    printf("%s\n",str->ch);
}

int symmetry(seqstring *str)
{
    int left,right;
    left = 0;
    right = str->len-1;
    while(left < right)
    {
        if(str->ch[left] != str->ch[right])
        {
            return 0;
        }
        left++;
        right--;
    }
    return 1;
}