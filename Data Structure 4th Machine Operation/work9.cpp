#include<stdio.h>
#include<stdlib.h>

const int n = 5;
const int e = 5;

typedef struct node
{
    int adjvex;
    struct node *next;
}edgenode;

typedef struct 
{
    char vertex;
    edgenode *link;
    edgenode *rear;
}vexnode;

void create();
int dfs_cycle(vexnode *,int);
void dfs_print(vexnode *,int);

vexnode ga[n];
int visited[n];
int dfs_path[n];

int main()
{
    create();
    int start,flag = 0;
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    printf("请输入出发点序号：");
    scanf("%d",&start);
    printf("从%d出发的遍历序列为：",start);
    dfs_print(ga,start);
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            dfs_print(ga,i);
        }
    }
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        dfs_path[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        if (dfs_cycle(ga,i))
        {
            flag = 1;
        }
    }
    if (flag == 1)
    {
        printf("该有向图存在回路！");
    }
    else
    {
        printf("该有向图不存在回路！");
    }
    return 0;
}

void create()
{
    int i,j;
    printf("请输入5个顶点的字符数据信息：");
    for (int k = 0; k < n; k++)
    {
        ga[k].vertex = getchar();
        ga[k].link = NULL;
        ga[k].rear = NULL;
    }
    printf("请输入5条边的起、终点i,j：\n");
    for (int k = 0; k < e; k++)
    {
        scanf("%d,%d",&i,&j);
        edgenode *s = (edgenode *)malloc(sizeof(edgenode));
        s->adjvex = j;
        s->next = NULL;
        if (ga[i].rear == NULL)
        {
            ga[i].link = s;
            ga[i].rear = s;
        }
        else
        {
            ga[i].rear->next = s;
            ga[i].rear = s;
        }
    }
}

int dfs_cycle(vexnode *ga,int i)
{
    edgenode *p;
    visited[i] = 1;
    dfs_path[i] = 1;
    p = ga[i].link;
    while (p != NULL)
    {
        if (visited[p->adjvex] == 0)
        {
            if(dfs_cycle(ga,p->adjvex))
            {
                return 1;
            }
        }
        else if (dfs_path[p->adjvex] == 1)
        {
            return 1;
        }
        p = p->next;
    }
    dfs_path[i] = 0;
    return 0;
}

void dfs_print(vexnode *ga,int i)
{
    edgenode *p;
    printf("%c ",ga[i].vertex);
    visited[i] = 1;
    p = ga[i].link;
    while (p != NULL)
    {
        if (visited[p->adjvex] == 0)
        {
            dfs_print(ga,p->adjvex);
        }
        p = p->next;
    }
}