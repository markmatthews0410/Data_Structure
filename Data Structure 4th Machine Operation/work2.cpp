#include<stdio.h>
#include<stdlib.h>

const int maxsize = 1024;
typedef char datatype;
typedef struct node
{
    datatype data;
    struct node *lchild,*rchild;
}bitree;

bitree *create();
bitree *preorder_delete(bitree *,datatype);
void preorder(bitree *);

int main()
{
    printf("***************请构建二叉树：\n");
    bitree *pa = create();
    printf("***************原二叉树的先序遍历序列为：");
    preorder(pa);
    printf("\n***************请输入待删除的结点x：");
    getchar();
    datatype x = getchar();
    bitree *pb = preorder_delete(pa,x);
    printf("***************删除子树后的二叉树的先序遍历序列：");
    preorder(pa);
    printf("\n");
    printf("***************被删除子树的先序遍历序列为：");
    preorder(pb);
    printf("\n");
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

void preorder(bitree *t)
{
    if (t != NULL)
    {
        printf("%c ",t->data);
        preorder(t->lchild);
        preorder(t->rchild);
    }
}

bitree *preorder_delete(bitree *pa,datatype x)
{
    bitree *p = pa,*stack[maxsize],*root;
    int top = -1,i = 0,flag = -1;
    datatype *tree;
    while (!(p == NULL && top == -1))
    {
        if (p != NULL)
        {
            stack[++top] = p;
            if (p->lchild != NULL)
            {
                if (p->lchild->data == x) 
                {
                    flag = 0;
                    break;
                }
            }
            if (p->rchild != NULL)
            {
                if (p->rchild->data == x) 
                {
                    flag = 1;
                    break;
                }
            }
            p = p->lchild;
        }
        else
        {
            p = stack[top--];
            p = p->rchild;
        }
    }
    if (flag == 0)
    {
        root = p->lchild;
        p->lchild = NULL;
    }
    else if (flag == 1)
    {
        root = p->rchild;
        p->rchild = NULL;
    }
    return root;
}