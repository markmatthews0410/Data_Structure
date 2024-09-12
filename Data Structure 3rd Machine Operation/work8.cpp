#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int maxsize = 1024;

typedef struct node
{
    char data;
    struct node *lchild;
    struct node *rchild;
}bitree;

bitree *createtree();
void inorder(bitree *,char *);
void search(char *,char);

int main()
{
    printf("请输入一个二叉树：");
    bitree *root = createtree();
    printf("该二叉树中序遍历序列为：");
    char tree[maxsize];
    inorder(root,tree);
    puts(tree);
    printf("请输入待查找的结点：");
    char c = getchar();
    char ch1;
    scanf("%c",&ch1);
    search(tree,ch1);
    return 0;
}

bitree *createtree()
{
    bitree *queue[maxsize];
    bitree *s,*root;
    int front = 1,rear = 0;
    char ch;
    root = NULL;
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
            if(s && queue[front])
            {
                if(rear%2 == 0) queue[front]->lchild = s;
                else queue[front]->rchild = s;
            }
            if(rear%2 == 1) front++;
        }
    }
    return root;
}

void inorder(bitree *t,char *tree)
{
    bitree *p = t;
    bitree *stack[maxsize];
    int top = -1,i = 0;
    while (!(p == NULL && top == -1))
    {
        if (p != NULL)
        {
            stack[++top] = p;
            p = p->lchild;
        }
        else
        {
            p = stack[top--];
            tree[i++] = p->data;
            p = p->rchild;
        }
    }
}

void search(char *tree,char ch1)
{
    int i;
    if(ch1 == tree[strlen(tree)-1])
    {
        printf("结点%c没有中序后继结点",ch1);
        return;
    }
    else
    {
        for(i = 0;i < strlen(tree)-1;i++)
        {
            if(tree[i] == ch1)
            {
                printf("结点%c的中序后继结点为%c",ch1,tree[i+1]);
                return;
            }
        }
    }
    printf("结点%c不在二叉树中",ch1);
}