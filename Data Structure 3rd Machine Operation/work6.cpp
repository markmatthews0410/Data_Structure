#include<stdio.h>
#include<stdlib.h>

const int maxsize = 1024;

typedef char datatype;
typedef struct node
{
    datatype data;
    struct node *lchild,*rchild;
}bitree;

bitree *createtree();
void preorder(bitree *);
void inorder(bitree *);
void swap(bitree *);

int main()
{
    bitree *pb;
    printf("**********按层次输入二叉树，虚结点输入'@'，以'#'结束输入********\n");
    pb = createtree();
    printf("******************交换之前的原二叉树先序遍历序列为：");
    preorder(pb);
    printf("\n");
    printf("******************交换之前的原二叉树中序遍历序列为：");
    inorder(pb);
    printf("\n");
    swap(pb);
    printf("******************交换之后的二叉树先序遍历序列为：");
    preorder(pb);
    printf("\n");
    printf("******************交换之后的二叉树中序遍历序列为：");
    inorder(pb);
    printf("\n");
    return 0;
}

bitree *createtree()
{
    char ch;
    bitree *queue[maxsize];//queue[0]不存
    int front,rear;
    bitree *root,*s;
    root = NULL;
    front = 1;
    rear = 0;
    while ((ch = getchar()) != '#')
    {
        s = NULL;
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

void inorder(bitree *t)
{
    if (t != NULL)
    {
        inorder(t->lchild);
        printf("%c ",t->data);
        inorder(t->rchild);
    }
    return;
}

void swap(bitree *t)
{
    if (t != NULL)
    {
        bitree *temp = t->lchild;
        t->lchild = t->rchild;
        t->rchild = temp;
        swap(t->lchild);
        swap(t->rchild);
    }
}