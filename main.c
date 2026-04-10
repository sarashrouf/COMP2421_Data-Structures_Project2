 /*sara shrouf
 1220481
 section 1*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

////////////////////////////////////////////////////////////
struct undostack{
struct undostack * next;
char addstr[100];
int index;
int status;

};
typedef struct undostack* ptr;
typedef struct undostack *StackToundo;
///////////////////////////////////////////////////////////////
 typedef struct Node  *queueptr;
typedef struct Node{

queueptr next;
char data[100] ;


} Node;
////////////////////////////////////////////////////////////////////
typedef struct Queue {
    queueptr front;  //<-- it will point to the first node(head) of the linkedList.
     queueptr rear;  //<-- it will point to the last node(tail) of the linkedList.
}Queue;
///////************************************************************////////////////////////
//isRead is used to check if the input file has been read or not
int isRead=0;
//////**************************************************************///////////////////////


///////////////////////////////// FUNCTIONS IN MY PROJECT  /////////////////////////////////////////
void readInputFile();
Queue * createQueue();
char * deQueue(Queue* q);
void inserQueau(Queue *q,char *text);
void insertoText(Queue *q,StackToundo s,char*array,int index);
int  deleteFromText(char *array,char *word);
void enQueue(Queue* q, char *data);
char * deQueue(Queue* q);
void printQueue(Queue *q);
StackToundo createStack();
void push (StackToundo s ,char * data,int status,int index);
 void pop(StackToundo s);
char * top (StackToundo s);
void undoOP(StackToundo s,StackToundo s2,char *array);
void redoOP(StackToundo s,StackToundo s2,char *array);
void printUndoRedoStack(StackToundo s,StackToundo s2);
 void saveToOutputFile() ;
 /////////////////////////////////////////////////////////////////////////////////////////////////////
 char initialAray[1000];
 char copyarray[1000];
Queue *q;
StackToundo s;
StackToundo s2;
StackToundo s3;

int main(){

q=createQueue();
 s=createStack();
 s2=createStack();
 s3=createStack();
char text[100];//The word I will add
char word [100];//the word i will delete
//////////////////////////////
  displayMenu();
    int operation;
    scanf("%d",&operation);
    while(1)
    {
        while (operation < 1 || operation > 9) // to test if the operation valid or not
        {
            printf("\n This option is not valid. please choose number  between 1-7 ");
            displayMenu();
            scanf("%d",&operation);
        }
        switch(operation){
  case 1:
       if (isRead==1){

                printf("THE INPUT FILE HAS BEEN READ ALREADY!\n\nPLEASE CHOOSE ANOTHER OPERATION TO EXECUTE.\n\n");
                printf("---------------------------------------------------------------------------\n\n");

                break;
            }
             readInputFile();/*to read the input file*/
                    printf("\n Reading process was successful. ");
                    isRead=1;
                    break;


  case 2: if(isRead==0){ /*to check if the input file has been read*/

                printf("THE INPUT FILE HAS NOT BEEN READ YET.\n\nPLEASE CHOOSE TO READ FILE FIRST.\n");
                printf("\n---------------------------------------------------------------------------\n\n");

                break;
            }
            printf("%s\n",initialAray);




    break;

   case 3 : if(isRead==0){
       printf("THE INPUT FILE HAS NOT BEEN READ YET.\n\nPLEASE CHOOSE TO READ FILE FIRST.\n");
                printf("\n---------------------------------------------------------------------------\n\n");

                break;
            }
            int k;
           printf("Enter a string: ");
                getchar();// consume newline character left in buffer
                scanf(" %99[^\n]", text);//write a text
         printf("Enter the index:   (-1) to add to the last ");
           scanf("%d",&k);

          inserQueau(q,text);//add text  to Queue
      insertoText(q,s,copyarray,k);//insert frome   Queue to the array and stack
     printf("%s",copyarray);


break;
   case 4: if(isRead==0){
       printf("THE INPUT FILE HAS NOT BEEN READ YET.\n\nPLEASE CHOOSE TO READ FILE FIRST.\n");
                printf("\n---------------------------------------------------------------------------\n\n");}
                 printf("Enter the sentence you want to delete");
                getchar();// consume newline character left in buffer
                scanf(" %99[^\n]", word);//write a text



               int Index=  deleteFromText(copyarray,word);
               if(Index==-1){
                printf("The word you want to delete does not exist");
               }

              else {
              printf("%s",copyarray);
              }



    break;


   case 5:  if(isRead==0){
       printf("THE INPUT FILE HAS NOT BEEN READ YET.\n\nPLEASE CHOOSE TO READ FILE FIRST.\n");
                printf("\n---------------------------------------------------------------------------\n\n");

                break;
            }
     undoOP(s,s2,copyarray);

break;

case 6:if(isRead==0){
       printf("THE INPUT FILE HAS NOT BEEN READ YET.\n\nPLEASE CHOOSE TO READ FILE FIRST.\n");
                printf("\n---------------------------------------------------------------------------\n\n");

                break;
            }
            redoOP(s,s2,copyarray);
            break;

case 7:
    if(isRead==0){
       printf("THE INPUT FILE HAS NOT BEEN READ YET.\n\nPLEASE CHOOSE TO READ FILE FIRST.\n");
                printf("\n---------------------------------------------------------------------------\n\n");

                break;
            }


    printUndoRedoStack(s,s2);
     break;
case 8:

    saveToOutputFile();
     if(isRead==0){
       printf("THE INPUT FILE HAS NOT BEEN READ YET.\n\nPLEASE CHOOSE TO READ FILE FIRST.\n");
                printf("\n---------------------------------------------------------------------------\n\n");

                break;
case(9):
   printf("THANK YOU FOR CHOOSING MY PROGRAM.. EXITING PROGRAM..\n");
            printf("\n---------------------------------------------------------------------------\n\n");

            return 0;

        break;

            }

        }
          displayMenu();
              scanf("%d",&operation);
    }
}




