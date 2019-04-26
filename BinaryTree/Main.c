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