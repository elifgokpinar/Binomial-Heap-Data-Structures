//elif.gokpinar project3
//I used given code at the beginning of the code.
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#define Error( Str )        FatalError( Str )
#define FatalError( Str )   fprintf( stderr, "%s\n", Str ), exit( 1 )
typedef double ElementType;
        #define Infinity (60000000000000000000000L)
        #ifndef _BinHeap_H
        #define MaxTrees (30)   /* Stores 2^30 -1 items */
        #define Capacity (1073741823)

        struct BinNode;
        typedef struct BinNode *BinTree;
        struct Collection;
        typedef struct Collection *BinQueue;
       

        BinQueue Initialize( void );
        void Destroy( BinQueue H );
        BinQueue MakeEmpty( BinQueue H );
        BinQueue Insert(float Item,char *pName,int pLength,int pTime,int firstTime ,int wTime,BinQueue H );
        float DeleteMin( BinQueue H );
        BinQueue Merge( BinQueue H1, BinQueue H2 );
        //ElementType FindMin( BinQueue H );
        int IsEmpty( BinQueue H );
        int IsFull( BinQueue H );
        #endif

typedef struct BinNode *Position;

struct BinNode
{
	float Item;
	int processLength;
        int processTime;
	char processName[30];
	int firstEnter;
	int wTime;
    	//model_node_type mn;
    	Position    LeftChild;
    	Position    NextSibling;
};

struct Collection
{
   	int CurrentSize;
    	BinTree TheTrees[ MaxTrees ];
};
		
struct list{
	int key;
	int degree;
	char pName[30];
	int pLength;
	int copyLength;
	int pTime;
	int priorityValue;
	int again;
	int firstEnter;
	int wTime;
	int lTime;
	float AWT;
	struct list *parent;
	struct list *sibling;
	struct list *child;
	struct list *next;
};

	struct list *root=NULL;
	struct list *copyRoot=NULL;
	struct list *awt=NULL;
	int count=0;
	float pValue=0;
	//int emax=4;
	int findemax=-100;
	int addwTime=0;
	int addSequence=0;
	char name[30];
	
//*********************************************************FUNCTIONS*********************************************
	
void insertAwt(struct list** header,float awt){
		
    struct list *newNode=malloc(sizeof(struct list));
    newNode->AWT = awt; 
    newNode->next=NULL;
 
    if(*header == NULL)
	*header = newNode;
    else
    {
        struct list *search =* header;
		
        while(search->next != NULL)
        {
            search = search->next;
        }
        search->next = newNode;
    }
}
	
void insertLinkedList(struct list** header,char *processName,int processLength,int processTime) { 
    struct list *newNode=malloc(sizeof(struct list));
    strcpy(newNode->pName,processName);
    newNode->pLength = processLength; 
    newNode->copyLength=0;
    newNode->pTime=processTime;
    newNode->again=0;
    newNode->firstEnter=0;
    newNode->priorityValue=0;
    newNode->wTime=0;
    newNode->parent = NULL; 
    newNode->next=NULL;
 
    
    if(*header == NULL)
	*header = newNode;
    else
    {
	struct list *search =* header;
		
        	while(search->next != NULL)
        	{
          	  search = search->next;
       	 }
       	 search->next = newNode;
    }
} 

BinQueue Initialize( void ){
            BinQueue H;
            int i;

            H = malloc( sizeof( struct Collection ) );
            if( H == NULL )
                FatalError( "Out of space!!!" );
            H->CurrentSize = 0;
            for( i = 0; i < MaxTrees; i++ )
                H->TheTrees[ i ] = NULL;
            return H;
}

static void DestroyTree( BinTree T ){
    if( T != NULL ){
        DestroyTree( T->LeftChild );
        DestroyTree( T->NextSibling );
        free( T );}
}

void Destroy( BinQueue H ) {
    int i;
    for( i = 0; i < MaxTrees; i++ )
        DestroyTree( H->TheTrees[ i ] );
}

BinQueue MakeEmpty( BinQueue H ){
    int i;
    Destroy( H );
    for( i = 0; i < MaxTrees; i++ )
        H->TheTrees[ i ] = NULL;
        H->CurrentSize = 0;
        return H;
}

