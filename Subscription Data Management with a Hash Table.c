#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Ali  Özkoca
//2585271
#define MAX_NAME_LENGTH 100
#define MAX_SERVICE_NAME_LENGTH 50
#define MAX_COUNTRY_LENGTH 50

// DO NOT CHANGE THE DATA STRUCTURES

typedef struct {
    int subscriptionID;
    char serviceName[50];
    float serviceCharge;
    int devicesRegistered;
    char startDate[11];
    char endDate[11];
    char status[10];
    char country[MAX_COUNTRY_LENGTH];
} Subscription;


typedef struct {
    char name[MAX_NAME_LENGTH];
    int subscriptionCount;
    float subscriptionCostTotal;
    Subscription *subscriptions;
    int subscriptionCapacity;
} Customer;



//DO NOT CHANGE FUNCTION PROTOTYPES
void menu();
void printCustomers(Customer *customers, int no_of_customers);
int countCustomers(FILE *inFile);
void readSubscriptions(FILE *inFile, Customer *customers, int no_of_customers);
Customer* createHashTable(int hashTableSize);
Customer* addCustomer(Customer *hashTable, Customer addedCustomer, int *hashTableSize, int criteria);
Customer* rehash(Customer *hashTable, int *hashTableSize, int criteria);
void printTable(Customer *hashTable, int hashTableSize);
void searchTable(Customer *hashTable, int hashTableSize, char searchName[], int criteria);

//DO NOT CHANGE THE main FUNCTION
int main() {

    FILE *inFile;
    int no_of_customers = 0;
    Customer *customers;
    Customer *hashTable;

    inFile = fopen("subscriptions.txt", "r");
    if (inFile == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }
    no_of_customers = countCustomers(inFile);
    printf("There are %d unique customers\n", no_of_customers);

    customers = (Customer*) malloc(no_of_customers * sizeof(Customer));
    fclose(inFile);
    inFile = fopen("subscriptions.txt", "r");
    if (inFile == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }

    readSubscriptions(inFile, customers, no_of_customers);
    if (customers == NULL) {
        printf("\nCustomers have NOT been read successfully!\n");
        exit(1);
    }
    printCustomers(customers, no_of_customers);

    int hashTableSize = 11;
    char criteria;

    hashTable = createHashTable(hashTableSize);

    printf("Enter your hashing criteria: ");
    printf("1. Linear Probing 2. Quadratic Probing  3. Double Hashing\n");
    fflush(stdin);
    scanf("%c", &criteria);

    while (criteria != '1' && criteria != '2' && criteria != '3'){
        printf("Error! Please enter a valid hashing criteria: ");
        fflush(stdin);
        scanf("%c", &criteria);
    }
    fflush(stdin);

    int i;
    for (i = 0; i < no_of_customers; i++){
        hashTable = addCustomer(hashTable, customers[i], &hashTableSize, criteria - '0');
        printf("%s has been added to the table, the hash table now can be seen below:\n", customers[i].name);
        printTable(hashTable, hashTableSize);
        printf("\n");
    }

    char command = 0;
    int exit = 0;
    char searchName[81];
    while (exit != 1) {
        menu();
        printf("\nCommand: ");
        fflush(stdin);
        scanf("%c", &command);

        if (command == '1') {
            printf("Enter the customer's name: ");
            fflush(stdin);
            scanf("%s", searchName);
            searchTable(hashTable, hashTableSize, searchName, criteria - '0');
        }
        else if (command == '2'){
            printTable(hashTable, hashTableSize);
        }
        else if (command == '3'){
            exit = 1;
            printf("Goodbye!\n");
        }
        else{
            printf("Please enter a valid command!\n");
        }
    }


    free(customers);
    free(hashTable);

    return 0;
}

//DO NOT CHANGE THE menu FUNCTION
void menu () {
    printf("Please choose one of the following options:\n"
           "(1) Search a customer\n"
           "(2) Display hashtable\n"
           "(3) Exit\n");
}

//DO NOT CHANGE THE printCustomers FUNCTION
void printCustomers(Customer* customers, int no_of_customers) {
    printf("List of customers:\n");
    int i, j;
    for (i = 0; i < no_of_customers; ++i) {
        // Print customer details
        if (customers[i].subscriptionCount > 0) {
            printf("Name: %s, number of subscriptions = %d, total amount paid for subscriptions = %.2f, "
                   "average amount paid per subscription = %.2f\n",
                   customers[i].name, customers[i].subscriptionCount,
                   customers[i].subscriptionCostTotal, customers[i].subscriptionCostTotal / customers[i].subscriptionCount);
        } else {
            printf("Name: %s, number of subscriptions = %d, total amount paid for subscriptions = %.2f, "
                   "average amount paid per subscription = N/A\n",
                   customers[i].name, customers[i].subscriptionCount, customers[i].subscriptionCostTotal);
        }
    }
}

