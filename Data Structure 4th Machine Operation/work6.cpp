#include<stdio.h>
#include<stdlib.h>

#define n 5
#define e 5

typedef char vextype;
typedef int adjtype;

typedef struct 
{
    vextype vexs[n];
    adjtype arcs[n][n];
}adjacency_matrix_graph;

typedef struct node
{
    int adjvex;
    struct node *next;
}edgenode;

typedef struct 
{
    vextype vertex;
    edgenode *link;
    edgenode *rear;
}vexnode;

adjacency_matrix_graph *create_adjacency_matrix();
void transform_matrix_into_list(adjacency_matrix_graph *,vexnode []);
void dfs_adjacency_matrix(adjacency_matrix_graph *,int);
void dfs_adjacency_list(vexnode [],int);

int matrix_visited[n];
int list_visited[n];

int main()
{
    adjacency_matrix_graph *g = create_adjacency_matrix();
    vexnode ga[n];
    transform_matrix_into_list(g,ga);
    for (int k = 0; k < n; k++)
    {
        matrix_visited[k] = 0;
    }
    for (int k = 0; k < n; k++)
    {
        list_visited[k] = 0;
    }
    printf("邻接矩阵dfs遍历如下：");
    dfs_adjacency_matrix(g,0);
    printf("\n");
    printf("邻接表dfs遍历如下：");
    dfs_adjacency_list(ga,0);
    printf("\n");
    return 0;
}

adjacency_matrix_graph *create_adjacency_matrix()
{
    adjacency_matrix_graph *g = (adjacency_matrix_graph *)malloc(sizeof(adjacency_matrix_graph));
    int i,j,k;
    printf("请创建顶点表：");
    for (i = 0; i < n; i++) 
    {
        g->vexs[i] = getchar();
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            g->arcs[i][j] = 0;
        }
    }
    printf("请创建邻接矩阵：");       
    for (k = 0; k < e; k++)
    {
        scanf("%d %d",&i,&j);
        g->arcs[i][j] = 1;
        g->arcs[j][i] = 1;
    }
    return g;
}

void transform_matrix_into_list(adjacency_matrix_graph *g,vexnode ga[])
{
    int i,j;
    for (i = 0; i < n; i++)
    {
        ga[i].vertex = g->vexs[i];
        ga[i].link = NULL;
        ga[i].rear = NULL;
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (g->arcs[i][j] == 1)
            {
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
    }
}

void dfs_adjacency_matrix(adjacency_matrix_graph *g,int i)
{
    int j;
    printf("%c ",g->vexs[i]);
    matrix_visited[i] = 1;
    for (j = 0; j < n; j++)
    {
        if ((g->arcs[i][j] == 1) && (matrix_visited[j] == 0))
        {
            dfs_adjacency_matrix(g,j);
        }
    }
}

void dfs_adjacency_list(vexnode ga[],int i)
{
    edgenode *p;
    printf("%c ",ga[i].vertex);
    list_visited[i] = 1;
    p = ga[i].link;
    while (p != NULL)
    {
        if (list_visited[p->adjvex] == 0)
        {
            dfs_adjacency_list(ga,p->adjvex);
        }
        p = p->next;
    }
}