BinQueue Insert( float Item,char *pName,int pLength,int pTime,int firstTime,int waitTime, BinQueue H ){
            BinTree NewNode;
            BinQueue OneItem;
	    int i;

            NewNode = malloc( sizeof( struct BinNode ) );
            if( NewNode == NULL )
            FatalError( "Out of space!!!" );
            NewNode->LeftChild = NewNode->NextSibling = NULL;
            NewNode->processLength=pLength;
            NewNode->processTime=pTime;
            NewNode->firstEnter=firstTime;
            NewNode->wTime=waitTime;
            strcpy(NewNode->processName,pName);
	    NewNode->Item = Item;
         
            OneItem = Initialize( );
            OneItem->CurrentSize = 1;
            OneItem->TheTrees[ 0 ] = NewNode;

            return Merge( H, OneItem );
        }

float DeleteMin( BinQueue H ){
            int i, j;
            int MinTree;   /* The tree with the minimum item */
            BinQueue A;
            BinQueue DeletedQueue;
            Position DeletedTree, OldRoot;
            ElementType MinItem;
	    //model_node_type MinItem;

            if( IsEmpty( H ) )
            {
             Error( "Empty binomial queue" );
	     MinItem=-INFINITY;
				
			//  for (i=0; i < max_act_const; i++) {
			//    MinItem.from[i].s=-1;
			//    MinItem->mn.from[i].a=m.from[i].a;
			//  }
                return MinItem;
            }

            MinItem = INFINITY;
            for( i = 0; i < MaxTrees; i++ )
            {
                if( H->TheTrees[ i ] &&
                    H->TheTrees[ i ]->Item < MinItem )
                {
                    /* Update minimum */
                    MinItem = H->TheTrees[ i ]->Item;
	            strcpy(name,H->TheTrees[ i ]->processName);
                    MinTree = i;
                }
            }
		//printf("\n%.3f Min item ",MinItem);
		//printf("\n %s",name);
            DeletedTree = H->TheTrees[ MinTree ];
            OldRoot = DeletedTree;
            DeletedTree = DeletedTree->LeftChild;
            free( OldRoot );

            DeletedQueue = Initialize( );
            DeletedQueue->CurrentSize = ( 1 << MinTree ) - 1;
            for( j = MinTree - 1; j >= 0; j-- )
            {
                DeletedQueue->TheTrees[ j ] = DeletedTree;
                DeletedTree = DeletedTree->NextSibling;
                DeletedQueue->TheTrees[ j ]->NextSibling = NULL;
            }

            H->TheTrees[ MinTree ] = NULL;
            H->CurrentSize -= DeletedQueue->CurrentSize + 1;

            Merge( H, DeletedQueue );
            return MinItem;
        }

int FindMin( BinQueue H ){
            int i;
            ElementType MinItem;

            if( IsEmpty( H ) )
            {
                Error( "Empty binomial queue" );
	        MinItem=0;
                return MinItem;
            }

            MinItem = Infinity;
			
            for( i = 0; i < MaxTrees; i++ )
            {
                if( H->TheTrees[ i ] && H->TheTrees[ i ]->Item < MinItem ) {
                    MinItem = H->TheTrees[ i ]->Item;
	     }	
            }	
            return MinItem;
        }

int IsEmpty( BinQueue H ){
            return H->CurrentSize == 0;
        }

int IsFull( BinQueue H ){
            return H->CurrentSize == Capacity;
        }

BinTree CombineTrees( BinTree T1, BinTree T2 )
        {
            if( T1->Item > T2->Item )
                return CombineTrees( T2, T1 );
            T2->NextSibling = T1->LeftChild;
            T1->LeftChild = T2;
            return T1;
        }

//Merge the binomial heap
BinQueue Merge( BinQueue H1, BinQueue H2 ){
            BinTree T1, T2, Carry = NULL;
            int i, j;

            if( H1->CurrentSize + H2->CurrentSize > Capacity )
                Error( "Merge would exceed capacity" );

            H1->CurrentSize += H2->CurrentSize;
            for( i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2 )
            {
                T1 = H1->TheTrees[ i ]; T2 = H2->TheTrees[ i ];

                switch( !!T1 + 2 * !!T2 + 4 * !!Carry )
                {
                    case 0: /* No trees */
                    case 1: /* Only H1 */
                        break;
                    case 2: /* Only H2 */
                        H1->TheTrees[ i ] = T2;
                        H2->TheTrees[ i ] = NULL;
                        break;
                    case 4: /* Only Carry */
                        H1->TheTrees[ i ] = Carry;
                        Carry = NULL;
                        break;
                    case 3: /* H1 and H2 */
                        Carry = CombineTrees( T1, T2 );
                        H1->TheTrees[ i ] = H2->TheTrees[ i ] = NULL;
                        break;
                    case 5: /* H1 and Carry */
                        Carry = CombineTrees( T1, Carry );
                        H1->TheTrees[ i ] = NULL;
                        break;
                    case 6: /* H2 and Carry */
                        Carry = CombineTrees( T2, Carry );
                        H2->TheTrees[ i ] = NULL;
                        break;
                    case 7: /* All three */
                        H1->TheTrees[ i ] = Carry;
                        Carry = CombineTrees( T1, T2 );
                        H2->TheTrees[ i ] = NULL;
                        break;
                }
            }
            return H1;
        }