int countCustomers(FILE *inFile) {
    // WRITE YOUR CODE HERE
    int num_of_cust=0,empty;
    char *customerNames[100];
    for(int i=0;i<100;i++) {
        customerNames[i]=NULL;//making the all customer initaly null
    }
    int row=0;
    char c;
    while((c = fgetc(inFile))!=EOF) {
        if(c == '\n') // if the character is a new line, increase the row number
            row++;
    }
    fseek(inFile,0L,SEEK_SET);//after finding the number of the row go to the start of the file
    char currentcust[MAX_NAME_LENGTH];
    for(int i=0;i<row;i++){
        int ch;
        while ((ch = fgetc(inFile))!= EOF) {
            if (ch == '\n') {
                break;  // Exit loop once the first line is skipped
            }
        }
        fscanf(inFile,"%[^;]", currentcust);//reading first string which is name of customer
        int exists=0;
        for (int j =0;j<=num_of_cust;j++)//cheking the customer is unquie or already exist
        {
            if(customerNames[j]!=NULL &&strcmp(customerNames[j],currentcust)==0 ) {
                exists=1;
                break;
            }
        }
        if(exists==0) { // if the customer is unique adds to customer name array which is help us to follow unuqieness
            customerNames[num_of_cust] = malloc(strlen(currentcust) + 1);
            if (customerNames[num_of_cust] == NULL) {
                printf("Memory allocation error\n");
                exit(1);
            }
            strcpy(customerNames[num_of_cust],currentcust);
            num_of_cust++;
        }
    }

    for(int i =0;i<100;i++)//clearing the customer name array
        free(customerNames[i]);
    return num_of_cust;
}



