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

void preorder(bitree *);
void inorder(bitree *);
void postorder(bitree *);

bitree *locate(bitree *,datatype);
bitree *inorder_prior(bitree *);
bitree *inorder_post(bitree *);

int main()
{
    char ch;    
    bitree *q,*y;
    printf("************请建立一棵二叉树***********\n");
    bitree *root = create();
    inthreading(root);
    printf("************该线索二叉树的先序遍历序列为***********\n"); 
    preorder(root); 
    printf("\n"); 
    printf("************该线索二叉树的中序遍历序列为***********\n"); 
    inorder(root);
    printf("\n");
    printf("************该线索二叉树的后序遍历序列为***********\n"); 
    postorder(root);
    printf("\n");
    printf("************请输入待查询的结点***********\n");  
    getchar();
    ch = getchar();
    y = locate(root,ch);
    printf("************输出待查询的结点及其内存地址***********\n"); 
    printf("%c %p\n ",y->data,y);
    q = inorder_prior(y);
    if (q == NULL) printf("************该结点无中序前驱结点***********\n");
    else
    {
        printf("************输出待查询的结点的中序前驱结点及其内存地址***********\n");
        printf("%c %p\n",q->data,q);
    } 
    q = inorder_post(y);
    if (q == NULL) printf("************该结点无中序后继结点***********");
    else
    {
        printf("************输出待查询的结点的中序后继结点及内存地址***********\n");
        printf("%c %p",q->data,q);
    }
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

void preorder(bitree *p)
{
    if (p != NULL)
    {
        printf("%c ",p->data);
        if (p->ltag == 0) preorder(p->lchild);
        if (p->rtag == 0) preorder(p->rchild);
    }
}

void inorder(bitree *p)
{
    while (p != NULL && p->ltag == 0) p = p->lchild;
    while (p != NULL)
    {
        printf("%c ",p->data);
        if (p->rtag == 1) p = p->rchild;
        else
        {
            p = p->rchild;
            while (p != NULL && p->ltag == 0) p = p->lchild; 
        }
    }
}

/*
void inorder(bitree *p)
{
    if (p != NULL)
    {
        if (p->ltag == 0) inorder(p->lchild);
        printf("%c ",p->data);
        if (p->rtag == 0) inorder(p->rchild);
    }
}
*/

void postorder(bitree *p)
{
    if (p != NULL)
    {
        if (p->ltag == 0) postorder(p->lchild);
        if (p->rtag == 0) postorder(p->rchild);
        printf("%c ",p->data);
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

bitree *inorder_prior(bitree *y)
{
    if (y->ltag == 1) return y->lchild;
    else
    {
        y = y->lchild;
        while (y != NULL && y->rtag == 0) y = y->rchild;
        return y;
    }
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