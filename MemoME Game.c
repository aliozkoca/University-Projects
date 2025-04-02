// ALI OZKOCA
//  2585271
// CNG 140 Section-3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int board_size()
{
    int size,sizeerror1=0;
    while(sizeerror1==0)//if user enter wrong value size of board it will repeat
    {
        printf("Please specify the board size (2-30):");
        scanf("%d",&size);
        if(size<2||size>30)
        {
            printf("Board size can only be between 2-30!\n");
            sizeerror1=0;// repeat the take input because user enter wrong value
        }
        else if(size%2!=0)
        {
            printf("Board size can only be a multiple of two!\n");
            sizeerror1=0;// repeat the take input because user enter wrong value
        }
        else
        {
            sizeerror1=1;
        }
    }
    printf("A Board is created for you with the size of %d x %d !\n",size,size);
    return size;// it will send the size to main function
}
int initializeBoard(char **arry,int size)//fill the real board which is user can not see
{
    int i,j,k,l;
    char **chaarry = (char **) malloc(size * sizeof(char*));// create another array for make all symbols used same amount
    if(chaarry==NULL)
    {
        printf("Error in allocation");
        exit(1);
    }
    for(i=0;i<size;++i)
    {
        chaarry[i] = (char *) malloc(size * sizeof(char));
        if(chaarry[i]==NULL)
        {
            printf("Error in allocation");
            exit(1);
        }
    }
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;++j)
        {
            chaarry[i][j]=33+i;// initialize the char array with ascii number of ! to ascii number of (!+size)

        }
    }

    for(i=0;i<size;++i)
    {
        for(j=0;j<size;++j)
        {
            do
            {
                k=rand()%size;//we choose random point to initialize array
                l=rand()%size;

            }while(chaarry[k][l]==0);//check char array[k][l] have symbol or not
            arry[i][j]=chaarry[k][l];//we initialize array with symbols
            chaarry[k][l]=0;// change the symbol with another value for do not use again
        }
    }
}
int check(int row1, int row2, int column1, int column2, int size, char **arry)
{
    if(arry[row1-1][column1-1]==arry[row2-1][column2-1])//this is check two elements of real board they are equal or not for example arry[1][2] and arry[2][4]
        return 1;
    else
        return 0;
}