void readSubscriptions(FILE* inFile, Customer* customers, int no_of_customers) {
    // WRITE YOUR CODE HERE
    int row=0;
    char name[MAX_NAME_LENGTH];
    int subscriptionID;
    char serviceName[50];
    float serviceCharge;
    int devicesRegistered;
    char startDate[11];
    char endDate[11];
    char status[10];
    char country[MAX_COUNTRY_LENGTH];
    int current=0;
    int ch;
    for(int k=0;k<no_of_customers;k++) {
        strcpy(customers[k].name,"xxx");//for making it initaly "xxx" which is mean in my code null
    }
    char c;
    while((c = fgetc(inFile))!=EOF) {
        if(c == '\n') // if the character is a new line, increase the row number
            row++;
    }
    fseek(inFile,0L,SEEK_SET);//after finding the number of row inFile goes to start of the file

    while ((ch = fgetc(inFile))!=EOF) {
        if (ch == '\n') {
            break;  // Exit loop once the first line is skipped
        }
    }
    if(customers!=NULL) {
        for(int i=0;i<row;i++) {
            fflush(stdin);
            int exists_index=0;
            fscanf(inFile, "%[^;];%d;%[^;];%f;%d;%[^;];%[^;];%[^;];%[^\n]%*c", name, &subscriptionID,
                   serviceName, &serviceCharge, &devicesRegistered, startDate, endDate, status, country);//reading each line of file
            int exists=0;
            for (int j =0;j<no_of_customers;j++) {//cheking the if customer already exist
                if(strcmp(name,customers[j].name)==0) {
                    exists=1;
                    exists_index=j;
                }
            }
            if(exists==0) {//if the customer is not already exixst we are adding the the customer and its subscription details
                customers[current].subscriptions = (Subscription *)malloc(sizeof(Subscription));
                strcpy(customers[current].name,name);
                customers[current].subscriptions[0].subscriptionID=subscriptionID;
                strcpy(customers[current].subscriptions[0].serviceName,serviceName);
                customers[current].subscriptions[0].serviceCharge=serviceCharge;
                customers[current].subscriptions[0].devicesRegistered=devicesRegistered;
                strcpy(customers[current].subscriptions[0].startDate,startDate);
                strcpy(customers[current].subscriptions[0].endDate,endDate);
                strcpy(customers[current].subscriptions[0].status,status);
                strcpy(customers[current].subscriptions[0].country,country);
                customers[current].subscriptionCount=1;
                customers[current].subscriptionCostTotal=serviceCharge;
                customers[current].subscriptionCapacity=customers[current].subscriptionCount;
                current=current+1;
            }
            else {//if customer already exists which means we are adding new subscription to that customer
                int count=customers[exists_index].subscriptionCount;
                Subscription* temp = realloc(customers[exists_index].subscriptions, sizeof(Subscription) * (count+1));//reallocating the subscription of the customer to add new subcription details
                if (temp == NULL) {
                    printf("Memory reallocation error");
                    exit(1);
                }
                customers[exists_index].subscriptions=temp;
                customers[exists_index].subscriptions[count].subscriptionID=subscriptionID;
                strcpy(customers[exists_index].subscriptions[count].serviceName,serviceName);
                customers[exists_index].subscriptions[count].serviceCharge=serviceCharge;
                customers[exists_index].subscriptions[count].devicesRegistered=devicesRegistered;
                strcpy(customers[exists_index].subscriptions[count].startDate,startDate);
                strcpy(customers[exists_index].subscriptions[count].endDate,endDate);
                strcpy(customers[exists_index].subscriptions[count].status,status);
                strcpy(customers[exists_index].subscriptions[count].country,country);
                customers[exists_index].subscriptionCount++;
                customers[exists_index].subscriptionCostTotal+=serviceCharge;
                customers[exists_index].subscriptionCapacity=customers[exists_index].subscriptionCount;
            }
        }
    }
}
Customer* createHashTable(int hashTableSize) {
    // WRITE YOUR CODE HERE
    Customer * hashTable= (Customer*)malloc(hashTableSize * sizeof(Customer));//creating new customer structure called hash table to implement Hashtable
    if(hashTable==NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    for(int i=0;i<hashTableSize;i++) {
        strcpy(hashTable[i].name,"NULL");//initializing to "NULL" helps to checking conditions in other functions
        hashTable[i].subscriptions=NULL;
        hashTable[i].subscriptionCapacity=-1;
        hashTable[i].subscriptionCount=-1;
        hashTable[i].subscriptionCostTotal=-1;
    }
    return hashTable;
}
Customer* addCustomer(Customer *hashTable, Customer addedCustomer, int *hashTableSize, int criteria) {
    // WRITE YOUR CODE HERE
    int added=-1;
    int key=0;
    for(int j=0;addedCustomer.name[j]!='\0';j++) {//finding key with help of XOR hashing
        key^=addedCustomer.name[j];
    }
    int pos= key%*hashTableSize;
    if(strcmp(hashTable[pos].name,"NULL")==0) { //if the first postion is empty add the customer to that position
        strcpy(hashTable[pos].name,addedCustomer.name);
        hashTable[pos].subscriptions=addedCustomer.subscriptions;
        hashTable[pos].subscriptionCapacity=addedCustomer.subscriptionCapacity;
        hashTable[pos].subscriptionCount=addedCustomer.subscriptionCount;
        hashTable[pos].subscriptionCostTotal=addedCustomer.subscriptionCostTotal;
        added=1;
    }
    if(strcmp(hashTable[pos].name,"NULL")!=0) {//if the first position is not empty finds the new position based on criteria
        int i =1;
        while(i<=*hashTableSize && added==-1) {
            if(criteria==1) {
                pos=(key%*hashTableSize+i)%*hashTableSize;
            }
            else if(criteria==2) {
                pos=((key%*hashTableSize)+(i*i))%*hashTableSize;
            }
            else if(criteria==3){
                pos=((key%*hashTableSize)+(i*(7-(key%7))))%*hashTableSize;
            }
            if(strcmp(hashTable[pos].name,"NULL")==0) {
                strcpy(hashTable[pos].name,addedCustomer.name);
                hashTable[pos].subscriptions=addedCustomer.subscriptions;
                hashTable[pos].subscriptionCapacity=addedCustomer.subscriptionCapacity;
                hashTable[pos].subscriptionCount=addedCustomer.subscriptionCount;
                hashTable[pos].subscriptionCostTotal=addedCustomer.subscriptionCostTotal;
                added=1;
            }
            i++;
        }
    }
    int n=0;
    for(int k=0;k<*hashTableSize;k++) {//finds the number of customer added to hashtable to find loadfactor
        if(strcmp(hashTable[k].name,"NULL")!=0) {
            n++;
        }
    }
    int size=*hashTableSize;
    float load_factor=(float)n/size;//finds load factor by #ofCustomer in hashtable/ hashtableSize
    if(added==1 && load_factor>0.5)
        hashTable=rehash(hashTable,hashTableSize,criteria);//if loadfactor is greater than 0.5 our hash table rehashed
    return hashTable;
}
Customer* rehash(Customer *hashTable, int *hashTableSize, int criteria) {
    // WRITE YOUR CODE HERE
    int firstsize=*hashTableSize;
    *hashTableSize=2*(*hashTableSize);//finds the new hashtable size and make it nearest prime value
    int prime;
    do {
        prime=1;
        for(int i=2;i*i<=*hashTableSize;i++) {
            if(*hashTableSize%i==0) {
                prime=0;
                *hashTableSize=*hashTableSize+1;
                break;
            }
        }
    }while(prime!=0);
    Customer * rehashTable=createHashTable(*hashTableSize);//creating new hash table with new size
    for (int i=0;i<firstsize;i++) {//for all customer added to old hashtable finding new position for new hashtable which is called rehashTable
        int key=0;                 // and adding to new hashtable
        int added=-1;
        for(int j=0;hashTable[i].name[j]!='\0';j++) {
            key^=hashTable[i].name[j];
        }
        int pos= key%*hashTableSize;
        if(strcmp(rehashTable[pos].name,"NULL")==0) {
            strcpy(rehashTable[pos].name,hashTable[i].name);
            rehashTable[pos].subscriptions=hashTable[i].subscriptions;
            rehashTable[pos].subscriptionCapacity=hashTable[i].subscriptionCapacity;
            rehashTable[pos].subscriptionCount=hashTable[i].subscriptionCount;
            rehashTable[pos].subscriptionCostTotal=hashTable[i].subscriptionCostTotal;
            added=1;
        }
        if(strcmp(rehashTable[pos].name,"NULL")!=0) {
            int k =1;
            while(k<=*hashTableSize && added==-1) {
                if(criteria==1) {
                    pos=((key%*hashTableSize)+k)%*hashTableSize;
                }
                else if(criteria==2) {
                    pos=((key%*hashTableSize)+(k*k))%*hashTableSize;
                }
                else if(criteria==3) {
                    pos=((key%*hashTableSize)+(k*(7-(key%7))))%*hashTableSize;
                }
                if(strcmp(rehashTable[pos].name,"NULL")==0) {
                    strcpy(rehashTable[pos].name,hashTable[i].name);
                    rehashTable[pos].subscriptions=hashTable[i].subscriptions;
                    rehashTable[pos].subscriptionCapacity=hashTable[i].subscriptionCapacity;
                    rehashTable[pos].subscriptionCount=hashTable[i].subscriptionCount;
                    rehashTable[pos].subscriptionCostTotal=hashTable[i].subscriptionCostTotal;
                    added=1;
                }
                k++;
            }
        }
    }
    return rehashTable;
}
void printTable(Customer *hashTable, int hashTableSize) {
    // WRITE YOUR CODE HERE
    printf("%-15s %-8s %-24s %-15s \n ","Index","Name","Total Subscriptions","TotalCost");
    for(int i=0;i<hashTableSize;i++) {
        if(strcmp(hashTable[i].name,"NULL")==0) {
            printf("%-2d \n",i);
        }else {
            printf("%-15d %-15s %-18d %-15.2f\n",i,hashTable[i].name,hashTable[i].subscriptionCount,hashTable[i].subscriptionCostTotal);
        }
    }
}
void searchTable(Customer *hashTable, int hashTableSize, char searchName[], int criteria) {
    // WRITE YOUR CODE HERE
    int found=-1;
    int key=0;
    for(int j=0;searchName[j]!='\0';j++) {
        key^=searchName[j];//finding key of the searchname by XOR hashing
    }
    int i=1;
    int pos=key%hashTableSize;
    if(strcmp(hashTable[pos].name,searchName)==0) {//cheking the first position should located
        found=1;//if its located that position
    }
    while (found==-1&&i<hashTableSize) {//cheking the other possible positions according to criteria
        if(criteria==1) {
            pos=((key%hashTableSize)+i)%hashTableSize;
        }
        else if(criteria==2) {
            pos=((key%hashTableSize)+(i*i))%hashTableSize;
        }
        else if(criteria==3) {
            pos=((key%hashTableSize)+(i*(7-(key%7))))%hashTableSize;
        }
        if(strcmp(hashTable[pos].name,searchName)==0) {
            found=1;
        }
        i++;
    }
    if(found==1) {//if its found printing the customer info
        printf("Customer Found: %s \n",hashTable[pos].name);
        printf("More information about customer:\n");
        printf("Number of subscriptions: %d \n",hashTable[pos].subscriptionCount);
        printf("Total Cost: %.2f \n\n",hashTable[pos].subscriptionCostTotal);
        printf("Subscriptions:\n");
        for(int k=0;k<hashTable[pos].subscriptionCount;k++) {
            printf("Subscription %d:\n",k+1);
            printf("Subscription ID: %d \n",hashTable[pos].subscriptions[k].subscriptionID);
            printf("Service Name: %s \n",hashTable[pos].subscriptions[k].serviceName);
            printf("Service Charge: %.2f \n",hashTable[pos].subscriptions[k].serviceCharge);
            printf("Devices Registered: %d \n",hashTable[pos].subscriptions[k].devicesRegistered);
            printf("Start Date: %s \n",hashTable[pos].subscriptions[k].startDate);
            printf("End Date: %s \n",hashTable[pos].subscriptions[k].endDate);
            printf("Status: %s \n\n",hashTable[pos].subscriptions[k].status);
        }
    }
    if(found==-1) {
        printf("Customer not found.\n\n");
    }
}
