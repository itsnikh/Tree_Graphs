/*
*	This program is to implement graphs and to show output using minimum Spanning Tree
*
*/

#include"../include/Header.h"

/*
 * The structure Mst will store the Final shortest/minimum weights  from a vertex to any vertex.
 */

struct mst
{
	char s;
	char d;
	short dist;
	char v;
}m[100];

/*
 * The structure Map will store the shortest distance from any vertex to any vertex.
 */

struct map
{
	char data;
	unsigned short value;
}v[100] ;

/*
 * The structure Graph will store the Graph vertices and edge weights which we will take as input from the user.
 */

struct graph
{
	char node;
	int distance;
	struct graph *next;
	
} **ptr;

unsigned short NodeCount;

/*
 * the Pre-Exit() which performs all the pre-exit procedure like freeing up of heap memory.
 */

void pre_exit()
{
	struct graph *temp=NULL, *new=NULL;
	int i;

	for(i=0;i<NodeCount;i++)
	{
		temp=new=ptr[i]->next;

		while(temp)
		{
			new=temp->next;
			free(temp);
			memset(temp,'\0', sizeof(struct graph));
			temp=new;
		}

		free(ptr[i]);
		memset(ptr[i],'\0', sizeof(struct graph));
		ptr[i]=NULL;
	}	

	free(ptr);
}

/*
 * Swap() will simply swap the array elements of struct map data type for the sorting technique used.
 */

void swap(struct map *a, struct map *b)
{
	struct map temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * FindMin() will do the sorting of the data Structure map, so that we can select the minimum of the all distances from respective neighbour. 
 */

void findmin(int start)
{
	int i, j, min;
 
	for (i = start; i < NodeCount; i++)
	{
		min = i;
		for (j = i+1; j <NodeCount; j++)
		    if (v[j].value < v[min].value)
			min = j;
		swap(&v[min], &v[i]);
	}
}

/*
 * MST() will find the minimum Spanning Tree out of the graph which we taken as input from the user.
 */

void MST()
{
	unsigned short i=0,flag=0;
	unsigned short j=0,c=0;
	unsigned char temp=0;
	unsigned char k=0;
	struct graph *traverse=NULL;

	for(i=0;i<NodeCount;i++)
	{
		v[i].data=ptr[i]->node;
		if (i==0)
		    v[0].value=0;
		else
		    v[i].value=65530;
	}
	
	for(i=0;i<NodeCount;i++)
	{
		findmin(i);
		temp = v[i].data;
		j=0;
		
		while( ptr[j]!= NULL && temp!= ptr[j]->node) j++;

		if(ptr[j]==NULL)
		break;

		traverse = ptr[j]->next;
		while(traverse)
		{
			flag=0;
			for (j=i+1;j<NodeCount;j++)
			{
				if(traverse->node == v[j].data)
				{
					for(k=0;k<NodeCount;k++)
					  if(v[j].data == m[k].v)
					  {	flag = 1; break;}

					if (flag ==1 && v[j].value > traverse->distance)
					{
						m[k].s=temp;
						m[k].d=traverse->node;
						m[k].dist = v[j].value = traverse->distance;	
						break;
					}
					else if (v[j].value > traverse->distance)
					{
						v[j].value = traverse->distance;
						m[c].s=temp;
						m[c].d=traverse->node;
						m[c].dist = v[j].value;
						m[c++].v = v[j].data;
						break;
					}
					else continue;
				}
				else continue;
			}
			traverse=traverse->next;
			
		}

	}
	
}

/*
 * Display() will show the final result.
 */

void display()
{
	unsigned int i;
	unsigned int sum=0;
	
	printf("\n\n\n\n\t\t-----Final Result-----\n\n");
	
	for (i=0;i<NodeCount-1;i++)
	{
	    printf(" %c%c --> ", m[i].s,m[i].d);
		sum+=m[i].dist;
	}
	printf("NULL\n\n");
	printf("Minimum Distance = %d\n\n\n\n\n\n",sum);
	
}

/*
 * Main() will take input of graph from user, find the minimum Spanning Tree from the graph(calling MST()) and then display (calling Display())
 */

int main()
{
	unsigned char node='\0';
	unsigned short input;
	unsigned int i=0;
	struct graph l, *listptr;
	struct graph *prev=NULL;
	
	printf("\n\nEnter the graph details: \n");
	printf("\nTotal number of nodes: ");
	scanf("%hd",&NodeCount);
/*
 * Taking Heap memory according to the number of Nodes.
 */

	ptr = (struct graph **) malloc( sizeof(struct graph *) * NodeCount ) ;

	if(ptr == NULL)
	{
		printf("MALLOC ERROR");
		exit(1);
	}

	for(i=0;i<NodeCount;i++)
	{
		ptr[i] = (struct graph *) malloc( sizeof(struct graph)  ) ;

		if (!ptr[i])
		{
			printf("ptr[%d] Failed",i);
			exit(1);
		}
	}
/*
 * Taking input for the graph
 */	

	for(i=0;i<NodeCount;i++)						
	{
		printf("\nEnter the New Home Character: ");
		scanf(" %c", &node);	
		input=2;

		ptr[i]->node = node;

		while(input)
		{
			prev = listptr;

			printf("\nEnter the New node Character: ");
			scanf(" %c", &l.node);

			printf("\nEnter the distance from Parent: ");
			scanf(" %d",&l.distance);

			listptr = (struct graph *)malloc(sizeof(struct graph));
			listptr->node = l.node;
			listptr->distance = l.distance;
			listptr->next = NULL;

			if(input == 2)
			{
				prev = listptr;
				ptr[i]->next = listptr; 

			}
			else
			prev->next = listptr;
			
			printf("\nWant to add more to this Parent (1/0): ");
			scanf(" %hd", &input);
			if (input == 0 )
			    break;
			else continue;

		}
	}

/* 
 * Graph is included now to convert this graph to Minimum Spanning Tree by calling MST();
 */

	MST();
	display();
	pre_exit();

	return 0;
}

