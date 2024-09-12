#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char a[100];
int k=0;
// 链表节点结构体
typedef struct node 
{
    char data;
    struct node* next;
}node;
// 创建链表节点
node* createnode(char data) 
{
    node* newnode=(node*)malloc(sizeof(node));
    newnode->data=data;
    newnode->next=NULL;
    return newnode;
}
// 将字符串转换为链表
node* zhuanlist(char* word) 
{	
	node* head=createnode('\0');
    node* tail=head;
    int len=strlen(word);
    for (int i=0;i<len;i++) 
	{
        node* newnode=createnode(word[i]);
        tail->next=newnode;
        tail=newnode;
    }
    return head->next;
}
// 反转链表
node* fanlinklist(node* head)
{
    node* pre=NULL;
    node* cur=head;
    node* next=NULL;
    while (cur!=NULL)
	{
        next=cur->next;
        cur->next=pre;
        pre=cur;
        cur=next;
    }
    return pre;
}
// 判断两个链表是否具有共同后缀
void hassame(node* head1,node* head2)
{
    while(head1&&head2)
	{
        if(head1->data==head2->data)
		{
            a[k++]=head1->data;
        }
		else
		{
            return ;
        }
        head1=head1->next;
        head2=head2->next;
    }
}

int main() 
{   // 输入两个单词
    char word1[100],word2[100];
    printf("请输入第一个单词：");
    scanf("%s",word1);
    printf("请输入第二个单词：");
    scanf("%s",word2);
    // 将单词转换为链表
    node* list1=zhuanlist(word1);
    node* list2=zhuanlist(word2);
    list1=fanlinklist(list1);
    list2=fanlinklist(list2);
    // 判断是否具有共同后缀
    hassame(list1,list2);
    if(k!=0)
	{
		printf("两个链表具有共同后缀");
    	for(int i=k-1;i>=0;i--)
		{	
        	printf("%c",a[i]);
    	}
	} 
	if(k==0)
	printf("无");
    return 0;
}