#include<stdio.h>
#include<malloc.h>

#define maxsize 1024

typedef int datatype;
typedef struct 
{
    datatype data[maxsize];
    int last;
}sequenlist;

sequenlist *create();
void print(sequenlist *);
void Delete(sequenlist *, sequenlist *, sequenlist *);
void ListDelete(sequenlist *L, int i);

int main()
{
    sequenlist *LA,*LB,*LC;
    printf("*************please input LA numbers:***********************\n"); 
    LA = create();
    printf("*************please input LB numbers:***********************\n"); 
    LB = create();
    printf("*************please input LC numbers:***********************\n");
    LC = create();
    printf("*************删除之前的LA表为:***********************\n");
    print(LA);
    Delete(LA,LB,LC);
    printf("*************删除之后的LA表为:***********************\n");
    print(LA);
    return 0;
}

sequenlist *create()
{
    sequenlist *L = (sequenlist *)malloc(sizeof(sequenlist));
    L->last = 0;
    int ch;
    scanf("%d",&ch);
    while(ch != -1)
    {
        L->last++;
        L->data[L->last] = ch;
        scanf("%d",&ch);
    }
    return L;
}

void print(sequenlist *L)
{
    for(int i = 1;i <= L->last;i++) 
    {
        printf("%d ",L->data[i]);
    }
    printf("\n");
}

void Delete(sequenlist *LA, sequenlist *LB, sequenlist *LC)
{
    datatype str[maxsize];
    int p = 0,flag = 1;
    for(int i = 1;i <= LB->last;i++)
    {
        for(int j = 1;j <= LC->last;j++)
        {
            if(LB->data[i] == LC->data[j])
            {
                flag = 1;
                for(int q = 0;q < p;q++)
                {
                    if(str[q] == LB->data[i])
                    {
                        flag = 0;
                    }
                }
                if(flag == 1)
                {
                    str[p++] = LB->data[i];
                    i++;
                }
            }
        }
    }
    for(int i = 0;i <= LA->last;i++)
    {
        for(int j = 0;j < p;j++)
        {
            if(LA->data[i] == str[j])
            {
                ListDelete(LA,i);
            }
        }
    }
}

void ListDelete(sequenlist *L, int i)
{
    for(int j = i;j < L->last;j++) 
    {
        L->data[j] = L->data[j+1];
    }
    L->last--;
}