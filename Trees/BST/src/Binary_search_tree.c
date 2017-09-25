/*
 * An Implementation of Binary Search Tree.
 */

#include"../include/Header.h"

/*
 * ClearScreen() will clear the Bash terminal Page.
 */
void clearscreen(void)
{
	printf("\033[H\033[J");

}
/*
 * Structure will to maintain the tree
 */
struct tree
{
	unsigned int data;
	struct tree *lchild;
	struct tree *rchild;

};
/*
 * Node_Delete() will delete the node which it receives as agrument when called from Delete_tree().
 */
struct tree *node_delete( struct tree *q, struct tree *prev, int data)
{
	struct tree *temp = q;
	struct tree *swap=NULL;
	int min;
	while(temp)
	{
		if(temp->data == data)
		   break;
		prev=temp;
		if(temp->lchild!=NULL)
		temp->lchild=node_delete( temp->lchild, prev,data);
		if(temp->rchild!=NULL)
			temp->rchild=node_delete( temp->rchild, prev, data);
		break;
		//temp=NULL;
	}

	if(temp!=NULL && temp->data == data)
	{
		if(temp->lchild == NULL && temp->rchild == NULL)
		{
			free(temp);
			memset(temp, '\0', sizeof(struct tree));
			temp=NULL;
			return temp;
		}
		else if(temp->lchild == NULL || temp->rchild == NULL)
		{
			if (temp->lchild == NULL)
			{
				if(prev->lchild->data == data)
				{
					prev->lchild = temp->rchild;
					free(temp);
					memset(temp, '\0', sizeof(struct tree));
					temp=NULL;
					return prev->lchild;
				}
				else if(prev->rchild->data == data)
				{
					prev->rchild = temp->rchild;
					free(temp);
					memset(temp, '\0', sizeof(struct tree));
					temp=NULL;
					return prev->rchild;
				}
			}
			else if (temp->rchild == NULL)
			{
				if(prev->lchild->data == data)
				{
					prev->lchild = temp->lchild;
					free(temp);
					memset(temp, '\0', sizeof(struct tree));
					temp=NULL;
					return prev->lchild;
				}
				else if(prev->rchild->data == data)
				{
					prev->rchild = temp->lchild;
					free(temp);
					memset(temp, '\0', sizeof(struct tree));
					temp=NULL;
					return prev->rchild;
				}
			}
		}
		else if (temp->lchild!=NULL && temp->rchild!=NULL)
		{
			swap=temp;
			temp=temp->rchild;
			while(temp!=NULL)
			{
				if(temp->lchild == NULL)
					break;
				prev=temp;
				temp=temp->lchild;
			}

			min = temp->data;
			temp->data = swap->data;
			swap->data = min;
			free(temp);
			memset(temp, '\0', sizeof(struct tree));
			temp=NULL;
			prev->lchild = NULL;
			return prev->lchild;
		}
	}

	return temp;
}
/*
 * Insert_Tree() will simply check the number according to the Binary Search Property and delete them accordingly.
 */
void insert_tree( void **q, int data )
{
	struct tree *p = (struct tree *)*q;
	struct tree *temp=NULL;

	if(p==NULL)
	{
		p= (struct tree*)malloc(sizeof(struct tree));
		if(p==NULL) {
		printf("MALLOC ERROR");
		exit(1);
		}
		p->data=data;
		p->lchild=NULL;
		p->rchild=NULL;
		*q=p;
		return;
	}
	else
	{
		temp=p;
		while(temp!=NULL)
		{
			p=temp;
			if(temp->data >= data)
				temp=temp->lchild;
			else if (temp->data < data)
				temp=temp->rchild;
		}

		temp = (struct tree *) malloc(sizeof(struct tree));
		temp->data=data;
		temp->lchild=temp->rchild=NULL;
		if(data <= p->data)
			p->lchild=temp;
		else if (data > p->data )
			p->rchild=temp;

	}
}
/*
 * Delete_Tree() calls node_delete() to delete the desired node according to the procedure.
 */
void delete_tree(void **q, int data)
{
	struct tree *p = (struct tree *) *q;
	struct tree *prev;
	prev=p;

	p=node_delete(p,prev,data);
	*q = (void *) p;
}
/*
 * Search_Tree() searches for the node, and return True / False for the element to be searched.
 */