/*to display main menu*/
   void displayMenu()
    {
        printf("\n\n Select the number of option you want to do.");
        printf("\n\n 1- Load the input file which contains the initial text.");
        printf("\n 2-Print the loaded text.");
        printf("\n 3-Insert strings to the text ");
        printf("\n 4-Remove strings from the text. ");
        printf("\n 5- Perform Undo operation .");
        printf("\n 6-Perform Redo operation");
        printf("\n 7-Print the Undo Stack and the Redo stack ");
        printf("\n 8-Save the updated text to the output file");
        printf("\n 9- Exit");
        printf("\n");
    }

//function to insert the word that add by user to Queue
void inserQueau(Queue *q,char *text){


char *word=strtok(text," ");
while(word!=NULL){
    enQueue(q,word);
    word = strtok(NULL," ");}

}
//function to insert to the array and puch to stack frome Queue
void insertoText(Queue *q,StackToundo s,char*array,int index){
    int length=strlen(array);
     Node* temp = q->front;

    if(index==-1){//to add in the last of string

    while(temp!=NULL){
char*t1= deQueue(q);
strcat(array," ");
strcat(array,t1);
 push(s,t1,1,index);
temp=temp->next;

}
    }
    else{//if add at specific index
       while(temp!=NULL){
       char *t2=deQueue(q);

        //move the index
        for(int i=length;i>=index;i--){
            array[i+strlen(t2)]=array[i];
        }
              strncpy(&array[index],t2,strlen(t2));
        array[index+strlen(t2)]=' ';//insert the text frome Queue
        //add space
        index+=strlen(t2)+1;//move the index*/
        push(s,t2,1,index);

        temp=temp->next;
       }



    }
}
//function to delete from string and return the index of deleted word
int  deleteFromText(char *array,char *word){

int lenword=strlen(word);//length of the word
int len=strlen(array) ;//length of the array
//int i,j;
if (lenword == 1) {
        for (int i = 0; i < len; i++) {
            if (array[i] == word[0]) {
                // Shift elements to the left
                for (int j = i; j < len - 1; j++) {
                    array[j] = array[j + 1];
                }
                len--;
                array[len] = '\0';
                push(s,word,0,i++);
                return i++;
            }
        }
        printf("'%c' not found in the list.\n", word[0]);
    } else {
 char *find=strstr(array,word);//find the pos to the word in array
 int pos=find-array;//find the index of word in array
 if(find!=NULL){

    int length=strlen(find+lenword);//the length of array after remove thw word
    //shift the array
    for(int i=0;i<=length;i++){
        array[pos+i]=array[pos+lenword+i];
    }
   push(s,word,0,pos+1);
    return pos;//the index of the deleted word

 }
    }

return -1;



}
/////////////////////////////////////      👇🏽       Queue  FUNCTION   👇🏽                 ///////////////////////////////////////////////////////////

