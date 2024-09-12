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
void preorder(bitree *);
void swap(bitree *);

int main()
{
    bitree *pb = create();
    printf("******************交换之前的原二叉树的先序遍历序列为：\n");
    preorder(pb);
    printf("\n");
    swap(pb);
    printf("******************交换之后的原二叉树的先序遍历序列为：\n");
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
    return;
}

void swap(bitree *t)
{
    if (t != NULL)
    {
        if (t->lchild && t->rchild && (t->lchild->data < t->rchild->data))
        {
            bitree *temp = t->lchild;
            t->lchild = t->rchild;
            t->rchild = temp;
        }
        if (t->lchild != NULL) swap(t->lchild);
        if (t->rchild != NULL) swap(t->rchild);
    }
}