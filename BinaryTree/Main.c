#include <stdio.h>
#include <stdlib.h>

#define MAXSTACK 100

//������ ��������
typedef struct BinaryTree
{
	char data;
	struct BinaryTree* parent, * lchild, * rchild;
}BinaryTree, * pBinaryTree;

//����
typedef struct Queue
{
	pBinaryTree data;
	struct Queue* next;
}Queue, * pQueue;

//����ָ��
typedef struct
{
	pQueue front, rear;//ͷ��βָ��
}LinkQueue;

//���ɿ���
int CreateBinaryTreeNULL(pBinaryTree* T)
{
	*T = NULL;
	return 1;
}

//������
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
		*T = NULL; //��Ұ
	}
}

//�������� ��˫��ָ��Ķ����� �����������б���Ҫ�����������
void CreateBinaryTree1(pBinaryTree* T)
{
	char ch;
	scanf("%c", &ch);
	if (ch == ' ') //��
	{
		*T = NULL;
	}
	else
	{
		*T = (pBinaryTree)malloc(sizeof(BinaryTree));
		if (!*T)
			exit(0);
		(*T)->data = ch; //���ɸ����
		CreateBinaryTree1(&(*T)->lchild); //����������
		CreateBinaryTree1(&(*T)->rchild); //����������
	}
}

//��һ���ն���
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

//��QΪ�ն���,�򷵻�1,���򷵻�0
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

//����Ԫ��e ��ΪQ���µĶ�βԪ��
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

//�����в���,ɾ��Q�Ķ�ͷԪ��,��e������ֵ,������1,���򷵻�0
int DelQueue(LinkQueue* Q, pBinaryTree* e)
{
	pQueue p;
	if ((*Q).front == (*Q).rear) //����Ϊ��
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

//�������� �������������ʾ�Ķ�����
int CreateBiTree2(pBinaryTree* T)
{
	LinkQueue q;
	pBinaryTree a;
	CreateBinaryTree1(T); //��˫��ָ������������ʾ�Ķ�����
	if (*T)
	{
		(*T)->parent = NULL;
		CreateQueue(&q); //��������
		InsertQueue(&q, *T); //��ָ�����
		while (!InspectQueue(q)) //���в���
		{
			DelQueue(&q, &a); //����,����Ԫ�ظ���a
			if (a->lchild) //������
			{
				a->lchild->parent = a; //�����ӵ�˫��ָ�븳ֵ
				InsertQueue(&q, a->lchild); //�������
			}
			if (a->rchild) //���Һ���
			{
				a->rchild->parent = a; //���Һ��ӵ�˫��ָ�븳ֵ
				InsertQueue(&q, a->rchild); //�Һ������
			}
		}
	}
	return 1;
}

//����T�ĸ�
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

//����p��ָ����ֵ
pBinaryTree ReturnNode(pBinaryTree p)
{
	return p->data;
}

//��p��ָ��㸳ֵΪvalue
void AssignmentNode(pBinaryTree p, char value)
{
	p->data = value;
}

//��������ָ��Ԫ��ֵΪe�Ľ���ָ��
pBinaryTree ReturnPoint(pBinaryTree T, char e)
{
	LinkQueue q;
	pBinaryTree a;

	if (T)
	{
		CreateQueue(&q); //��������
		InsertQueue(&q, T); //��������
		while (!InspectQueue(q)) //�Ӳ���
		{
			DelQueue(&q, &a); //����,����Ԫ�ظ���a
			if (a->data == e)
			{
				return a;
			}
			if (a->lchild) //������
			{
				InsertQueue(&q, a->lchild); //�������
			}
			if (a->rchild) //���Һ���
			{
				InsertQueue(&q, a->rchild); //����Һ���
			}
		}
	}
	return NULL;
}

//��e��T�ķǸ����,�򷵻�����˫��,���򷵻ؿ�
char ReturnParent(pBinaryTree T, char e)
{
	pBinaryTree a;
	if (T) //�ǿ���
	{
		a = ReturnPoint(T, e); //a�ǽ��e��ָ��
		if (a && a != T) //���ڽ��e�Ǹ�
		{
			return a->parent->data;
		}
	}
	return ' ';
}

int main()
{
	int i;
	pBinaryTree T, c, q;
	char e1, e2, z;

	while (1)
	{
		CreateBinaryTreeNULL(&T);
		printf("�밴�������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n");
		CreateBiTree2(&T);
		e1 = ReturnRoot(T);
		if (e1 != ' ')
			printf("�������ĸ�Ϊ: %c\n", e1);
		else
			printf("���գ��޸�\n");

		printf("\n\n");

		printf("����ݹ����������:\n");
		PreOrderTraverse(T, visitT);

		printf("\n\n");

		printf("����ݹ����������:\n");
		InOrderTraverse(T, visitT);

		printf("\n\n");

		printf("����ݹ����������:\n");
		PostOrderTraverse(T, visitT);

		printf("\n\n");

		printf("�������������:\n");
		LevelOrderTraverse(T, visitT);

		printf("\n\n");

		printf("����ǵݹ����������:\n");
		PreOrder(T, visitT);

		printf("\n\n");

		printf("����ǵݹ����������:\n");
		InOrder(T, visitT);

		printf("\n\n");

		printf("����ǵݹ����������:\n");
		PostOrder(T, visitT);

		printf("\n\n");

		while (1)
		{
			printf("������һ������ֵ: ");
			scanf("%*c");
			scanf("%c%*c", &e1);
			c = ReturnPoint(T, e1); // cΪe1��ָ��
			if (c == NULL)
			{
				printf("���в����ڸýڵ�\n");
				printf("\n\n");

				printf("\n\n�Ƿ������ѯ�� Y/N\n");
				scanf("%c", &z);
				if (z == 'N')
				{
					break;
				}
			}
			else
			{
				printf("����ֵΪ%c\n", ReturnNode(c));
				printf("\n\n");

				e2 = e1;
				AssignmentNode(c, e2);
				e1 = ReturnParent(T, e2);
				if (e1 != ' ')
				{
					printf("%c��˫����%c\n", e2, e1);
				}
				else
				{
					printf("%cû��˫��\n", e2);
				}
				e1 = ReturnLeftChild(T, e2);
				if (e1 != ' ')
				{
					printf("%c��������%c\n", e2, e1);
				}
				else
				{
					printf("%cû������\n", e2);
				}
				e1 = ReturnRightChild(T, e2);
				if (e1 != ' ')
				{
					printf("%c���Һ�����%c\n", e2, e1);
				}
				else
				{
					printf("%cû���Һ���\n", e2);
				}

				printf("\n\n�Ƿ������ѯ�� Y/N\n");
				scanf("%c", &z);
				if (z == 'N')
				{
					break;
				}
			}
		}

		DelBinaryTree(&T);

		printf("\n\n������һ�������ǽ����� Y/N\n");
		scanf("%*c");
		scanf("%c%*c", &z);
		if (z == 'N')
		{
			break;
		}
	}

	return 0;
}