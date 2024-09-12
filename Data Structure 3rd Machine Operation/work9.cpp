#include<stdio.h>
#include<stdlib.h>

#define maxsize 100

typedef struct 
{
    int num[maxsize][maxsize];
}seqstring;

seqstring *init()
{
    seqstring *str = (seqstring *)malloc(sizeof(seqstring));
    for(int i = 0;i < maxsize;i++)
    {
        for(int j = 0;j < maxsize;j++)
        {
            str->num[i][j] = 0;
        }
    }
    return str;
}

void magic_matrix(seqstring *str, int n) {
    int i, j, k;
    j = 0;
    k = n/2;
    for(i = 1;i <= n * n;i++) 
    {
        str->num[j][k] = i;
        int new_j = (j-1+n)%n;
        int new_k = (k-1+n)%n;
        if(str->num[new_j][new_k] != 0)
        {
            j = (j+1)%n;
        }
        else
        {
            j = new_j;
            k = new_k;
        }
    }
}


int main()
{
    while(1)
    {
        int n;
        seqstring *str = init();
        printf("********请输入矩阵规模参数n,输入-1结束********\n");
        scanf("%d",&n);
        if(n == -1) break;
        magic_matrix(str,n);
        printf("********输出%d阶魔方阵如下********\n",n);
        for(int i = 0;i < n;i++)
        {
            for(int j = 0;j < n;j++)
            {
                printf("%d\t",str->num[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}