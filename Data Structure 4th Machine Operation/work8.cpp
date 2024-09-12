#include<stdio.h>
#include<stdlib.h>

#define n 5
#define e 4

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

void create_graph_list(vexnode []);
void dfs_print(vexnode [],int);
int count_connected_components(vexnode []);
void dfs(vexnode[],int);

vexnode ga[n];
int visited[n];

int main()
{
    int start;
    create_graph_list(ga);
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
    int num = count_connected_components(ga);
    printf("该图包含的连通分量的个数为：%d\n",num);
    if (num+e > n)
    {
        printf("该图存在回路！");
    }
    else
    {
        printf("该图不存在回路！");
    }
    return 0;
}

void create_graph_list(vexnode ga[])
{
    int j,k;
    printf("请输入5个顶点的字符数据信息：");
    for (int i = 0; i < n; i++)
    {
        ga[i].vertex = getchar();
        ga[i].link = NULL;
        ga[i].rear = NULL;
    }
    printf("请输入4条边的起、终点i,j：\n");
    for (int i = 0; i < e; i++)
    {
        scanf("%d,%d",&j,&k);
        edgenode *s = (edgenode *)malloc(sizeof(edgenode));
        s->adjvex = k;
        s->next = NULL;
        if (ga[j].rear == NULL)
        {
            ga[j].link = s;
            ga[j].rear = s;
        }
        else
        {
            ga[j].rear->next = s;
            ga[j].rear = s;
        }
        edgenode *m = (edgenode *)malloc(sizeof(edgenode));
        m->adjvex = j;
        m->next = NULL;
        if (ga[k].rear == NULL)
        {
            ga[k].link = m;
            ga[k].link = m;
        }
        else
        {
            ga[k].rear->next = m;
            ga[k].rear = m;
        }
    }
}

void dfs_print(vexnode ga[],int i)
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

int count_connected_components(vexnode ga[])
{
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    int num = 0;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            dfs(ga,i);
            num++;
        }
    }
    return num;
}

void dfs(vexnode ga[],int i)
{
    edgenode *p;
    visited[i] = 1;
    p = ga[i].link;
    while (p != NULL)
    {
        if (visited[p->adjvex] == 0)
        {
            dfs(ga,p->adjvex);
        }
        p = p->next;
    }
}