//         Ali Ozkoca
//           2585271
//       CNG-140 Section-3



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct signatures//define the structure
{
    char name[80];
    char surname[80];
    int x_initial;
    int x_final;
    int y_initial;
    int y_final;
    int width;
    int height;
};
int find_row(char filename[80])// finding the row number
{
    int row=0;
    FILE *infile;//creating the flow
    infile = fopen(filename, "r");//opening the file
    if(infile == NULL){
        printf("Could not open the file.");//if any mistake in opening file will pprint error message
        exit(1);
    }
    char c;
    while((c = fgetc(infile))!=EOF){
        if(c == '\n') // if the character is a new line, increase the row number
            row++;

    }
    fclose(infile);
    return row;
}
struct signatures* Load_SignaturesTable(char filename[80],int *row)
{
    int empty;
    fflush(stdin);//to clear memory for other times
    FILE *infile;//creating the flow
    infile = fopen(filename, "r");//opening the file
    while(infile==NULL) {//if user enter the wrong file name this loop will ask again
        infile = fopen(filename, "r");
        printf("This file does not exist. Please enter again:");
        gets(filename);

    }
    *row= find_row(filename);//calling the find_row
    struct signatures* table;
    int i;
    table=(struct signatures* ) malloc(sizeof (struct signatures) *(*row));// creating the table
    if(table==NULL)//if anything goes wrong while creating table
    {
        printf("Error in allocation");
        exit(1);
    }
    fflush(stdin);
    while(empty=fgetc(infile)!='\n'&& empty!=EOF);// for skip first line which include "fullname;x_initial;x_final;y_initial;y;final;". empty is int because fgetc()returns char as a int
    for(i = 0; i < *row; i++)//filling the table
    {
        fscanf(infile,"%s %[^;];%d;%d;%d;%d;",table[i].name,table[i].surname,&table[i].x_initial,&table[i].x_final,&table[i].y_initial,&table[i].y_final);//%[^;]help to read until ; for string
        table[i].height=table[i].y_final-table[i].y_initial;
        table[i].width=table[i].x_final-table[i].x_initial;
    }
    fclose(infile);
    return table;//returning table to main function
}
void Display_SignaturesTable(int row, struct signatures*signatures)//display the table
{
    int j;
    printf("\n");
    printf("Full_name \t       x_initial    x_final    y_initial    y_final     width      height\n");

    for(j=0;j<row;j++)
    {
            // %-13s \t and %-10d for print the table correct form
        printf("%s %-13s\t %-10d  %-10d  %-10d  %-10d  %-10d  %d\n",signatures[j].name,signatures[j].surname,signatures[j].x_initial,signatures[j].x_final,signatures[j].y_initial,signatures[j].y_final,signatures[j].width,signatures[j].height);

    }

}
int Search(int row , struct signatures* signatures ,char name[80])
{
    int i=0,j=0,result=-1;
    char *token, *token2  ;
    fflush(stdin);//clearing the memory
    token=strtok(name," ");//if user enter Efa Murillo for example we divide to two part Efa And Murillo
    token2=strtok(NULL," ");
    token[0]= toupper(token[0]);//first element of name Will be Upper case
    for (int k = 1; k < strlen(token) ; k++) {
        token[k]= tolower(token[k]);//other elements of name will be lowercase
    }
    if(token2==NULL)//if user enter only one name for example Efa
    {
        while(i<row)
        {
            if(!strcmp(signatures[i].name,token)|| !strcmp(signatures[i].surname, token))//cheking the input is exist or not check both name and surname
            {
                result=i;//if it is exist result will be i index
            }
            ++i;
        }
    }
    else // if user enter the two name for example Efa Murillo
    {
        token2[0]= toupper(token2[0]);//first element of surname will be uppercase
        for (int k = 1; k < strlen(token2) ; k++) {
            token2[k]= tolower(token2[k]);//other elements of surname will be lowercase
        }

        while (i < row) {
            if (!strcmp(signatures[i].name, token) && !strcmp(signatures[i].surname, token2)) //check name to name and surname to surname
            {
                result = i;
            }
            ++i;
        }
    }
    return result;
}
void sort(int row, struct signatures*signatures,char option) {
    int i,j;
    fflush(stdin);
    struct signatures tempr;
    if (option == 'h' || option == 'H') {// i use bubble sort algorithm  compares each pair of nearby items and switches them regularly as it moves through the list to be sorted.
        for (i = 0; i < row; ++i)
        {
            for(j=0;j<row-i-1;++j)
            {
                if (signatures[j].height < signatures[j + 1].height) {
                    tempr = signatures[j];
                    signatures[j] = signatures[j + 1];
                    signatures[j + 1] = tempr;
                }
            }

        }
    }
    if (option == 'w' || option == 'W') {
        for (i = 0; i < row; ++i)
        {
            for(j=0;j<row-i-1;++j)
            {
                if (signatures[j].width < signatures[j + 1].width) {
                    tempr = signatures[j];
                    signatures[j] = signatures[j + 1];
                    signatures[j + 1] = tempr;
                }
            }
        }
    }
}
int main(int argc,char *argv[]) {
    struct signatures* signatures;
    int error=1,row=0,j,choice,searchresult;
    char name[80],option;
    signatures=Load_SignaturesTable(argv[1],&row);// call the load_signatures function and signatures initilized
    Display_SignaturesTable(row,signatures);
    printf("\n\n");
    printf("To search for a signature, please press 1\n");
    printf("To sort signatures based on width or height, please press 2\n");
    printf("To exit, please press 3\n");
    printf("Your choice:");
    scanf("%d",&choice);
    fflush(stdin);
    while(choice!=3)// the loop until user choose 3
    {
        fflush(stdin);
        if(choice==1)
        {
            printf("\n");
            printf("Enter the name of the signature owner:");
            gets(name);
            searchresult=Search(row,signatures,name);// the search result equal to index of the user in the table
            if(searchresult==-1)
            {
                printf("That owner does not exist! Please try again!");
            }
            while(searchresult==-1)
            {

                printf("\n");
                printf("Enter the name of the signature owner:");
                gets(name);
                searchresult=Search(row,signatures,name);
                if(searchresult==-1)
                {
                    printf("That owner does not exist! Please try again!");
                }

            }
            printf(" %s %s start signing at x = %d and y = %d  and finalized at x = %d and y = %d. Hence, %s %s has a signature of width %d and height %d.",signatures[searchresult].name,signatures[searchresult].surname,signatures[searchresult].x_initial,signatures[searchresult].y_initial,signatures[searchresult].x_final,signatures[searchresult].y_final,signatures[searchresult].name,signatures[searchresult].surname,signatures[searchresult].width,signatures[searchresult].height);

        }
        if(choice==2)
        {
            fflush(stdin);
            printf("\n");
            printf("\nSort by (w: width, h: height):");
            scanf("%c",&option);
            sort(row,signatures,option);
            Display_SignaturesTable(row,signatures);
        }
        printf("\n\n");
        printf("To search for a signature, please press 1\n");
        printf("To sort signatures based on width or height, please press 2\n");
        printf("To exit, please press 3\n");
        printf("Your choice:");
        scanf("%d",&choice);
    }
    printf("BYEE");
    return 0;
}