// this function will create a new linked lidt node and store the dat in it :
 Node* newNode(char * data) {

    Node* temp = (struct Node*)malloc(sizeof(struct Node)); //<-- will search for empty space in memo.

    // handle if there any issue in the  allocating memory:
    if (temp == NULL) {
        printf("Memory overflow. Could not allocate memory.\n");
        exit(0);
    }
    strcpy(temp->data,data);       //<-- insert the data in the node.
    temp->next = NULL;   //<-- set the pointer.
    return temp;
}
//this function will create a  Queue Node:
 Queue * createQueue() {

 struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    // handle if there any issue in the  allocating memory:
    if (q == NULL) {
        printf("Memory overflow. Could not allocate memory.\n");
        exit(0);
    }
    q->front = q->rear = NULL;
    return q;
}
//function to add to the queue
void enQueue(Queue* q, char *data) {

    // create a new linkedlist node with the inserted element(K):
     Node* temp = newNode(data);

    // if queue is empty then -> new node will be the front & rear both(the only emelent in the queue):
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    // if the queue is NOT empty then -> add the new node at the end of queue and change the rear:
    q->rear->next = temp;
    q->rear = temp;  //<-- make the last inserted  element  the rear.
}

// this function will remove a key from the front of the given queue:
char * deQueue(Queue* q) {

    // if queue is empty -> return NULL(nothing to remove)
    if (q->front == NULL){
       return;
    }

    // store previous front and move front one node ahead.
     Node* temp = q->front;
     q->front = q->front->next;

    // if front becomes NULL then -> change rear also to NULL.
    if (q->front == NULL){
       q->rear = NULL;
    }

    //printf("element { %d }  removed \n", temp->data);
 return temp->data;
    free(temp); //<-- free the node.

}
//function to print queue **not use in my project just To check my project**//
void printQueue(Queue* q){

    if(q==NULL){
        printf("Queue Not Found..\n");
        return;
    }
    Node *temp=q->front;

    printf("Queue->\t  ");
    while(temp!= NULL){
        printf("%s\t",temp->data );
       temp=temp->next;

    }
    printf("\n");
}
/////////////////////////////////////      👇🏽       STACK FUNCTION   👇🏽                 ///////////////////////////////////////////////////////////
StackToundo createStack()
 {
     StackToundo s = (StackToundo)malloc(sizeof(struct undostack));
     if(s==NULL)
     {
         printf("\n Out of space");
     }
     else
       s->next=NULL;
     return s ;
 }
 int isEmpty(StackToundo s)
 {
     return (s->next==NULL);
 }

/*to push a new  char element to the top of the stack*/
 void push (StackToundo s ,char * data,int status,int index)
 {
     if(s!=NULL)
     {
        StackToundo  newstack = (StackToundo)malloc(sizeof(struct undostack));
         if (newstack==NULL) // to check if the new node is null or not
         {
             printf("\n Out of space");
             return;
         }
         else
         {
            strcpy(newstack->addstr,data);
            newstack->index=index;
           newstack->status=status;

            newstack->next= s->next;
            s->next = newstack;
         }
     }
   }


    /*to remove the top char element of the stack */
    void pop(StackToundo s)
    {

        if(isEmpty(s)==1)
        {
            printf("\n Empty stack.you can not delete an empty stack");
        }
        else {
            ptr temp = s->next;
            s->next=temp->next;
            free(temp);
        }
    }
//function to return the top of stack
char * top (StackToundo s)
  {
      if(!isEmpty(s))
      {
          return s->next->addstr;
      }
      else
        printf("\n empty stack");
      return '\0' ;
  }


/*to read input data file*/
void readInputFile(){

    FILE* input; // pointer to input file
    char fileName[100]; // string to store file name
    printf("\n please enter input file name: \n ");
     scanf("%s",fileName);
     input= fopen(fileName,"r");

     while(input==NULL) /*to check if the file does not exist*/
     {
        printf("\n Failed to open file. This File does not exist.");
        printf("\n please enter an exist file name:\n ");
        scanf("%s",fileName);
        input= fopen(fileName,"r");

     }
     fgets(initialAray,sizeof(initialAray),input);
     strcpy(copyarray,initialAray);/*reading line (inital text ) and store it in array .*/
     fclose(input);
}

