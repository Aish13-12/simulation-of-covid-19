#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_VERTICES 10000
#define MAX_EDGES 3000

     

typedef unsigned char vertex;
struct node_key //struct to store the node values of neighbours
{
	int key;
	struct node_key*next;
};

void insert(int key1,struct node_key**head)//insert function for the above node in a linked list
{
	struct node_key*temp1;
	temp1=(struct node_key*)malloc(sizeof(struct node_key));
	temp1->key=key1;
	temp1->next=NULL;
	if(*head==NULL)
	*head=temp1;
	else
	{
		struct node_key*temp=*head;
	    while(temp->next!=NULL)
	    temp=temp->next;
	    temp->next=temp1;
	}   
	
	
	
}
 
struct node_key*arr[MAX_VERTICES];    //array to store the neighbours of each node
struct status//to keep track of the nodes recovered,susceptible and infected
{
	
	int node;
	struct status*next;
};

struct event//struct for the priority queue
{
	int day; //the day the event is supposed to happen
	int node; //the node's number
	char statw; //type of event
	struct event*next;
};

/* heads of susceptoble,infected and recovered lists*/
struct status*susceptible=NULL;
struct status*infected=NULL;
struct status*recovered=NULL;

void appendst(int key,struct status**head)//to append nodes in the SIR lists
{
	struct status*temp1;
	temp1=(struct status*)malloc(sizeof(struct status));
	
	temp1->node=key;
	temp1->next=NULL;
	if(*head==NULL)
	*head=temp1;
	else
	{
		struct status*temp=*head;
	    while(temp->next!=NULL)
	    temp=temp->next;
	    temp->next=temp1;
	}
}

void deletest(int key,struct status**head)//to delete nodes in the SIR lists
{
	struct status*temp=*head,*prev=*head;
	while(temp->node!=key)
	{
		prev=temp;
		temp=temp->next;
		
	}	
	
	if(temp==*head)
	{
		*head=temp->next;
		free(temp);
	}
	else if(temp->next==NULL&&temp!=*head)
	{
		prev->next=NULL;
		free(temp);
	}
	else
	{
		prev->next=temp->next;
		temp->next=NULL;
		free(temp);
	}
}
/*The implementation of the priority queue has been done using linked lists.The node with highest priority is obtained by searching the entire list */

struct event*prqueuehead=NULL;//head of the events list

void appendeve(char statw1,int day1,int key,struct event**head)//to append events to the list
{
	struct event*temp1;
	temp1=(struct event*)malloc(sizeof(struct event));
	temp1->statw=statw1;
	temp1->day=day1;
	temp1->node=key;
	temp1->next=NULL;
	if(*head==NULL)
	*head=temp1;
	else
	{
		struct event*temp=*head;
		while(temp->next!=NULL)
		temp=temp->next;
		temp->next=temp1;
	}
}

void deleteeve(int key,struct event**head)//to delete events from the list
{
	struct event*temp=*head,*prev=*head;
	while(temp->node!=key)
	{
		prev=temp;
		temp=temp->next;
		
	}	
	
	if(temp==*head)
	{
		*head=temp->next;
		free(temp);
	}
	else if(temp->next==NULL&&temp!=*head)
	{
		prev->next=NULL;
		free(temp);
	}
	else
	{
		prev->next=temp->next;
		temp->next=NULL;
		free(temp);
	}
}			
		
int numofpeoplestat(struct status*head)//returns number of nodes in a list
{
	struct status*temp=head;
	int i=0;
	while(temp!=NULL)
	{
		i++;
		temp=temp->next;
	}
	return i;
}	
	
/* returns 0 if a particular node exists in an y one of the SIR lists else returns 1*/
int findnodestat(int key,struct status*head)
{
	if(head==NULL)
	return 1;
	else
	{
		struct status*temp=head;
	    while(temp!=NULL)
	    {
			if(temp->node==key)
			break;
			temp=temp->next;
        }
	   if(temp==NULL)
	   return 1;
	   else
	   return 0;
	  } 
	
}			
		
void printstat(struct status*head)//for printing any of the SIR lists
{
	struct status*temp=head;
	while(temp!=NULL)
	{
		printf("%d ",temp->node);
		temp=temp->next;
	}
}	
										
	