BinTree printTree(BinTree p, BinTree *r, int i){
		  BinTree t[100]={NULL}, q; int j;
		  for ( j=0; j<i; j++ ) t[j]= r[j];
		  i=0;
		  if (p!=NULL) { 
		    printf("\n%.3f",p->Item);
		    printf("\n%s    \n waiting time = %d",p->processName, p->wTime);
			q=p->NextSibling;
			j=0;
			do {
			  while (q!=NULL) { 
			    printf("\n%.3f",q->Item); 
			    printf("\n %s		\n waiting time = %d",q->processName, q->wTime);
			    if (q->LeftChild != NULL) { r[i]=q->LeftChild; i++; }
			    q=q->NextSibling;
			  }
			  q=t[j++];
			} while (q!=NULL);
		  }
		  else return NULL;
		  //for (j=0; j<i; j++) t[j]=NULL;
		  
		  printTree(p->LeftChild, r, i);
}

BinTree firstPrint(BinTree p, BinTree *r, int i){
		  BinTree t[100]={NULL}, q; int j;
		  for ( j=0; j<i; j++ ) t[j]= r[j];
		  i=0;
		  if (p!=NULL) { 
		
		    printf(" %s ",p->processName);
			q=p->NextSibling;
			j=0;
			do {
			  while (q!=NULL) { 
			    printf(" %s ",q->processName); 
			    if (q->LeftChild != NULL) { r[i]=q->LeftChild; i++; }
			    q=q->NextSibling;
			  }
			  q=t[j++];
			} while (q!=NULL);
		  }
		  else return NULL;
		  //for (j=0; j<i; j++) t[j]=NULL;
		  
		  firstPrint(p->LeftChild, r, i);
}
BinTree printResults(BinTree p, BinTree *r, int i){
		
		  BinTree t[100]={NULL}, q; int j;
		  for ( j=0; j<i; j++ ) t[j]= r[j];
		  i=0;
		  if (p!=NULL) { 
		  	pValue=0;
		  	if(p->firstEnter==0){
		  		calculateFirstTime(p->processLength);	
			}
			else if(p->firstEnter==1){
			  	calculate(findemax,p->processLength);
			}
		  	//printf("\n pvalue %.2f",pValue);
		  	p->Item=pValue;
		  	//printf("\n%s     waiting time = %d",p->processName, p->wTime);
		  	printf("     ");
		           printf("  %s:%.3f ",p->processName,p->Item);
			q=p->NextSibling;
			j=0;
			do {
			  while (q!=NULL) { 
			    printf("     ");
			    printf("  %s:%.3f ",q->processName,q->Item); 
			    //	printf("\n%s     waiting time = %d",q->processName, q->wTime);
			    if (q->LeftChild != NULL) { r[i]=q->LeftChild; i++; }
			    q=q->NextSibling;
			  }
			  q=t[j++];
			} while (q!=NULL);
		  }
		  else return NULL;
		  //for (j=0; j<i; j++) t[j]=NULL;
		  
		  printResults(p->LeftChild, r, i);
}
//Control the heap
void countNode(BinTree p, BinTree *r, int i){
		
		  BinTree t[100]={NULL}, q; int j;
		  for ( j=0; j<i; j++ ) t[j]= r[j];
		  i=0;
		  if (p!=NULL) { 
		  	count++;
		           //printf("\n%s",p->processName);
			q=p->NextSibling;
			j=0;
			do {
			  while (q!=NULL) { 
			    count++;
			    //printf("\n%s",q->processName); 
			    if (q->LeftChild != NULL) { r[i]=q->LeftChild; i++; }
			    q=q->NextSibling;
			  }
			  q=t[j++];
			} while (q!=NULL);
		  }
		  else return NULL;
		  //for (j=0; j<i; j++) t[j]=NULL;
		  
		  countNode(p->LeftChild, r, i);
}
//Add passed time
BinTree lateTime(BinTree p, BinTree *r, int i){
		  BinTree t[100]={NULL}, q; int j;
		  for ( j=0; j<i; j++ ) t[j]= r[j];
		  i=0;
		  if (p!=NULL) { 
		  
		  struct list* traverse=copyRoot;
		  
		  while(traverse !=NULL){
		  	
		  	if(strcmp(p->processName,traverse->pName)==0){
		  		if(traverse->firstEnter==0){
		  			traverse->firstEnter=1;
		  			traverse->wTime=addSequence - p->processTime ;
				  }
			  }
		  	
		  	traverse=traverse->next;	
		  }

		    //printf(" %s ",p->processName);
			q=p->NextSibling;
			j=0;
			do {
			  while (q!=NULL) { 
			  
		  struct list* traverse1=copyRoot;
		  
		  while(traverse1 !=NULL){
		  	
		  	if(strcmp(q->processName,traverse1->pName)==0){
		  		if(traverse1->firstEnter==0){
		  			traverse1->firstEnter=1;
		  			traverse1->wTime=addSequence - q->processTime ;
				  }
			  }
		  	
		  	traverse1=traverse1->next;		  	
		  }
			
			    //printf(" %s ",q->processName); 
			if (q->LeftChild != NULL) { r[i]=q->LeftChild; i++; }
			    q=q->NextSibling;
			  }
			  q=t[j++];
			} while (q!=NULL);
		  }
		  else return NULL;
		  //for (j=0; j<i; j++) t[j]=NULL;
		  
		  lateTime(p->LeftChild, r, i);
}
//Adds waiting time
BinTree addWaitingTime(BinTree p, BinTree *r, int i ,int process){
		  BinTree t[100]={NULL}, q; int j;
		  for ( j=0; j<i; j++ ) t[j]= r[j];
		  i=0;
		  if (p!=NULL) {
		  struct list *traverse=copyRoot;
		  if(strcmp(name,p->processName)!=0){
		  	traverse=copyRoot;
		  	while(traverse!=NULL){
		  	           if(strcmp(p->processName,traverse->pName)==0){
		  		   traverse->wTime=traverse->wTime+process;
				  }
		  		traverse=traverse->next;
			  }  	
		  } 
		    //printf("\n%.3f",p->Item);
			q=p->NextSibling;
			j=0;
		do {
		while (q!=NULL) { 
		 struct list *traverse1=copyRoot;
		
		 if(strcmp(name,q->processName)!=0){
		  	traverse1=copyRoot;
		  	while(traverse1!=NULL){
		  		if(strcmp(q->processName,traverse1->pName)==0){
		  			traverse1->wTime=traverse1->wTime+process;
				  }
		  		traverse1=traverse1->next;
			  }
		} 
	            if (q->LeftChild != NULL) {
			r[i]=q->LeftChild; i++; 
	           }
		           q=q->NextSibling;
		}
	           q=t[j++];
		      } while (q!=NULL);
		}
		  else return NULL;
		  //for (j=0; j<i; j++) t[j]=NULL;
		  addWaitingTime(p->LeftChild, r, i,process);
}
//calculation of priority
void calculate(int emax,int processLength){
	float a = (float)(2*processLength)/(3*emax);
	float b = pow(a,3);
	float c= exp(-b);
	pValue=(1/c)*processLength;
	//printf("\n%.3f",pValue);
	
}
void calculateFirstTime(int processLength){	
	 pValue=(1)*processLength;
	//printf("\n%.3f",pValue);	
}
void print(struct list* x){
	struct list* tempList=x;
	int i=0;
	while(tempList!=NULL){
		printf("\n%s   %d  %d  ",tempList->pName,tempList->pLength,tempList->pTime);
		tempList=tempList->next;
		i++;
	}
	//printf("%d",i);
}
				
