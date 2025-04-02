#include <stdio.h>
#include "stdlib.h"
#include "string.h"
 // ALi Ozkoca 2585271

struct graphArc{
    int weight;
    struct graphVertex *destination;
    struct graphArc *next;
}Arc;


typedef struct graphVertex {
    struct graphVertex *next;
    char warehouseName[50];
    int inDegree;
    int outDegree;
    int processed;
    struct graphArc *firstArc;
} Vertex;


typedef struct graphHead {
    int count;
    struct graphVertex *first;
} Graph;

struct graphHead * createGraph(void);
void insertVertex(struct graphHead *head, char *data);
int insertArc(struct graphHead *head, char *fromKey, char *toKey ,int weight);
void printAllArcOfVertex(struct  graphVertex *graphVertexName);
void printAllVertex(struct graphHead *graphName);
void printAllVertexWithRoutes(struct graphHead *graphName);
void readRoutes(char *fileName,struct graphHead *warehouseGraph);
void readWarehouseNames(char *fileName, struct graphHead *warehouseGraph);
void getMostDeliveries(struct graphHead *warehouseGraph);
void sendMostDeliveries(struct graphHead *warehouseGraph);
void routesWithHighestDistance(struct graphHead *warehouseGraph);
void routesWithLowestDistance(struct graphHead *warehouseGraph);
int findPath(struct graphVertex *currentVertex, struct graphVertex *destinationVertex, int *totalDistance);
void checkDistance(struct graphHead *warehouseGraph, char *departure, char *destination);

int main (int argc, char *argv[]){
    struct graphHead *warehouseGraph = createGraph();
    readWarehouseNames("WarehouseLocations.txt", warehouseGraph);
    readRoutes("WarehouseRoutes.txt", warehouseGraph);

    printf("\nWarehouse and route data read successfully.\n");

    printf("\nRead warehouse locations:\n");
    printAllVertex(warehouseGraph);

    printf("\nRead routes:\n");
    printAllVertexWithRoutes(warehouseGraph);

    printf("\n");
    getMostDeliveries(warehouseGraph);

    printf("\n");
    sendMostDeliveries(warehouseGraph);

    printf("\n");
    routesWithHighestDistance(warehouseGraph);

    printf("\n");
    routesWithLowestDistance(warehouseGraph);

    printf("\n");
    if(argc > 1){
        checkDistance(warehouseGraph, argv[1], argv[2]);
    }
}

struct graphHead * createGraph(void){
    struct graphHead * head = (struct graphHead *)malloc(sizeof(struct graphHead));
    head->count = 0;
    head->first = NULL;
    return head;
}

void insertVertex(struct graphHead *head, char *data){
    struct graphVertex *vertex = (struct graphVertex *)malloc(sizeof(struct graphVertex));
    vertex->next = NULL;
    strcpy(vertex->warehouseName, data);
    vertex->inDegree = 0;
    vertex->outDegree = 0;
    vertex->firstArc = NULL;
    vertex->processed = 0;
    head->count += 1;
    if(head->first == NULL){
        head->first = vertex;
    }
    else{
        struct graphVertex *temp = head->first;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = vertex;
    }
}

int insertArc(struct graphHead *head, char *fromKey, char *toKey ,int weight){
    //To be completed
    Vertex * current=head->first;
    Vertex * fromvertex;//creating temporary structs
    Vertex * tovertex;
    while(current!=NULL) {//finding correct vertexs according to from key and to key
        if(strcmp(current->warehouseName,fromKey)==0) {
            fromvertex=current;
        }
        if(strcmp(current->warehouseName,toKey)==0) {
            tovertex=current;
        }
        current=current->next;
    }
    fromvertex->outDegree= fromvertex->outDegree+1;//adding one out degree to from warehouse
    tovertex->inDegree=tovertex->inDegree+1;//adding one in degree to destination warehouse
    struct graphArc* newarc = (struct graphArc *)malloc(sizeof(struct graphArc));
    if(newarc==NULL) {
        printf("Error In Allocation");
        exit(1);
    }
    newarc->destination=tovertex;//adding detail of the arc
    newarc->weight=weight;
    newarc->next=NULL;
    if(fromvertex->firstArc==NULL) // connecting arc to vertex list
        fromvertex->firstArc=newarc;
    else {
        struct graphArc* tmp=fromvertex->firstArc;
        while (tmp->next!=NULL) {
            tmp=tmp->next;
        }
        tmp->next=newarc;
    }
}
void printAllVertex(struct graphHead *graphName){
    //To be completed
    Vertex * tmp=graphName->first;
    while(tmp!=NULL) {
        printf(" %s\n",tmp->warehouseName);
        tmp=tmp->next;
    }
}
void printAllArcOfVertex(struct  graphVertex *graphVertexName){
    //To be completed
    struct graphArc * tmparc=graphVertexName->firstArc;
    printf("%s|",graphVertexName->warehouseName);
    while(tmparc->next!=NULL) {
        printf(" -%d-> %s|",tmparc->weight,tmparc->destination->warehouseName);
        tmparc=tmparc->next;
    }
    printf(" -%d-> %s|\n",tmparc->weight,tmparc->destination->warehouseName);//for the last one since loop finish before printing the last one
}

