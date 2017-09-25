/*
*	This program is to implement a graphs and to find the Single Source Shortest Path using Dijkstra Algorithm.
*
*/
#include"../include/Header.h"

/*
* Structure ShortestPath will store the shortest path to any vertex from a start point/via a parent chosen from the user.
*/

struct ShortestPath
{
	char vertex;
	char parent;
} sp[10];

/*
* Structure DistanceMap will store the distances of the vertex from the start point. It will change it's value from infinity to the shortest distance found while traversing throught the graph
*/

struct DistanceMap
{
	unsigned char vertex;
	unsigned short distance;
} dm[10];
/*
* Structure Map will temporarily store distances from the vertex to source node, this structure is sorted and then the minimum distance is extracted from the array.
*/
struct Map
{
	char vertex;
	unsigned short distance;
} map[10];

/*
 * Graph structure will store the graph vertex details.
 */
struct Graph
{
	char vertex;
	int distance;
	struct Graph *next;
	
} **ptr;

unsigned short NodeCount;
/*
 * To Clear the Terminal screen.
 */
void clearscreen(void)
{
	printf("\033[H\033[J");
}
/*
 * the Pre-Exit() which performs all the pre-exit procedure like freeing up of heap memory.
 */
void pre_exit()
{
	struct Graph *temp=NULL, *new=NULL;
	int i;

	for(i=0;i<NodeCount;i++)
	{
		temp=new=ptr[i]->next;

		while(temp)
		{
			new=temp->next;
			memset(temp,'\0', sizeof(struct Graph));
			free(temp);
			temp=new;
		}

		memset(ptr[i],'\0', sizeof(struct Graph));
		free(ptr[i]);
		ptr[i]=NULL;
	}	

	free(ptr);
}
/*
 * Swap() will simply swap the array elements of struct map data type for the sorting technique used.
 */
void swap(struct Map *a, struct Map *b)
{
	struct Map temp;
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
		    if (map[j].distance < map[min].distance)
			min = j;
		swap(&map[min], &map[i]);
	}
}


void SSSP(unsigned char start)
{
	unsigned short i=0,flag=0;
	unsigned short j=0,count=0;
	unsigned char temp=0;
	unsigned char k=0;
	struct Graph *traverse=NULL;
/*
 * Here, we will initialize the map data structure with all the vertices.
 * Initialize the start vertex with 0 distance and others with distance of 65530(approx. Infinity).
 */

	for(i=0;i<NodeCount;i++)
	{
		map[i].vertex = ptr[i]->vertex;
								
		if (map[i].vertex == start)
		    map[i].distance = 0;
		else
		    map[i].distance = 65530;
	}
	
	for(i=0;i<NodeCount;i++)
	{
		findmin(i);
		temp = map[i].vertex;
/*
 * We have extracted the minimum value from the map data structure and now will find the distance of the neighbour from temp.
 */
		j=0;
		while( ptr[j]!= NULL && temp!= ptr[j]->vertex) j++;
/*
 * If vertex not found in graph, we simply get out of the loop.
 */
		if(ptr[j]==NULL)
		break;
/*
 * Else we will traverse along the graph for the vertices neighbour.
 * Also, We Insert the value of current vertex with distance from A in the DM DS.
 */
		traverse = ptr[j]->next;

		dm[i].vertex= map[i].vertex;
		dm[i].distance = map[i].distance;

		while(traverse)
		{
			flag=0;
			for (j=i+1;j<NodeCount;j++)
			{
/*
 * For every neighbour in the graph, we traverse the map DS and check whether that element is present or not.
 * If present then, we simpy will check the value of the distance.
 * If the distance, in the map DS is less than the distance of that vertex from start, we will replace the distance.
 * Also we should update the vertex and parent in the sp DS.
 */	
				if(traverse->vertex == map[j].vertex)
				{
					if(map[j].distance > (traverse->distance + dm[i].distance))
					{
						map[j].distance = (traverse->distance + dm[i].distance);
						for (k=0;k<NodeCount;k++)
						{
							if(sp[k].vertex == map[j].vertex)
							{
								flag=1;
								break;
							}
						}
						if(flag==1)
						{
							sp[k].parent = temp;
							break;							
						}
						else
						{
							sp[count].vertex=traverse->vertex;
							sp[count++].parent=temp;
						}
					}
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
void display(unsigned char start)
{
	unsigned int i,j;
		
	printf("\n\n\n\n\t\t-----Final Result-----\n\n");
	
	for (i=0;i<NodeCount-1;i++)
		for(j=0;j<NodeCount;j++)
			if(dm[j].vertex == sp[i].vertex)
				printf(" %c|%c| %d \n", start, sp[i].vertex, dm[j].distance);
		
	printf("\n\n");
	
}

/*
 * Main() will take input of graph from user, find the minimum Spanning Tree from the graph(calling MST()) and then display (calling Display())
 */

int main()
{
	unsigned char node='\0', start = '\0';
	unsigned short input;
	unsigned int i=0;
	struct Graph l, *listptr;
	struct Graph *prev=NULL;
	
	printf("\n\nEnter the graph details: \n");
	printf("\nTotal number of nodes: ");
	scanf("%hd",&NodeCount);
/*
 * Taking Heap memory according to the number of Nodes.
 */
	ptr = (struct Graph **) malloc( sizeof(struct Graph *) * NodeCount ) ;

	if(ptr == NULL)
	{
		printf("MALLOC ERROR");
		exit(1);
	}

	for(i=0;i<NodeCount;i++)
	{
		ptr[i] = (struct Graph *) malloc( sizeof(struct Graph)  ) ;

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
		CLS;
		printf("\nEnter the Vertex: ");
		scanf(" %c", &node);	
		input=2;

		ptr[i]->vertex = node;

		while(input)
		{
			prev = listptr;

			printf("\nEnter the Neighbour of vertex ( %c ): ", node);
			scanf(" %c", &l.vertex);

			printf("\nEnter the distance from Parent: ");
			scanf(" %d",&l.distance);

			listptr = (struct Graph *)malloc(sizeof(struct Graph));
			listptr->vertex = l.vertex;
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

/* Graph is included now to convert this graph to Single Source Shortest Path */

	CLS;

	printf("\n\nFrom Where do you want to start the SSSP");
	scanf(" %c",&start);

	SSSP(start);
	display(start);
	pre_exit();

	return 0;
}

