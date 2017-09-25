/*
 * An Implementation of Red Black Binary Search Tree.
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
	int data;
	struct tree *lchild;
	struct tree *rchild;
	char colour;

};
/*
 * LlProblem() is called when a skewed Left RED RED issue occurs. In this we will rotate right the 3 Generation the Grand, Parent and the child such that the grandparent becomes the Right child of Parent.
 */
struct tree *llproblem(struct tree *q)
{
	struct tree *a,*b,*c,*x,*y;

	a=b=c=x=y=NULL;
	
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
	
	q->rchild->colour = 'r';
	q->colour = 'b';
	
	return q;
}
/*
 * RrProblem() is called when a skewed Right RED RED issue occurs. In this we will rotate right the 3 Generation the Grand, Parent & uncle and the child such that the grand parent becomes the Left child of Parent.
 */
struct tree *rrproblem(struct tree *q)
{
	struct tree *a,*b,*c,*x,*y;

	a=b=c=x=y=NULL;

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

	q->lchild->colour = 'r';
	q->colour = 'b';
		
	return q;
}
/*
 * LrProblem() is called when a issue of RED RED occurs for a Right Child of the Left Parent of the Grand-parent. 
 * In this we will Rotate Right the Parent and the Child so that the Parent becomes Child and viceversa making it a LLProblem. 
 * This LlProblem can be solved using Right rotation of the skewed Left nodes. 
 */
struct tree *lrproblem(struct tree *q)
{
	struct tree *a,*b;
	struct tree *c,*d;
	struct tree *x,*y,*z;

	a=b=c=d=x=z=y=NULL;
	
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

	q->colour = 'b';
	q->rchild->colour = 'r';

	return q;
}
/*
 * RlProblem() is called when a issue of RED RED occurs for a Left Child of the Right Parent of the Grand-Parent. 
 * In this we will Rotate Light the Parent and the Child so that the Parent becomes Child and viceversa making it a RrProblem. 
 * This RrProblem can be solved using Left rotation of the skewed Right nodes. 
 */
struct tree *rlproblem(struct tree *q)
{
	struct tree *a,*b;
	struct tree *c,*d;
	struct tree *x,*y,*z;

	a=b=c=d=x=z=y=NULL;
	
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

	q->colour = 'b';
	q->lchild->colour = 'r';

	return q;
}
/*
 * Node_Colour() maintains the colour of each node, and changes the colour if RED RED colour problems occurs in LL,LR,RR,RL patterns.
 */
struct tree *node_colour( struct tree *q , int data)
{
	struct tree *sib1=q->lchild;
	struct tree *sib2=q->rchild;
	char flag;

	if( sib1!= NULL && sib1->lchild != NULL && data == sib1->lchild->data)
		flag=0;
	else if( sib1 != NULL && sib1->rchild != NULL && data == sib1->rchild->data)
		flag=1;
	else if( sib2 != NULL && sib2->lchild != NULL && data == sib2->lchild->data)
		flag=2;
	else
		flag=3;

	if (sib2 == NULL) 
	{
	    if (flag == 0)
		q=llproblem(q);
	    else if (flag == 1)
		q=lrproblem(q);
		return q;
	}
	else if(sib1 == NULL )
	{
	    if (flag == 2)
		q=rlproblem(q);
	    else if(flag == 3)
		q=rrproblem(q);
	}
	else if(sib1->colour == 'r' && sib2->colour == 'r')
	{
		if (sib1!=NULL)
		    sib1->colour = 'b';
		if (sib2!=NULL)
		    sib2->colour = 'b';
		q->colour = 'r';
	}
	else
	{
		if (flag==0)
		    q=llproblem(q);
		else if(flag == 1)
		    q=lrproblem(q);
		else if(flag==2)
		    q=rlproblem(q);
		else if(flag==3)
		    q=rrproblem(q);
	}
	
	return q;
}
/*
 * Insert_Tree() will insert the new node and calls the node_colour() to maintain the balance.
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
		p->colour='r';
	}
	else if (p->data >= data )
	{
		p->lchild= (struct tree *) insert_tree( (void *)p->lchild, data);
		if (p->lchild->lchild != NULL)
		{
			if (p->lchild->colour=='r' && p->lchild->lchild->colour=='r')
				p=node_colour(p,data);
		}	
		else if (p->lchild->rchild!=NULL)
			if (p->lchild->colour=='r' && p->lchild->rchild->colour=='r')
				p=node_colour(p,data);
	}
	else if(p->data < data )
	{
		p->rchild= (struct tree *) insert_tree( (void *)p->rchild, data);
		if (p->rchild->lchild != NULL)
		{
			if (p->rchild->colour=='r' && p->rchild->lchild->colour=='r')
				p=node_colour(p,data);
		}	
		else if (p->rchild->rchild!=NULL)
			if (p->rchild->colour=='r' && p->rchild->rchild->colour=='r')
				p=node_colour(p,data);
	}

	q= (void *)p;
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
		printf("%d%c- ",temp->data,temp->colour);
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
		printf("%d%c- ",temp->data,temp->colour);
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
		printf("%d%c- ",temp->data,temp->colour);
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
	printf("\n\n\n");
	printf("\nPREORDER  :  ");
	preorder(p);
	printf("\nINORDER   :  ");
	inorder(p);
	printf("\nPOSTORDER :  ");
	postorder(p);
	printf("\n\n\n\n\n");
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
		printf("\n\t\t---MENU---\n\n1. Enter Node\n2. Delete Node\n3. Search Node\n4. Display Tree\n");
		printf("0. EXIT\n\nEnter your Choice:  ");
		scanf("%hd",&choice);
		
		switch(choice)
		{
			case 1: printf("\n\nEnter the Data that needs to be Inserted in the tree: ");
				scanf("%d",&data);
				p = (struct tree *) insert_tree((void *)p, data);
				if (p->colour == 'r')
				    p->colour = 'b';
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
				printf("\n\nExiting... \n\n");
				CLS;
				break;

			default: printf("\n\nWrong INPUT!!!");
				CLS;
				break;
		}
		
	}while(choice!=0);

	return 0;
}