/* Function to make the UNDO operation */

void undoOP(StackToundo s,StackToundo s2,char *array){

    if (isEmpty(s)){

    printf("the stack is Null");

    }

 else if(s->next->status==1){//if the last operation it was an addition we remove it
char *p=s->next->addstr;
   int lenword=strlen(p);//length of the word
 char *find=strstr(array,p);
 int pos=find-array;
 int length=strlen(find+lenword);
 if(find!=NULL){//shift element
    for(int i=0;i<=length;i++){
        array[pos+i]=array[pos+lenword+i];
    }
   push(s2,p,1,s->next->index);//push to redo stack
   pop(s);//delete from undo stack

 }}

else   if (s->next->status==0){//if the last operation it was an remove we add it
    push(s2,s->next->addstr,0,s->next->index);//push to redo stack
    int arrayln=strlen(array);
    int index=(s->next->index)-1;
    int wordln=strlen(s->next->addstr);
    for(int i=arrayln;i>=index;i--){
        array[i+wordln]=array[i];
    }
    for(int i=0;i<wordln;i++){
        array[index+i]=s->next->addstr[i];
    }

pop(s);//delete from undo stack
}

  printf("%s",array);



}
/* Function tomake REDO operation */
void redoOP(StackToundo s,StackToundo s2,char *array){

 if(isEmpty(s2)){

    printf("the stack is Null");
    }

if (s2->next->status==1){
    push(s,s2->next->addstr,1,s2->next->index);//push to undo stack
    int arrayln=strlen(array);
    int index=s2->next->index;
    if(index==-1){
strcat(array," ");
strcat(array,s2->next->addstr);


}

    else{
    int wordln=strlen(s2->next->addstr);
    for(int i=arrayln;i>=index;i--){
        array[i+wordln]=array[i];
    }
    for(int i=0;i<wordln;i++){
        array[index+i]=s2->next->addstr[i];
    }

;}
pop(s2);//delete frome redo stack
}

else if(s2->next->status==0){
char *p=s2->next->addstr;
   int lenword=strlen(p);//length of the word
 char *find=strstr(array,p);
 int pos=find-array;
 if(find!=NULL){

    int length=strlen(find+lenword);
    for(int i=0;i<=length;i++){
        array[pos+i]=array[pos+lenword+i];
    }
   push(s,p,1,pos+1);//add to undo stack
   pop(s2);//delete from redo stack

 }}
 printf("%s",array);


}
/* print to undo stack and redo stack*/
void printUndoRedoStack(StackToundo s,StackToundo s2){

if(isEmpty(s)){

    printf("stack is empty ,There is nothing to print");
}
else{
    printf("\t\t\t---------UNDOSTACK--------\t\t\t\n");
     ptr temp2=s->next;
        while(temp2!=NULL){
              push(s3,temp2->addstr,temp2->status,temp2->index);
                if(s3->next->status==1){
                printf("%s\t\t\t%d\t\t\t%s\n",s3->next->addstr,s3->next->index,"INSERT");}
                else{
                     printf("%s\t\t\t%d\t\t\t%s\n",s3->next->addstr,s3->next->index,"Delete");}

   //top = s->next->addstr;

           ptr temp = s3->next;
            s3->next=temp->next;
            temp2=temp2->next;
            free(temp);
            //pop


        }


}
printf("\n\n");

 if(isEmpty(s2)){

    printf("stack is empty ,There is nothing to print");
}
else{
        printf("\t\t\t---------REDOSTAKC-------\t\t\t\n");
         ptr temp2=s2->next;
        while(temp2!=NULL){
 push(s3,temp2->addstr,temp2->status,temp2->index);
                if(s3->next->status==1){
                printf("%s\t\t\t%d\t\t\t%s\n",s3->next->addstr,s3->next->index,"INSERT");}
                else{
                printf("%s\t\t\t%d\t\t\t%s\n",s3->next->addstr,s3->next->index,"Delete");}

   //top = s->next->addstr;
            ptr temp = s3->next;
            s3->next=temp->next;
            temp2=temp2->next;
           free(temp);
        }



}

}
// Function to save to output file
    void saveToOutputFile() {
        FILE* output;
        output = fopen("output2.txt", "w");
        if (output == NULL) {
            printf("Failed to create output file.\n");
            return;
        }

        strcpy(initialAray,copyarray);

            fclose(output);
        }