void printAllVertexWithRoutes(struct graphHead *graphName){
    //To be completed
    Vertex * tmpverx=graphName->first;
    while(tmpverx !=NULL) {
        if(tmpverx->firstArc!=NULL) {
            printAllArcOfVertex(tmpverx);
        }
        tmpverx=tmpverx->next;
    }
}
void readWarehouseNames(char *fileName, struct graphHead *warehouseGraph){
    //To be completed
    char c;
    int row=0;
    FILE * inFile;
    inFile=fopen(fileName,"r");
    if(inFile==NULL) {
        printf("Error While opening the file");
        exit(1);
    }
    printf("%s has been opened successfully\n",fileName);
    while((c = fgetc(inFile))!=EOF) {
        if(c == '\n') // if the character is a new line, increase the row number
            row++;
    }
    fseek(inFile,0L,SEEK_SET);//after finding the number of the row go to the start of the file
    char name[50];
    for(int i=0;i<=row;i++) {
        fscanf(inFile,"%s",name);
        insertVertex(warehouseGraph,name);
    }
}
void readRoutes(char *fileName,struct graphHead *warehouseGraph){
    //To be completed

    char from[50];
    char to[50];
    int distances;
    FILE * infile;
    infile= fopen(fileName,"r");//opening file
    if(infile==NULL) {
        printf("Error While opening the file");
        exit(1);
    }
    printf("%s has been opened successfully\n",fileName);
    char row[1024];
    while(fgets(row,sizeof(row),infile)){
        char *tok=strtok(row,";");//takes first string until; which is will be from warehouse
        if(tok==NULL)
            continue;
        strcpy(from,tok);//saving token to fromwarehouse name;
        int check=0;//creating condtitation
        while(check==0) {
            tok=strtok(NULL,";");//taking distance
            if(tok==NULL)
                check=1;
            distances=atoi(tok);//converting string to int since distance should be int
            tok=strtok(NULL,";");//taking to warehouse
            if(tok==NULL && check==1)
                check=1;
            if(check==0) {
                strcpy(to,tok);//saving to warehouse name
                int size=strlen(to);
                if(to[size-1]=='\n')//if the last char of the string newline char it chages to '\0' char
                    to[size-1]='\0';
                insertArc(warehouseGraph,from,to,distances);
            }
        }
    }
}
void getMostDeliveries(struct graphHead *warehouseGraph){
    //To be completed
    Vertex * tmpvertex=warehouseGraph->first;
    Vertex *printvertex=warehouseGraph->first;
    int most=0;
    while(tmpvertex!=NULL) {
        if(most<tmpvertex->inDegree) {
            most=tmpvertex->inDegree; //finding the most delivery number
        }
        tmpvertex=tmpvertex->next;
    }
    printf("Warehouses that receives deliveries from the most different locations (%d):\n",most);
    while (printvertex!=NULL) {
        if(printvertex->inDegree==most) { //according to most delivery number it print the name
            printf("- %s\n",printvertex->warehouseName);
        }
        printvertex=printvertex->next;
    }
}
void sendMostDeliveries(struct graphHead *warehouseGraph){
    //To be completed
    Vertex * tmpvertex=warehouseGraph->first;
    Vertex *printvertex=warehouseGraph->first;
    int most=0;
    while(tmpvertex!=NULL) {
        if(most<tmpvertex->outDegree) {
            most=tmpvertex->outDegree;//finding the most delivery number
        }
        tmpvertex=tmpvertex->next;
    }
    printf("Warehouses that sends deliveries to most different locations (%d):\n",most);
    while (printvertex!=NULL) {
        if(printvertex->outDegree==most) {
            printf("- %s\n",printvertex->warehouseName);//according to most delivery number it print the name
        }
        printvertex=printvertex->next;
    }
}
void routesWithHighestDistance(struct graphHead *warehouseGraph) {
    //To be completed
    Vertex*tmpvertex=warehouseGraph->first;
    Vertex*printvertex=warehouseGraph->first;
    int most=0;
    while (tmpvertex!=NULL) {
        struct graphArc * tmparc= tmpvertex->firstArc;
        while (tmparc!=NULL) {
            if(tmparc->weight>most) {
                most=tmparc->weight;  // finding the longest distance
            }
            tmparc=tmparc->next;
        }
        tmpvertex=tmpvertex->next;
    }
    printf("Routes with the highest distance (%d):\n",most);
    while (printvertex!=NULL) {
        struct graphArc * printarc= printvertex->firstArc;
        while (printarc!=NULL) {
            if(printarc->weight==most) { // according to longest distance printing the details
                printf("%s -%d-> %s\n",printvertex->warehouseName,printarc->weight,printarc->destination->warehouseName);
            }
            printarc=printarc->next;
        }
        printvertex=printvertex->next;
    }
}
void routesWithLowestDistance(struct graphHead *warehouseGraph) {
    //To be completed
    Vertex*tmpvertex=warehouseGraph->first;
    Vertex*printvertex=warehouseGraph->first;
    int least=99999999;
    while (tmpvertex!=NULL) {
        struct graphArc * tmparc= tmpvertex->firstArc;
        while (tmparc!=NULL) {
            if(tmparc->weight<least) {
                least=tmparc->weight; // find the least distance
            }
            tmparc=tmparc->next;
        }
        tmpvertex=tmpvertex->next;
    }
    printf("Routes with the smallest distance (%d):\n",least);
    while (printvertex!=NULL) {
        struct graphArc * printarc= printvertex->firstArc;
        while (printarc!=NULL) {
            if(printarc->weight==least) { // according to least distance printing the deatils
                printf("%s -%d-> %s\n",printvertex->warehouseName,printarc->weight,printarc->destination->warehouseName);
            }
            printarc=printarc->next;
        }
        printvertex=printvertex->next;
    }
}
int findPath(struct graphVertex *currentVertex, struct graphVertex *destinationVertex, int *totalDistance) {
    //To be completed
    //I used recursive depth first trevesal algorithm
    currentVertex->processed=1; // if this vertex visited changing the processed value which is initialy 0 from insertvertex function.
    struct graphArc * tmparc=currentVertex->firstArc;
    if(currentVertex==destinationVertex) {
        printf("%s ",destinationVertex->warehouseName);//when algoritm arrived to destination warehouse printing the name
        return 1;//mean path founded
    }
    while (tmparc!=NULL) {
        if(tmparc->destination->processed!=1) {//if algorithm did not already check this warehouse
            *totalDistance=*totalDistance+tmparc->weight; // adding arc lenght to total distance
            if(findPath(tmparc->destination,destinationVertex,totalDistance)==1) { //recursive calling
                printf("<-%d -%s ",tmparc->weight,currentVertex->warehouseName);
                return 1;//mean path founded
            }
            *totalDistance=*totalDistance-tmparc->weight;//taking back if there is not path for this arc
        }
        tmparc=tmparc->next;
    }
    return 0;//mean path can not founded
}
void checkDistance(struct graphHead *warehouseGraph, char *departure, char *destination) {
    //To be completed
    Vertex * current=warehouseGraph->first;
    Vertex * fromvertex;
    Vertex * tovertex;
    int distance=0;
    while(current!=NULL) {// if departure and destination exists it will assign to corresponding vertex
        if(strcmp(current->warehouseName,departure)==0) {
            fromvertex=current;
        }
        if(strcmp(current->warehouseName,destination)==0) {
            tovertex=current;
        }
        current=current->next;
    }
    if(fromvertex==NULL) {// if Departure vertex not founded it print error message and exit
        printf("Could not find the Departure Warehouse");
        exit(1);
    }
    if(tovertex==NULL) {// if Destination vertex not founded it print error message and exit
        printf("Could not find the Destination Warehouse");
        exit(1);
    }
    printf("Searching for a route from %s to %s...\n",departure,destination);
    int find=findPath(fromvertex,tovertex,&distance); //calling the findpath function which will return 0 or 1. Zero means path can not found
    if(find==1) {
        printf("\nTotal Distance : %d",distance);
    }else {//if path couldnot find will print this error.
        printf("Path could not find for Departure: %s Destination: %s",departure,destination);
    }
}