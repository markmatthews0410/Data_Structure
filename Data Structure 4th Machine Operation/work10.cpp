#include<stdlib.h>
#include<stdio.h>

const int maxsize = 1024;

typedef char datatype;
typedef struct node
{
    datatype data;
    struct node *lchild,*rchild;
    bool ltag,rtag;
}bitree;

bitree *pre = NULL;

bitree *create();
void inthreading(bitree *);
bitree *locate(bitree *,datatype);
bitree *inorder_post(bitree *);

int main()
{
    char ch;    
    bitree *q,*y;
    printf("请建立一棵二叉树:");
    bitree *root = create();
    inthreading(root);
    printf("待查找结点为");  
    getchar();
    ch = getchar();
    y = locate(root,ch);
    q = inorder_post(y);
    if (q == NULL) printf("结点%c没有中序后继结点",ch);
    else printf("结点%c的中序后继结点为%c",ch,q->data);
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
            s->ltag = 0;
            s->rtag = 0;
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

void inthreading(bitree *p)
{
    if (p != NULL)
    {
        inthreading(p->lchild);
        if (p->lchild == NULL)
        {
            p->ltag = 1;
            p->lchild = pre;
        }
        if (p->rchild == NULL) p->rtag = 1;
        if (pre != NULL && pre->rtag == 1) pre->rchild = p;
        pre = p;
        inthreading(p->rchild);
    }
}

bitree *locate(bitree *root,datatype ch)
{
    bitree *p = root;
    while (p != NULL && p->ltag == 0) p = p->lchild;
    while (p != NULL)
    {
        if (p->data == ch) break;
        if (p->rtag == 1) p = p->rchild;
        else
        {
            p = p->rchild;
            while (p != NULL && p->ltag == 0) p = p->lchild; 
        }
    }
    return p;
}

bitree *inorder_post(bitree *y)
{
    if (y->rtag == 1) return y->rchild;
    else
    {
        y = y->rchild;
        while (y != NULL && y->ltag == 0) y = y->lchild;
        return y;
    }
}