char search_tree(void *q, int data)
{
	CLS;
	struct tree *p = (struct tree *) q;
	struct tree *temp=p;
	char flag=1;
	
	while(temp)
	{
		if(temp->data == data)
		{
			printf("\n\nDATA is Present!!");
			flag=0;
			return flag;
		}
		if(temp->lchild!=NULL)
			flag = search_tree( (void *) temp->lchild, data);
		if (flag == 0)
		   break;
		if(temp->rchild!=NULL)
			flag = search_tree( (void *) temp->rchild, data);
		if (flag == 0)
		   break;
		temp=NULL;	
	}

	return flag;
}
/*
 * PreOrder() Displays the result in PreOrder form.
 */
void preorder(struct tree *p)
{
	struct tree *temp=p;

	while(temp)
	{
		printf("%d ",temp->data);
		if(temp->lchild!=NULL)
			preorder( temp->lchild);
		if(temp->rchild!=NULL)
			preorder( temp->rchild);
		temp=NULL;
	}

	return;
}
/*
 * InOrder() Displays the result in InOrder form.
 */
void inorder(struct tree *p)
{
	struct tree *temp=p;

	while(temp)
	{
		if(temp->lchild!=NULL)
			inorder( temp->lchild);
		printf("%d ",temp->data);
		if(temp->rchild!=NULL)
			inorder( temp->rchild);
		temp=NULL;
	}

	return;
}
/*
 * PostOrder() Displays the result in PostOrder form.
 */
void postorder(struct tree *p)
{
	struct tree *temp=p;

	while(temp)
	{
		if(temp->lchild!=NULL)
			postorder( temp->lchild);
		if(temp->rchild!=NULL)
			postorder( temp->rchild);
		printf("%d ",temp->data);
		temp=NULL;
	}

	return;
}
/*
 * Display() calls PreOrder(), Inorder(), PostOrder() to display the result in each format.
 */
void display_tree(void *q)
{
	struct tree *p= (struct tree *)q;

	if(p==NULL)
	{
		
		printf("\n\n\t\tCannot Display...Tree Empty!!");
		return;
	}

	CLS;
	printf("\n\n\n\n\n");
	printf("\nPREORDER  : ");
	preorder(p);
	printf("\nINORDER   : ");
	inorder(p);
	printf("\nPOSTORDER : ");
	postorder(p);
	return;
}
/*
 * Pre_Exit() will free the Heap memeory used.
 */
void pre_exit(struct tree **p)
{
	struct tree *temp=*p;

	while(temp)
	{
		if(temp->lchild!=NULL)
			pre_exit( &temp->lchild);
		if(temp->rchild!=NULL)
			pre_exit( &temp->rchild);
		free(temp);
		memset(temp, '\0', sizeof(struct tree));
		temp=NULL;
		*p=temp;
	}
	printf("\n\n\n");
	return;
}
/*
 * Main() is a Menu Driven function which gives user the option to choose whether he wants to insert/delete/search a node and calls their respective functions.
 */
int main(void)
{
	struct tree *p=NULL;
	int data=0;
	unsigned char flag=1;
	short choice=0;

	CLS;

	do
	{
		printf("\n\t\t---MENU---\n\n1. Enter Node\n2. Delete Node\n3. Search Node\n4. Display Tree\n");
		printf("0. EXIT\n\nEnter your Choice:  ");
		scanf("%hd",&choice);
		
		switch(choice)
		{
			case 1: printf("\n\nEnter the Data that needs to be Inserted in the tree: ");
				scanf("%d",&data);
				insert_tree((void *)&p, data);
				CLS;
				break;

			case 2: printf("\n\nEnter the Data that needs to be Deleted in the tree: ");
				scanf("%d",&data);
				if( search_tree((void *)p,data)==1)
				{
					printf("\nEntry Cannot be Deleted\n");
					break;
				}
				delete_tree((void *)&p, data);
				CLS;
				break;

			case 3: printf("\n\nEnter the Data that needs to be Searched in the tree: ");
				scanf("%d",&data);
				flag = search_tree((void *)p, data);
				if(flag == 0)
					printf("\n\nEntry found \n\n\n\n");
				else if (flag == 1) 
					printf("\n\nNo Match Found!!\n\n\n\n");
				//CLS;
				break;

			case 4: CLS;
				display_tree((void *)p );
				break;

			case 0: pre_exit(&p);
				CLS;
				break;

			default: printf("\n\nWrong INPUT!!!");
				 CLS;
				 break;
		}
		
	}while(choice!=0);

	return 0;
}

