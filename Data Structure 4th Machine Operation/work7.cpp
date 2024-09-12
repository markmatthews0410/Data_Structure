#include<stdio.h>
#include<stdlib.h>

#define maxsize 1024

typedef struct node
{
    int weight;
    struct node *lchild,*rchild;
}bitree;

bitree *create_tree();
void preorder(bitree *);
void inorder(bitree *);
int wpl(bitree *,int);

int main()
{
    bitree *root = create_tree();
    printf("该二叉树的先序DFS序列为：");
    preorder(root);
    printf("\n");
    printf("该二叉树的中序DFS序列为：");
    inorder(root);
    printf("\n");
    int root_wpl = wpl(root,0);
    printf("该二叉树的WPL为：");
    printf("%d\n",root_wpl);
    return 0;
}

bitree *create_tree()
{
    bitree *queue[maxsize],*root = NULL;
    int front = 1,rear = 0,weight;
    while (1)
    {
        scanf("%d",&weight);
        if (weight == -1) break;
        bitree *s = NULL;
        if (weight != 0)
        {
            s = (bitree *)malloc(sizeof(bitree));
            s->weight = weight;
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

void preorder(bitree *p)
{
    if (p != NULL)
    {
        printf("%d ",p->weight);
        preorder(p->lchild);
        preorder(p->rchild);
    }
}

void inorder(bitree *p)
{
    if (p != NULL)
    {
        inorder(p->lchild);
        printf("%d ",p->weight);
        inorder(p->rchild);
    }
}

int wpl(bitree *root,int depth)
{
    if (root == NULL) return 0;
    int left_wpl = wpl(root->lchild,depth+1);
    int right_wpl = wpl(root->rchild,depth+1);
    int current_wpl = 0;
    if (left_wpl == 0 && right_wpl == 0) current_wpl = root->weight*depth;
    return (left_wpl+right_wpl+current_wpl);
}