void displayBoard(char **arry2,int size)// this function will display the second board which filled with "@" and users can see
{
    int i,j;
    printf("\n");
    printf("   ");// to help us to right print of coordinate system
    for(i=0;i<size;++i)
    {
        printf("%3.d",i+1);//%3.d to create space between each prints also this print print 1 to size to create coordinate system
    }
    for(i=0;i<size;++i)
    {
        printf("\n%3.d",i+1);//%3.d to create space between each prints also this print print 1 to size to create coordinate system
        for(j=0;j<size;++j)
        {
            printf("%3.c",arry2[i][j]);//%3.c to create space between each prints
        }
    }
}
int get_cord(char **arry2, int size,char **arry) {
    int  errors = 89,retrn,score, row1, row2, colm1, colm2;
    fflush(stdin);
    displayBoard(arry2,size);// call the function to show the board
    while (errors == 89)
    {
        printf("\nEnter the coordinates of doors to open:");
        fflush(stdin);
        scanf("(%d,%d) (%d,%d)",&row1,&colm1,&row2,&colm2);// take the coordinates
        if ((row1 == row2) && (colm1 == colm2))// check the inputs are they same or not
        {

            printf("Sorry, two door coordinates are same!");
            errors = 89;// this variable keep in the loop becasue input not correct
        }
        else if ((row1 > size) || (row2 > size) || (colm1 > size) || (colm2 > size))// check wrong coordinates
        {
            printf("Sorry, wrong coordinates!");
            errors = 89;// this variable keep in the loop becasue input not correct
        }
        else if(arry2[row1-1][colm1-1]!='@')//check the door opened before or not
        {
            errors = 89;// this variable keep in the loop becasue input not correct
            printf("(%d,%d) already opened!",row1,colm1);
        }
        else if(arry2[row2-1][colm2-1]!='@')//check the door opened before or not
        {
            errors = 89;// this variable keep in the loop becasue input not correct
            printf("(%d,%d) already opened!",row2,colm2);
        }
        else
            errors=98;// this variable end the loop becasue inputs are correct
    }
    retrn=check(row1,row2,colm1,colm2,size,arry);// call the checkchars  function
    arry2[row1-1][colm1-1]=arry[row1-1][colm1-1];// change the arry2 to print user opened which door
    arry2[row2-1][colm2-1]=arry[row2-1][colm2-1];// change the arry2 to print user opened which door
    displayBoard(arry2,size);
    if(retrn==1)
    {
        score=2;
    }
    else
    {
        arry2[row1-1][colm1-1]='@';// if user doors not same its make it previous version
        arry2[row2-1][colm2-1]='@';
        score=-1;
    }
    return score;//return score to main
}
int main() {
    int size,row,collum,i,j,score1=0,totalscoree1=0,fin=1,score2=0,totalscoree2=0;
    char conti='Y';
    fflush(stdin);
    srand(time(NULL));
    while(conti=='Y'||conti=='y') //repeat the game if user want
    {
        totalscoree1 = 0;//when the game repeated scores will 0
        totalscoree2 = 0;

        printf("Welcome to MemoMe!\n");
        size = board_size();// call the board_size function

        char **arry = (char **) malloc(size * sizeof(char *));//creating the real board which user can not see
        if(arry == NULL)
        {
            printf("Error in allocation");
            exit(1);
        }
        for (i = 0; i < size; ++i)
        {
            arry[i] = (char *) malloc(size * sizeof(char));
            if (arry[i] == NULL)
            {
                printf("Error in allocation");
                exit(1);
            }
        }

        char **arry2 = (char **) malloc(size * sizeof(char *));// creating the second board which user can see
        if(arry2 == NULL)
        {
            printf("Error in allocation");
            exit(1);
        }
        for (i = 0; i < size; ++i)
        {
            arry2[i] = (char *) malloc(size * sizeof(char));
            if (arry[i] == NULL)
            {
                printf("Error in allocation");
                exit(1);
            }
        }

        for (i = 0; i < size; ++i)// making all elements "@"in second board
        {
            for (j = 0; j < size; ++j)
                arry2[i][j] = '@';
        }
        initializeBoard(arry, size);// call the initializeBoard function
        fflush(stdin);
        while (fin == 1)//this is run until game finish
        {
            printf("\n");
            printf("\n--Player 1 turn--");
            score1 = get_cord(arry2, size, arry);//for player one call the get_cord function
            totalscoree1 += score1;
            if (score1 == 2) {
                printf("\n\nLucky you! Your score: %d total score:%d", score1, totalscoree1);
            } else {
                printf("\n\nUnlucky! Your score: %d, total score: %d", score1, totalscoree1);
            }
            printf("\n\n");
            printf("\n--Player 2 turn--");
            score2 = get_cord(arry2, size, arry);//for player two call the get_cord function
            totalscoree2 += score2;
            if (score2 == 2)
            {
                printf("\nLucky you! Your score: %d total score:%d", score2, totalscoree2);
            } else
            {
                printf("\n\nUnlucky! Your score: %d, total score: %d", score2, totalscoree2);
            }
            for (i = 0; i < size; ++i) {
                for (j = 0; j < size; ++j) {
                    if (arry2[i][j] != '@')// to check all the doors opened or not
                        fin = 0;
                    else
                        fin = 1;
                }
            }
        }
        if(totalscoree1>totalscoree2)
            printf("\n***Winner is Player 1!***");
        if(totalscoree2>totalscoree1)
            printf("\n***Winner is Player 2!***");
        if(totalscoree1==totalscoree2)
            printf("\nDraw");// asume the draw
        printf("\nWould you like to play again (Y/N)? ");
        scanf(" %c",&conti);
        if(conti=='N'||conti=='n')
            printf("\nBYEE!!");
    }
    return 0;
}
