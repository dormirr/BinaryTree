#include <stdio.h>
#include <stdlib.h>

#define MAXSTACK 100

//二叉树 三叉链表
typedef struct BinaryTree
{
	char data;
	struct BinaryTree* parent, * lchild, * rchild;
}BinaryTree, * pBinaryTree;

//队列
typedef struct Queue
{
	pBinaryTree data;
	struct Queue* next;
}Queue, * pQueue;

//队列指针
typedef struct
{
	pQueue front, rear;//头、尾指针
}LinkQueue;

//生成空树
int CreateBinaryTreeNULL(pBinaryTree* T)
{
	*T = NULL;
	return 1;
}

//销毁树
void DelBinaryTree(pBinaryTree* T)
{
	if (*T)
	{
		if ((*T)->lchild)
		{
			DelBinaryTree(&(*T)->lchild);
		}
		if ((*T)->rchild)
		{
			DelBinaryTree(&(*T)->rchild);
		}
		free(*T);
		*T = NULL; //防野
	}
}

//先序输入 无双亲指针的二叉树 完整的三叉列表需要调用这个函数
void CreateBinaryTree1(pBinaryTree* T)
{
	char ch;
	scanf("%c", &ch);
	if (ch == ' ') //空
	{
		*T = NULL;
	}
	else
	{
		*T = (pBinaryTree)malloc(sizeof(BinaryTree));
		if (!*T)
			exit(0);
		(*T)->data = ch; //生成根结点
		CreateBinaryTree1(&(*T)->lchild); //生成左子树
		CreateBinaryTree1(&(*T)->rchild); //生成右子树
	}
}

//建一个空队列
int CreateQueue(LinkQueue* Q)
{
	(*Q).front = (*Q).rear = (pQueue)malloc(sizeof(Queue));
	if (!(*Q).front)
	{
		exit(0);
	}
	(*Q).front->next = NULL;
	return 1;
}