//***********************************************************MAIN FUNCTION**************************************************
int main(){
	BinQueue H1, H2;
	BinTree p, r[100]={NULL};
	ElementType Item;
    	char ch;
    	int i,y;
   	H1 = Initialize( );
         
	FILE *read=fopen("input.txt","r");
	//FILE *output=fopen("output.txt","w");
	char processName[30];
	int processLength;
	int processTime;
	int totalTime=0;
	int t=0;
	int countNodes=0;
	int node=0;

	while(!feof(read)){	
		fscanf(read,"%s %d %d",processName,&processLength,&processTime);
		if(findemax<processLength){
		findemax=processLength;
		}
		insertLinkedList(&root,processName,processLength,processTime);
		insertLinkedList(&copyRoot,processName,processLength,processTime);
		totalTime=totalTime+processLength;
		node++;
	}
	fclose(read);

		//printf("%d",findemax);
		//print(root);
		// Item=(0.0001)*(rand()%10000);
		//Insert(Item,processName,processTime, H1);
		//printf("\n%d  totalTime",node);		    
					    
		struct list *traverse =root;				    
		struct list *search =root;
		struct list *list =root;
		struct list *linList=root;
		struct list *againList=root;
		struct list *awtList=awt;   
					    
		while(list!=NULL){    	
			list->copyLength=list->pLength;		    			    	
			list=list->next;			
		}
	
//********************************************************************************************************				    
					    
		//printf("q = 1");
		//fprintf(output,"%s","q= 1");
		//printf("\nTime Process in BH Priority value of processes in BH\n");
		
		for(t=0; t<=totalTime ; t++){
		//printf("\n %d	",t);
		count=0;	
		traverse=root;
		//Insert the data in the linked list.
        while(traverse!= NULL) {
        	if(t==traverse->pTime && traverse->again !=1 ){
        		//printf("%s ",traverse->pName);
        	
        		calculateFirstTime(traverse->pLength);
        		traverse->firstEnter=0;
		        Item=pValue;
        		
        		traverse->again=1;
        		Insert(Item,traverse->pName,traverse->pLength,traverse->pTime,traverse->firstEnter,traverse->wTime,H1);	
			}
            traverse = traverse->next;
        }
					    //If the binary heap is not empty
					    if(!IsEmpty( H1 )){
					    	/*for (i=0; i<MaxTrees; i++) {
			             		p=H1->TheTrees[i];
						firstPrint(p, r, 0);   
						} 
						for (i=0; i<MaxTrees; i++) {
			             		p=H1->TheTrees[i];
						printResults(p, r, 0);   
						} */
						}
						
						int isDelete=0;
						//Delete the min value.
					    if (!IsEmpty( H1 )){
					    	Item=DeleteMin( H1 );	
					    	isDelete=1;
					    	//printf("%.3f",Item);
						} 
						//If Delete process happened.
						if(isDelete=1){
								
						search=root;
					    	while(search!=NULL){
					    		//printf("%s",name);
					    		//If the process didn't complete,this code works
					    		if(strcmp(search->pName,name)==0){
					    			search->pLength=search->pLength-1;
					    			if(search->pLength>0){
					    			calculate(findemax,search->pLength);	
					    			Item=pValue;
					    			//Insert again the process in the BH
								Insert(Item,search->pName,search->pLength,search->pTime,1,search->wTime,H1);
								}
							}					    		
					    		search=search->next;
							}	
						for (i=0; i<MaxTrees; i++) {
			             		 p=H1->TheTrees[i];
						  countNode(p, r, 0); 
						}  
					    	countNodes=count;
							
						if(countNodes>=1){
							for (i=0; i<MaxTrees; i++) {
			             			p=H1->TheTrees[i];
						  	addWaitingTime(p, r, 0,1);   
						} 		
							}
					}
					 //if (IsEmpty( H1 )) printf("empty!");			
	}   
		
			printf("\nq = 1");
			printf("\nPID   WaitingTime");
			//fprintf(output,"\n%s","\nPID   WaitingTime");
			struct list* copyRoot2=copyRoot;
			struct list* copyAwt=awt;
			int totalwTime=0;
			while(copyRoot2!=NULL){
			//fprintf(output,"\n%s   %d",copyRoot2->pName,copyRoot2->wTime);
			printf("\n%s    %d",copyRoot2->pName,copyRoot2->wTime);
			totalwTime=totalwTime+copyRoot2->wTime;
			copyRoot2=copyRoot2->next;
			}
			//printf("**%.2f",(float)totalwTime);
			float number=(float)totalwTime/node;
			insertAwt(&awt,number);
			
 //**********************************************q=1***********************************************
						
			for(y=2; y<=10 ; y++){
				addSequence=0;
			//renovate the pLength for q=y; 
			
			linList=root;
			while(linList!=NULL){
				linList->pLength=linList->copyLength;
				//printf("\n%s %d %d ",linlist->pName,linlist->pLength,linlist->pTime);
				linList=linList->next;
					    	
			}
				copyRoot2=copyRoot;
				while(copyRoot2!=NULL){
				copyRoot2->wTime=0;
				copyRoot2->lTime=0;
				copyRoot2->firstEnter=0;
				//printf("\n%s   %d",copyRoot2->pName,copyRoot2->wTime);
				copyRoot2=copyRoot2->next;
				}
			
			struct list* copyRoot3=copyRoot;
				/*while(copyRoot3!=NULL){
				printf("\n%s   %d",copyRoot3->pName,copyRoot3->wTime);
				copyRoot3=copyRoot3->next;
				}*/
			
				/*while(root!=NULL){
				root->pLength=root->copyLength;
				printf("\n%s %d %d *",root->pName,root->pLength,root->pTime);
				root=root->next;
					    	
			}*/
					    
	     	printf("\n\nq = %d",y);
	     	//fprintf(output,"\nq = %d",y);
			//printf("\nTime Process in BH Priority value of processes in BH\n");
					    
			for(t=0; t<=totalTime ; t++){
			count=0;
			againList=root;
	//Insert the data in the linked list.
        	while(againList!= NULL) {
        	if(t==againList->pTime && againList->again !=y ){
        		        	
        		calculateFirstTime(againList->pLength);
        		againList->firstEnter=0;
		        Item=pValue;
        		againList->again=y;
        		Insert(Item,againList->pName,againList->pLength,againList->pTime,againList->firstEnter,againList->wTime,H1);	
	}
            againList = againList->next;
        }
			if(t==addSequence){
				   for (i=0; i<MaxTrees; i++) {
			              p=H1->TheTrees[i];
				   countNode(p, r, 0); 
			           	}  
					    countNodes=count;
					    //printf("***%d",countNodes);
					    
					    int late=0;
					    //If the binary heap is not empty
					    if(!IsEmpty(H1)){
					    /*	printf("\n %d	",addSequence);
					    	for (i=0; i<MaxTrees; i++) {
			             		p=H1->TheTrees[i];
						  		firstPrint(p, r, 0);   
						} 
							for (i=0; i<MaxTrees; i++) {
			             		p=H1->TheTrees[i];
						  		printResults(p, r, 0);   
						} */
						
						//Add passed time!
						for (i=0; i<MaxTrees; i++) {
			             		p=H1->TheTrees[i];
						lateTime(p, r, 0);   
						} 
					    	//Delete the min value.
					    	if (!IsEmpty( H1 )) Item=DeleteMin( H1 );
					    	
					    	linList=root;
					    						    	
					    		while(linList!=NULL){
					    		
					    		//If the process didn't complete,this code works
					    		if(strcmp(linList->pName,name)==0){
					    			
					    			if(linList->pLength<=y){
					    				late=linList->pLength;
					    				addSequence=addSequence + linList->pLength;
									}
					    			
					    			else {
					    			late=y;
					    			linList->pLength=linList->pLength-y;
					    			if(linList->pLength>0){
					    			calculate(findemax,linList->pLength);	
					    			Item=pValue;
					    			addSequence=addSequence + y;
								Insert(Item,linList->pName,linList->pLength,linList->pTime,1,linList->wTime,H1);			    			
									}	
								}
					    			
								}					    		
					    		linList=linList->next;
							}
			}
								//Add waiting time!
								if(countNodes>=2){
								for (i=0; i<MaxTrees; i++) {
			             		                p=H1->TheTrees[i];
						  		addWaitingTime(p, r, 0,late);   
						} 
						}
			}
		}
			printf("\nPID   WaitingTime");
			//fprintf(output,"\n%s","PID   WaitingTime");
			copyRoot3=copyRoot;
			totalwTime=0;
			while(copyRoot3!=NULL){
				//fprintf(output,"\n%s    %d",copyRoot3->pName,copyRoot3->wTime);
				printf("\n%s    %d",copyRoot3->pName,copyRoot3->wTime);
				totalwTime=totalwTime+copyRoot3->wTime;
				copyRoot3=copyRoot3->next;
				}
				
			//copyAwt->AWT=totalwTime/node;
			//copyAwt=copyAwt->next;
			//printf("%d ",totalwTime);
			//printf("**%.2f",(float)totalwTime/node);
			float number2 = (float)totalwTime/node;
			insertAwt(&awt,number2);
			}
		awtList=awt;
		int c=0;
		//*******************************AWT LIST******************************************
		printf("\n\nq		AWT\n");
		//fprintf(output,"\n\n%s","\n\nq		AWT\n");
		while(awtList!=NULL){
		   printf("\nq=%d		%.2f",++c,awtList->AWT);
		   //fprintf(output,"\nq=%d		%.2f",c,awtList->AWT);	
	           awtList=awtList->next;
		}
}
	fclose(output);
//********************************END***********************************************************
