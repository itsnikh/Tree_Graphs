/*
 * An Implementation of AVL Binary Search Tree.
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
	int height;

};

/*
 * Max() will return the max value out of both it's Argument
 */
int max(int a, int b)
{
	return ( (b>a)?b:a );
}
/*
 * LlProblem() is called when a skewed Left issue occurs. In this we will rotate right the 3 Generation the Grand, Parent & uncle and the child such that the grand parent becomes the Right child of Parent.
 */
struct tree *llproblem(struct tree *q)
{
	struct tree *a,*b,*c,*x,*y;
	
	y=q;
	x=q->lchild;
	c=q->rchild;
	a=x->lchild;
	b=x->rchild;	

	y->lchild = b;
	y->rchild = c;
	q=x;
	q->lchild = a;
	q->rchild = y;
	return q;
}
/*
 * RrProblem() is called when a skewed Right issue occurs. In this we will rotate right the 3 Generation the Grand, Parent & uncle and the child such that the grand parent becomes the Left child of Parent.
 */
struct tree *rrproblem(struct tree *q)
{
	struct tree *a,*b,*c,*x,*y;

	x=q;
	a=q->lchild;
	y=q->rchild;
	b=y->lchild;
	c=y->rchild;

	x->lchild = a;
	x->rchild = b;	
	q=y;
	q->lchild = x;
	q->rchild = c;
		
	return q;
}
/*
 * LrProblem() is called when a issue of balance occurs for a Right Child of the Left Parent of the Grand-parent. 
 * In this we will Rotate Right the Parent and the Child so that the Parent becomes Child and viceversa making it a LLProblem. 
 * This LlProblem can be solved using Right rotation of the skewed Left nodes. 
 */
struct tree *lrproblem(struct tree *q)
{
	struct tree *a,*b;
	struct tree *c,*d;
	struct tree *x,*y,*z;
	
	x=q;
	y=x->lchild;
	a=x->rchild;
	b=y->lchild;
	z=y->rchild;
	c=z->lchild;
	d=z->rchild;

	y->lchild=b;
	y->rchild=c;
	x->lchild=d;
	x->rchild=a;
	q=z;
	q->lchild=y;
	q->rchild=x;

	return q;
}
/*
 * RlProblem() is called when a issue of balance occurs for a Left Child of the Right Parent of the Grand-Parent. 
 * In this we will Rotate Light the Parent and the Child so that the Parent becomes Child and viceversa making it a RrProblem. 
 * This RrProblem can be solved using Left rotation of the skewed Right nodes. 
 */
struct tree *rlproblem(struct tree *q)
{
	struct tree *a,*b;
	struct tree *c,*d;
	struct tree *x,*y,*z;
	
	x=q;
	a=x->lchild;
	y=x->rchild;
	z=y->lchild;
	b=y->rchild;
	c=z->lchild;
	d=z->rchild;	

	x->lchild=a;
	x->rchild=c;
	y->lchild=d;
	y->rchild=b;
	q=z;
	q->lchild=x;
	q->rchild=y;

	return q;
}
/*
 * Balance_tree() maintains the balance of the tree, and balances if any problems like LL,LR,RR,RL occurs.
 */
struct tree *balance_tree( struct tree *q , int data)
{
	struct tree *p = q;
	struct tree *temp=p;
	short balance;


	if (p->rchild==NULL )
	   balance = temp->lchild->height + 1;
	else if(p->lchild == NULL)
	   balance = -(temp->rchild->height + 1);
	else	
	balance = (temp->lchild->height + 1 ) - (temp->rchild->height + 1 );


	if(balance == 0 || balance == 1 || balance == -1 )
		return temp;
	else if(balance > 2)
	{
		balance_tree(temp->lchild, data);
	}
	else if(balance < -2)
	{
		balance_tree(temp->rchild, data);
	}
	else if(balance==2)
	{
		if (temp->lchild->data >= data )	
			temp = llproblem(temp);
		else if (temp->lchild->data < data)
			temp = lrproblem(temp);
	}
	else if(balance == -2)
	{

		if ( data > temp->rchild->data )	
			temp = rrproblem(temp);
		else if(data <= temp->rchild->data ) 	
			temp = rlproblem(temp);
			
	}
	return temp;
}
/*
 * Insert_Tree() will insert the new node and calls the balancing functions to maintain the balance.
 */
void* insert_tree( void *q, int data )
{
	struct tree *p = (struct tree *)q;

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
		p->height=0;
	}
	else if (p->data >= data )
	{
		p->lchild= (struct tree *) insert_tree( (void *)p->lchild, data);
		if (p->rchild == NULL)
		   p->height = p->lchild->height + 1;
		else
		   p->height = max ( p->lchild->height , p->rchild->height) + 1;

		if (p->height>1)
		   p=balance_tree(p,data);
	}
	else if(p->data < data )
	{
		p->rchild= (struct tree *) insert_tree( (void *)p->rchild, data);
		if (p->lchild == NULL)
		   p->height = p->rchild->height + 1;
		else
		   p->height = max ( p->lchild->height , p->rchild->height) + 1;
		if ( p->height > 1 )
		  p=balance_tree(p,data);
	}
	q=(void *)p;
	return q;
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
	printf("\n\n\n");
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
 * Main() is a Menu Driven function which gives user the option to choose whether he wants to insert/search a node and calls their respective functions.
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
		printf("\n\t\t---MENU---\n\n1. Enter Node\n2. Search Node\n3. Display Tree\n");
		printf("0. EXIT\n\nEnter your Choice:  ");
		scanf("%hd",&choice);
		
		switch(choice)
		{
			case 1: printf("\n\nEnter the Data that needs to be Inserted in the tree: ");
				scanf("%d",&data);
				p = (struct tree *) insert_tree((void *)p, data);
				//height( (void *)p, data);
				CLS;
				break;

			case 2: printf("\n\nEnter the Data that needs to be Searched in the tree: ");
				scanf("%d",&data);
				flag = search_tree((void *)p, data);
				if(flag == 0)
					printf("\n\nEntry found \n\n\n\n");
				else if (flag == 1) 
					printf("\n\nNo Match Found!!\n\n\n\n");
				//CLS;
				break;

			case 3: CLS;
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