int main(){

     
        
        /*number of nodes in a graph*/

        srand ( time(NULL) );

        int numberOfVertices = 10000;//as given in the project.pdf, constructing the graph with 10000 nodes
        

     

        /*number of maximum edges a vertex can have*/

        srand ( time(NULL) );

        int maxNumberOfEdges = rand() % MAX_EDGES;

        /*graphs is 2 dimensional array of pointers*/

        if( numberOfVertices == 0)

            numberOfVertices++;

        vertex ***graph;

        printf("Total Vertices = %d, Max # of Edges = %d\n",numberOfVertices, maxNumberOfEdges);

     

        /*generate a dynamic array of random size*/

        if ((graph = (vertex ***) malloc(sizeof(vertex **) * numberOfVertices)) == NULL){

            printf("Could not allocate memory for graph\n");

            exit(1);

        }

     

        /*generate space for edges*/

        int vertexCounter = 0;

        /*generate space for vertices*/

        int edgeCounter = 0;

     

        for (vertexCounter = 0; vertexCounter < numberOfVertices; vertexCounter++){

            if ((graph[vertexCounter] = (vertex **) malloc(sizeof(vertex *) * maxNumberOfEdges)) == NULL){

                printf("Could not allocate memory for edges\n");

                exit(1);

            }

            for (edgeCounter = 0; edgeCounter < maxNumberOfEdges; edgeCounter++){

                if ((graph[vertexCounter][edgeCounter] = (vertex *) malloc(sizeof(vertex))) == NULL){

                    printf("Could not allocate memory for vertex\n");

                    exit(1);

                }

            }

        }

     

        /*start linking the graph. All vetrices need not have same number of links*/

        vertexCounter = 0;edgeCounter = 0;
        
        
       
        /* For node number "vertexCounter",all its neighbours are stored in a linked list whose head is in turn stored in arr[vertexCounter]*/
        for (vertexCounter = 0; vertexCounter < numberOfVertices; vertexCounter++){
			struct node_key*head=NULL;
			
			
			

            //printf("%d:\t",vertexCounter);
            
            
            
            
            
            

            for (edgeCounter=0; edgeCounter < maxNumberOfEdges; edgeCounter++){
				

                if (rand()%2 == 1){ /*link the vertices*/

                    int linkedVertex = rand() % numberOfVertices;

                    graph[vertexCounter][edgeCounter] = graph[linkedVertex];
                    insert(linkedVertex,&head);

                    //printf("%d, ", linkedVertex);
                    
                  
                    
                    
                    
                    
                    

                }

                else{ /*make the link NULL*/

                    graph[vertexCounter][edgeCounter] = NULL;

                }
                

            }
            arr[vertexCounter]=head;

           //printf("\n");

        }
        int j;
	    for(j=0;j<numberOfVertices;j++) //pushng all the nodes in susceptible list
	    appendst(j,&susceptible);
	    
	    
	    
	    int first_infec=rand()%numberOfVertices;//selecting a random node to be infected
	    
	    appendst(first_infec,&infected);//pushing the selected node in the infected list
	    deletest(first_infec,&susceptible);//deleting that node fron the "S" list
	    
	    
	    int i=0;
	    /* calculating number of days for transmission and recovery */
	    while((int)(100.0 * rand() / (RAND_MAX + 1.0)) + 1>50) //when the value of expression is <50 i.e a coin with a probabilty of 0.5 of it showing heads
	    i++;
	    appendeve('T',i,first_infec,&prqueuehead);
	    
	    i=0;
	    while((int)(100.0 * rand() / (RAND_MAX + 1.0)) + 1>20)//when the value of expression is <20 i.e a coin with a probabilty of 0.2 of it showing heads
	    i++;
	    appendeve('R',i,first_infec,&prqueuehead);
	    
	    i=0;
	    int numberOfdays;
	    /* only susceptible nodes can be infected ,not the recovered or already infected nodes*/
	    
	    for(numberOfdays=0;numberOfdays<300;numberOfdays++)//simulating for 300 days
	    {
			int y=numofpeoplestat(recovered);
			if(y==numberOfVertices)//if number of people recovered equals 10000 then stop the simulation
			break;
			else
			{
				
				struct event*temp=prqueuehead;
				while(temp!=NULL)//traversing the event list
				{
					
					if(temp->day==numberOfdays)//the day of occurence matches with the present day
					{
						
						if(temp->statw=='T')//if the event is transmission
						{
							
							struct node_key*temp1=arr[temp->node];//accessing the neighbours of the node
							while(temp1!=NULL)
							{
								if(findnodestat(temp1->key,susceptible)==0)//if the node is in the "S" list
								{
									deletest(temp1->key,&susceptible);
									appendst(temp1->key,&infected);
									/* adding events to the list*/
									
									while((int)(100.0 * rand() / (RAND_MAX + 1.0)) + 1>50)
									i++;
									appendeve('T',i+numberOfdays,temp1->key,&prqueuehead);
									i=0;
									while((int)(100.0 * rand() / (RAND_MAX + 1.0)) + 1>20)
									i++;
									appendeve('R',i+numberOfdays,temp1->key,&prqueuehead);
									i=0;
									temp1=temp1->next;
								}
								else
								temp1=temp1->next;
									
									
							}
							deleteeve(temp->node,&prqueuehead);//deleting the original event of transmission from the event list
						}
						else
						{
							/* if event is recovery*/
							appendst(temp->node,&recovered);
							deletest(temp->node,&infected);
							deleteeve(temp->node,&prqueuehead);	//deleting the event of recovery from event list
						}
						temp=temp->next;
					}
					else /* if the day of occurence hasn't yet occured*/
					temp=temp->next;
						
					
				}
				
			}
			
		}
		printf("Infected:");					
		printstat(infected);		
		printf("\n");
		printf("\n");
		printf("Susceptible:");
		printstat(susceptible);
		printf("\n");
		printf("\n");
		printf("Recovered:");
		printstat(recovered);
				
	    return 0;

}
