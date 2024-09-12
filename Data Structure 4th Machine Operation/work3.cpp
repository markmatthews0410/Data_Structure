#include<stdlib.h>
#include<stdio.h>

const int maxsize = 1024;

typedef char datatype;
typedef struct node
{
    datatype data;
    struct node *lchild,*rchild;
}bitree;

bitree *create();
void preorder(bitree *);

int main()
{
    printf("按层次输入二叉树，虚结点输入'@'，以'#'结束输入：");
    bitree *root = create();
    printf("************输出先序遍历序列如下***********\n");
    preorder(root);
    return 0;
}

bitree *create()
{
    bitree *queue[maxsize],*root = NULL;
    int front = 1,rear = 0;
    char ch;
    while ((ch = getchar()) != '#')
    {
        bitree *s = NULL;
        if (ch != '@')
        {
            s = (bitree *)malloc(sizeof(bitree));
            s->data = ch;
            s->lchild = NULL;
            s->rchild = NULL;
        }
        queue[++rear] = s;
        if (rear == 1) root = s;
        else
        {
            if (s && queue[front])
            {
                if (rear%2 == 0) queue[front]->lchild = s;
                else queue[front]->rchild = s;
            }
            if (rear%2 == 1) front++;
        }
    }
    return root;
}

void preorder(bitree *root)
{
    bitree *stack[maxsize],*p = root;
    int top = -1;
    while (p != NULL || top != -1)
    {
        if (p != NULL)
        {
            stack[++top] = p;
            printf("%c ",p->data);
            p = p->lchild;
        }
        else
        {
            p = stack[top--];
            p = p->rchild;
        }
    }
}