//若Q为空队列,则返回1,否则返回0
int InspectQueue(LinkQueue Q)
{
	if (Q.front == Q.rear)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//插入元素e 成为Q的新的队尾元素
int InsertQueue(LinkQueue* Q, pBinaryTree e)
{
	pQueue p = (pQueue)malloc(sizeof(Queue));
	if (!p)
	{
		exit(0);
	}
	p->data = e;
	p->next = NULL;
	(*Q).rear->next = p;
	(*Q).rear = p;
	return 1;
}

//若队列不空,删除Q的队头元素,用e返回其值,并返回1,否则返回0
int DelQueue(LinkQueue* Q, pBinaryTree* e)
{
	pQueue p;
	if ((*Q).front == (*Q).rear) //队列为空
	{
		return 0;

	}
	p = (*Q).front->next;
	*e = p->data;
	(*Q).front->next = p->next;
	if ((*Q).rear == p)
	{
		(*Q).rear = (*Q).front;
	}
	free(p);
	return 1;
}

//先序输入 构造三叉链表表示的二叉树
int CreateBiTree2(pBinaryTree* T)
{
	LinkQueue q;
	pBinaryTree a;
	CreateBinaryTree1(T); //无双亲指针的三叉链表表示的二叉树
	if (*T)
	{
		(*T)->parent = NULL;
		CreateQueue(&q); //创建队列
		InsertQueue(&q, *T); //根指针入队
		while (!InspectQueue(q)) //队列不空
		{
			DelQueue(&q, &a); //出队,队列元素赋给a
			if (a->lchild) //有左孩子
			{
				a->lchild->parent = a; //给左孩子的双亲指针赋值
				InsertQueue(&q, a->lchild); //左孩子入队
			}
			if (a->rchild) //有右孩子
			{
				a->rchild->parent = a; //给右孩子的双亲指针赋值
				InsertQueue(&q, a->rchild); //右孩子入队
			}
		}
	}
	return 1;
}

//返回T的根
char ReturnRoot(pBinaryTree T)
{
	if (T)
	{
		return T->data;
	}
	else
	{
		return ' ';
	}
}

//返回p所指结点的值
pBinaryTree ReturnNode(pBinaryTree p)
{
	return p->data;
}

//给p所指结点赋值为value
void AssignmentNode(pBinaryTree p, char value)
{
	p->data = value;
}

//返回树中指向元素值为e的结点的指针
pBinaryTree ReturnPoint(pBinaryTree T, char e)
{
	LinkQueue q;
	pBinaryTree a;

	if (T)
	{
		CreateQueue(&q); //创建队列
		InsertQueue(&q, T); //根结点入队
		while (!InspectQueue(q)) //队不空
		{
			DelQueue(&q, &a); //出队,队列元素赋给a
			if (a->data == e)
			{
				return a;
			}
			if (a->lchild) //有左孩子
			{
				InsertQueue(&q, a->lchild); //入队左孩子
			}
			if (a->rchild) //有右孩子
			{
				InsertQueue(&q, a->rchild); //入队右孩子
			}
		}
	}
	return NULL;
}

//若e是T的非根结点,则返回它的双亲,否则返回空
char ReturnParent(pBinaryTree T, char e)
{
	pBinaryTree a;
	if (T) //非空树
	{
		a = ReturnPoint(T, e); //a是结点e的指针
		if (a && a != T) //存在结点e非根
		{
			return a->parent->data;
		}
	}
	return ' ';
}

//返回e的左孩子 无则返回空
char ReturnLeftChild(pBinaryTree T, char e)
{
	pBinaryTree a;
	if (T)
	{
		a = ReturnPoint(T, e); //a是结点e的指针
		if (a && a->lchild) //T中存在结点e且e存在左孩子
		{
			return a->lchild->data; //返回e的左孩子的值
		}
	}
	return ' ';
}

//返回e的右孩子 无则返回空
char ReturnRightChild(pBinaryTree T, char e)
{
	pBinaryTree a;
	if (T)
	{
		a = ReturnPoint(T, e); //a是结点e的指针
		if (a && a->rchild) //T中存在结点e且e存在右孩子
		{
			return a->rchild->data; //返回e的右孩子的值
		}
	}
	return ' ';
}

//先序递归遍历
void PreOrderTraverse(pBinaryTree T, int(*Visit)(pBinaryTree))
{
	if (T)
	{
		Visit(T);
		PreOrderTraverse(T->lchild, Visit);
		PreOrderTraverse(T->rchild, Visit);
	}
}

//中序递归遍历
void InOrderTraverse(pBinaryTree T, int(*Visit)(pBinaryTree))
{
	if (T)
	{
		InOrderTraverse(T->lchild, Visit);
		Visit(T);
		InOrderTraverse(T->rchild, Visit);
	}
}

//后序递归遍历
void PostOrderTraverse(pBinaryTree T, int(*Visit)(pBinaryTree))
{
	if (T)
	{
		PostOrderTraverse(T->lchild, Visit);
		PostOrderTraverse(T->rchild, Visit);
		Visit(T);
	}
}

//层序遍历
void LevelOrderTraverse(pBinaryTree T, int(*Visit)(pBinaryTree))
{
	LinkQueue q;
	pBinaryTree a;
	if (T)
	{
		CreateQueue(&q);
		InsertQueue(&q, T);
		while (!InspectQueue(q))
		{
			DelQueue(&q, &a);
			Visit(a);
			if (a->lchild != NULL)
			{
				InsertQueue(&q, a->lchild);
			}
			if (a->rchild != NULL)
			{
				InsertQueue(&q, a->rchild);
			}
		}
	}
}

//遍历调用
int visitT(pBinaryTree T)
{
	if (T)
	{
		printf("%c是", T->data);
	}
	if (T->parent)
	{
		printf("%c", T->parent->data);
		if (T->parent->lchild == T)
		{
			printf("的左孩子\n");
		}
		else
		{
			printf("的右孩子\n");
		}
	}
	else
	{
		printf("根结点\n");
	}
	return 1;
}

//非递归前序遍历二叉树
void PreOrder(pBinaryTree T, int(*Visit)(pBinaryTree))
{
	pBinaryTree stack[MAXSTACK], p;
	int top = -1;

	if (T != NULL)
	{
		top++;
		stack[top] = T; //根入栈

		while (top > -1) //树不为空
		{
			p = stack[top];
			top--;
			Visit(p);

			if (p->rchild != NULL) //右孩子入栈
			{
				top++;
				stack[top] = p->rchild;
			}

			if (p->lchild != NULL) //左孩子入栈
			{
				top++;
				stack[top] = p->lchild;
			}
		}
	}
}

//非递归中序遍历二叉树
void InOrder(pBinaryTree T, int(*Visit)(pBinaryTree))
{
	pBinaryTree stack[MAXSTACK], p;
	int top = -1;

	if (T != NULL)
	{
		p = T;
		while (top > -1 || p != NULL) //栈不为空或遍历未完成
		{
			while (p != NULL) //所有左节点入栈 包括根
			{
				top++;
				stack[top] = p;
				p = p->lchild;
			}
			if (top > -1)
			{
				p = stack[top];
				top--;
				Visit(p); //左出栈
				p = p->rchild; //右节点入栈
			}
		}
	}
}

//非递归后序遍历二叉树
void PostOrder(pBinaryTree T, int(*Visit)(pBinaryTree))
{
	pBinaryTree stack[MAXSTACK], p;
	int sign, top = -1;
	if (T != NULL)
	{
		do
		{
			while (T != NULL)
			{
				top++;
				stack[top] = T; //T下所有左节点入栈 包括根
				T = T->lchild;
			}

			p = NULL;
			sign = 1; //正在处理当前结点

			while (top != -1 && sign)
			{

				T = stack[top]; //出栈

				if (T->rchild == p) //右孩子不存在或右孩子已访问则访问T
				{
					Visit(T);
					top--;
					p = T; //p指向被访问的节点
				}
				else
				{
					T = T->rchild; //T指向右孩子节点

					sign = 0; //处理非栈顶结点
				}
			}
		} while (top != -1);
	}
}

int main()
{
	int i;
	pBinaryTree T, c, q;
	char e1, e2, z;

	while (1)
	{
		CreateBinaryTreeNULL(&T);
		printf("请按先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
		CreateBiTree2(&T);
		e1 = ReturnRoot(T);
		if (e1 != ' ')
			printf("二叉树的根为: %c\n", e1);
		else
			printf("树空，无根\n");

		printf("\n\n");

		printf("先序递归遍历二叉树:\n");
		PreOrderTraverse(T, visitT);

		printf("\n\n");

		printf("中序递归遍历二叉树:\n");
		InOrderTraverse(T, visitT);

		printf("\n\n");

		printf("后序递归遍历二叉树:\n");
		PostOrderTraverse(T, visitT);

		printf("\n\n");

		printf("层序遍历二叉树:\n");
		LevelOrderTraverse(T, visitT);

		printf("\n\n");

		printf("先序非递归遍历二叉树:\n");
		PreOrder(T, visitT);

		printf("\n\n");

		printf("中序非递归遍历二叉树:\n");
		InOrder(T, visitT);

		printf("\n\n");

		printf("后序非递归遍历二叉树:\n");
		PostOrder(T, visitT);

		printf("\n\n");

		while (1)
		{
			printf("请输入一个结点的值: ");
			scanf("%*c");
			scanf("%c%*c", &e1);
			c = ReturnPoint(T, e1); // c为e1的指针
			if (c == NULL)
			{
				printf("树中不存在该节点\n");
				printf("\n\n");

				printf("\n\n是否继续查询？ Y/N\n");
				scanf("%c", &z);
				if (z == 'N')
				{
					break;
				}
			}
			else
			{
				printf("结点的值为%c\n", ReturnNode(c));
				printf("\n\n");

				e2 = e1;
				AssignmentNode(c, e2);
				e1 = ReturnParent(T, e2);
				if (e1 != ' ')
				{
					printf("%c的双亲是%c\n", e2, e1);
				}
				else
				{
					printf("%c没有双亲\n", e2);
				}
				e1 = ReturnLeftChild(T, e2);
				if (e1 != ' ')
				{
					printf("%c的左孩子是%c\n", e2, e1);
				}
				else
				{
					printf("%c没有左孩子\n", e2);
				}
				e1 = ReturnRightChild(T, e2);
				if (e1 != ' ')
				{
					printf("%c的右孩子是%c\n", e2, e1);
				}
				else
				{
					printf("%c没有右孩子\n", e2);
				}

				printf("\n\n是否继续查询？ Y/N\n");
				scanf("%c", &z);
				if (z == 'N')
				{
					break;
				}
			}
		}

		DelBinaryTree(&T);

		printf("\n\n输入另一棵树还是结束？ Y/N\n");
		scanf("%*c");
		scanf("%c%*c", &z);
		if (z == 'N')
		{
			break;
		}
	}

	return 0;
}