//            Ali Ozkoca
//            2585271
//            CNG-140 Section-3
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rolldice()
{
    int dice;// function for create random number between 1 and 6
    dice=1+rand()%6;
    return dice;
}
int playcomp()// function makes the computer play the game.
{
    int score,dice1,dice2,dice3,dice4,dice5,error1=2,error2=2,error3=2,error4=2,error5=2,totalscore=0,check,exctcheck1=6,exctcheck2=6,exctcheck3=6,exctcheck4=6,exctcheck5=6;
    printf("I got --->");
    dice1=rolldice();
    dice2=rolldice();
    dice3=rolldice();
    dice4=rolldice();
    dice5=rolldice();
    if(dice1==2||dice1==5||dice2==2||dice2==5||dice3==2||dice3==5||dice4==2||dice4==5||dice5==2||dice5==5)
        score=0;// if any dice is 2 or 5 it makes the score 0
    else
        score=dice1+dice2+dice3+dice4+dice5;

    if(dice1==2||dice1==5)
    {
        error1 = 3;// variable for to get out of the while loop when all the dice are 2 or 5
        exctcheck1=5; // variable for to be able to print that this dice is removed when it is 2 or 5

    }
    if(dice2==2||dice2==5)
    {
        error2 = 3;// variable for to get out of the while loop when all the dice are 2 or 5
        exctcheck2=5;// variable for to be able to print that this dice is removed when it is 2 or 5
    }
    if(dice3==2||dice3==5)
    {
        error3 = 3;// variable for to get out of the while loop when all the dice are 2 or 5
        exctcheck3=5;// variable for to be able to print that this dice is removed when it is 2 or 5
    }
    if(dice4==2||dice4==5)
    {
        error4 = 3;// variable for to get out of the while loop when all the dice are 2 or 5
        exctcheck4=5;// variable for to be able to print that this dice is removed when it is 2 or 5
    }
    if(dice5==2||dice5==5)
    {
        error5 = 3;// variable for to get out of the while loop when all the dice are 2 or 5
        exctcheck5=5;// variable for to be able to print that this dice is removed when it is 2 or 5
    }
    printf("[Dice 1 ]: %d [Dice 2 ]: %d [Dice 3 ]: %d [Dice 4 ]: %d [Dice 5 ]: %d \n",dice1,dice2,dice3,dice4,dice5);

    while(exctcheck5==5||exctcheck4==5||exctcheck3==5||exctcheck2==5||exctcheck1==5)// to check any of dices 2 or 5
    {
        printf("\n");
        if (exctcheck1 == 5)//To be able to print that this dice is removed when it is 2 or 5
            printf("[Dice 1] ");
        if (exctcheck2 == 5)
            printf("[Dice 2] ");
        if (exctcheck3 == 5)
            printf("[Dice 3] ");
        if (exctcheck4 == 5)
            printf("[Dice 4] ");
        if (exctcheck5 == 5)
            printf("[Dice 5] ");
        printf("are excluded ");
        exctcheck1=6,exctcheck2=6,exctcheck3=6,exctcheck4=6,exctcheck5=6;// change the value of the variable to print only once that the dice were removed


    }


    printf("\nmy score %d ",score); //to show the scores when each series of dice is rolled
    totalscore+=score;
    printf(" my  total score %d\n",totalscore);


    while(error1==2||error2==2||error3==2||error4==2||error5==2)// to finish the function when all dice 2 or 5
    {
        score=0;
        check=1;

        printf("\n");
        printf("I got --->  ");




        if ((dice1 != 2 && dice1 != 5)&&error1==2) // if 2 or 5 rolls, this dice will not be used again in this round
        {
            dice1 = rolldice();

            printf(" [Dice 1]: %d",dice1);
            if(dice1==2||dice1==5)
            {
                score=0;// when dice 2 or 5 score will be 0
                error1 = 3; // variable for to get out of the while loop when all the dice are 2 or 5
                check=0; // help to keep  score 0 when we roll other dice
                exctcheck1=5; // variable for to be able to print that this dice is removed when it is 2 or 5

            }
            else
            {
                score+=dice1; // to store score
                error1 = 2;// to stay in while loop
                check=1;// for be able to add dices
            }

        }

        if ((dice2 != 2 && dice2 != 5) && error2==2)// if 2 or 5 rolls, this dice will not be used again in this round
        {
            dice2 = rolldice();
            printf(" [Dice 2]: %d",dice2);

            if(dice2==2||dice2==5)
            {
                score=0;// when dice 2 or 5 score will be 0
                error2 = 3;// variable for to get out of the while loop when all the dice are 2 or 5
                check=0;// help to keep score 0 when we roll other dice
                exctcheck2=5;// variable for to be able to print that this dice is removed when it is 2 or 5
            }
            else if(check==1)// control the previous dice if 1,3,4 or 6 to add the dice
            {
                score+=dice2;// to store score
                error2 = 2;// to stay in while loop
                check=1;// for be able to add dices
            }

        }


        if ((dice3 != 2 && dice3 != 5)&&error3==2)// if 2 or 5 rolls, this dice will not be used again in this round
        {
            dice3 = rolldice();
            printf(" [Dice 3]: %d",dice3);

            if(dice3==2||dice3==5)
            {
                score=0;// when dice 2 or 5 score will be 0
                error3 = 3;// variable for to get out of the while loop when all the dice are 2 or 5
                check=0;// help to keep score 0 when we roll other dice
                exctcheck3=5;// variable for to be able to print that this dice is removed when it is 2 or 5

            }
            else if(check==1)// control the previous dice if 1,3,4 or 6 to add the dice
            {
                score+=dice3;// to store score
                error3 = 2;// to stay in while loop
                check=1;// for be able to add dices

            }

        }


        if ((dice4 != 2 && dice4 != 5)&&error4==2)// if 2 or 5 rolls, this dice will not be used again in this round
        {
            dice4 = rolldice();
            printf(" [Dice 4]: %d",dice4);
            if(dice4==2||dice4==5)
            {
                score=0;// when dice 2 or 5 score will be 0
                error4 = 3;// variable for to get out of the while loop when all the dice are 2 or 5
                check=0;// help to keep score 0 when we roll other dice
                exctcheck4=5;// variable for to be able to print that this dice is removed when it is 2 or 5

            }
            else if(check==1)// control the previous dice if 1,3,4 or 6 to add the dice
            {
                score+=dice4;// to store score
                error4 = 2;// to stay in while loop
                check=1;// for be able to add dices
            }

        }



        if ((dice5 != 2 && dice5 != 5)&&error5==2)// if 2 or 5 rolls, this dice will not be used again in this round
        {
            dice5 = rolldice();
            printf(" [Dice 5]: %d",dice5);

            if(dice5==2||dice5==5)
            {
                score=0;// when dice 2 or 5 score will be 0
                error5 = 3;// variable for to get out of the while loop when all the dice are 2 or 5
                check=0;// help to keep score 0 when we roll other dice
                exctcheck5=5;// variable for to be able to print that this dice is removed when it is 2 or 5

            }
            else if(check==1)// control the previous dice if 1,3,4 or 6 to add the dice
            {
                score+=dice5;// to store score
                error5 = 2;// to stay in while loop
                check=1;// for be able to add dices
            }

        }
        if((dice1==2||dice1==5)&&(dice2==2||dice2==5)&&(dice3==2||dice3==5)&&(dice4==2||dice4==5)&&(dice5==2||dice5==5))// when all dices 2 or 5 print drop death
            printf("\nDrop Dead!");
        else {

            while(exctcheck5==5||exctcheck4==5||exctcheck3==5||exctcheck2==5||exctcheck1==5)// to check any of dices 2 or 5
            {
                printf("\n");
                if (exctcheck1 == 5)//To be able to print that this dice is removed when it is 2 or 5
                    printf(" [Dice 1] ");
                if (exctcheck2 == 5)
                    printf(" [Dice 2] ");
                if (exctcheck3 == 5)
                    printf(" [Dice 3] ");
                if (exctcheck4 == 5)
                    printf(" [Dice 4] ");
                if (exctcheck5 == 5)
                    printf(" [Dice 5] ");
                printf("are excluded ");
                exctcheck1=6,exctcheck2=6,exctcheck3=6,exctcheck4=6,exctcheck5=6;// change the value of the variables to print only once that the dice were removed

            }
        }

        printf("\nmy score %d ",score);
        totalscore+=score;
        printf(" my  total score %d\n",totalscore);

    }
    return totalscore;// return computer score for only for the called round
}
int playerplay()// function makes the player play the game.
{
    int score,dice1,dice2,dice3,dice4,dice5,error1=2,error2=2,error3=2,error4=2,error5=2,totalscore=0,check,exctcheck1=6,exctcheck2=6,exctcheck3=6,exctcheck4=6,exctcheck5=6;
    printf("Are you ready to play! ");
    printf("I rolled them for you and you got");
    printf("--->  ");
    dice1=rolldice();
    dice2=rolldice();
    dice3=rolldice();
    dice4=rolldice();
    dice5=rolldice();
    if(dice1==2||dice1==5||dice2==2||dice2==5||dice3==2||dice3==5||dice4==2||dice4==5||dice5==2||dice5==5)// if any dice is 2 or 5 it makes the score 0
        score=0;
    else
        score=dice1+dice2+dice3+dice4+dice5;

    if(dice1==2||dice1==5)
    {
        error1 = 3;// variable for to get out of the while loop when all the dice are 2 or 5
        exctcheck1=5;// variable for to be able to print that this dice is removed when it is 2 or 5

    }
    if(dice2==2||dice2==5)
    {
        error2 = 3;
        exctcheck2=5;
    }
    if(dice3==2||dice3==5)
    {
        error3 = 3;
        exctcheck3=5;
    }
    if(dice4==2||dice4==5)
    {
        error4 = 3;
        exctcheck4=5;
    }
    if(dice5==2||dice5==5)
    {
        error5 = 3;
        exctcheck5=5;
    }
    printf("[Dice 1 ]: %d [Dice 2 ]: %d [Dice 3 ]: %d [Dice 4 ]: %d [Dice 5 ]: %d \n",dice1,dice2,dice3,dice4,dice5);

    while(exctcheck5==5||exctcheck4==5||exctcheck3==5||exctcheck2==5||exctcheck1==5)// to check any of dices 2 or 5
    {
        printf("\n");
        if (exctcheck1 == 5)//To be able to print that this dice is removed when it is 2 or 5
            printf("[Dice 1] ");
        if (exctcheck2 == 5)
            printf("[Dice 2] ");
        if (exctcheck3 == 5)
            printf("[Dice 3] ");
        if (exctcheck4 == 5)
            printf("[Dice 4] ");
        if (exctcheck5 == 5)
            printf("[Dice 5] ");
        printf("are excluded ");
        exctcheck1=6,exctcheck2=6,exctcheck3=6,exctcheck4=6,exctcheck5=6;// change the value of the variables to print only once that the dice were removed


    }

    printf("\n Your score %d ",score);
    totalscore+=score;
    printf(" Your total score %d\n",totalscore);


    while(error1==2||error2==2||error3==2||error4==2||error5==2)
    {
        score=0;
        check=1;
        printf("\n");
        printf("I rolled and you got --->  ");




        if ((dice1 != 2 && dice1 != 5)&&error1==2)// if 2 or 5 rolls, this dice will not be used again in this round
        {
            dice1 = rolldice();

            printf(" [Dice 1]: %d",dice1);
            if(dice1==2||dice1==5)
            {
                score=0;// when dice 2 or 5 score will be 0
                error1 = 3;// variable for to get out of the while loop when all the dice are 2 or 5
                check=0;// help to keep score is 0 or not when we roll other dice
                exctcheck1=5;// variable for to be able to print that this dice is removed when it is 2 or 5

            }
            else
            {
                score+=dice1;// to store score
                error1 = 2;// to stay in while loop
                check=1;// for be able to add dices
            }

        }

        if ((dice2 != 2 && dice2 != 5) && error2==2)
        {
            dice2 = rolldice();
            printf(" [Dice 2]: %d",dice2);

            if(dice2==2||dice2==5)
            {
                score=0;
                error2 = 3;
                check=0;
                exctcheck2=5;
            }
            else if(check==1)// control the previous dice if 1,3,4 or 6 to add the dice
            {
                score+=dice2;
                error2 = 2;
                check=1;
            }

        }


        if ((dice3 != 2 && dice3 != 5)&&error3==2)
        {
            dice3 = rolldice();
            printf(" [Dice 3]: %d",dice3);

            if(dice3==2||dice3==5)
            {
                score=0;
                error3 = 3;
                check=0;
                exctcheck3=5;

            }
            else if(check==1)
            {
                score+=dice3;
                error3 = 2;
                check=1;

            }

        }


        if ((dice4 != 2 && dice4 != 5)&&error4==2)
        {
            dice4 = rolldice();
            printf(" [Dice 4]: %d",dice4);
            if(dice4==2||dice4==5)
            {
                score=0;
                error4 = 3;
                check=0;
                exctcheck4=5;

            }
            else if(check==1)
            {
                score+=dice4;
                error4 = 2;
                check=1;
            }

        }



        if ((dice5 != 2 && dice5 != 5)&&error5==2)
        {
            dice5 = rolldice();
            printf(" [Dice 5]: %d",dice5);

            if(dice5==2||dice5==5)
            {
                score=0;
                error5 = 3;
                check=0;
                exctcheck5=5;

            }
            else if(check==1)
            {
                score+=dice5;
                error5 = 2;
                check=1;
            }

        }
        if((dice1==2||dice1==5)&&(dice2==2||dice2==5)&&(dice3==2||dice3==5)&&(dice4==2||dice4==5)&&(dice5==2||dice5==5))// when all dices 2 or 5 print drop death
            printf("\nDrop Dead!");
        else {

            while(exctcheck5==5||exctcheck4==5||exctcheck3==5||exctcheck2==5||exctcheck1==5)// to check any of dices 2 or 5
            {
                printf("\n");
                if (exctcheck1 == 5)//To be able to print that this dice is removed when it is 2 or 5
                    printf(" [Dice 1] ");
                if (exctcheck2 == 5)
                    printf(" [Dice 2] ");
                if (exctcheck3 == 5)
                    printf(" [Dice 3] ");
                if (exctcheck4 == 5)
                    printf(" [Dice 4] ");
                if (exctcheck5 == 5)
                    printf(" [Dice 5] ");
                printf("are excluded ");
                exctcheck1=6,exctcheck2=6,exctcheck3=6,exctcheck4=6,exctcheck5=6;// change the value of the variable to print only once that the dice were removed

            }
        }

        printf("\n Your score score %d ",score);
        totalscore+=score;
        printf(" Your  total score %d\n",totalscore);

    }
    return totalscore;// return player score for only for the called round
}

int scoresheet(int playertotal ,int comptotal)// this function responsible from printing scores
{
    //function takes total scores from main function and print them

    printf("\n============================");
    printf("\nMy Score                Your Score");
    printf("\n%d                      %d ",comptotal,playertotal);


}
int main()
{
    int round,i,startcheck=0,startcheck2=0,start,win,player,comp,comptotal=0,playertotal=0;
    srand(time(NULL));// for be able to create every dice randomly
    printf("Welcome to the Drop Dead game.\n");
    printf("Lets get started!\n");
    printf("How many rounds would you like to play? ");
    scanf("%d",&round);// take round number from user
    while(startcheck==startcheck2)// check which player start first  this while for draw situation
    {
        startcheck=rolldice();//computer dice for who start first
        startcheck2=rolldice();//player dice for who start first
        printf("I have rolled the dice and got %d\n",startcheck);
        printf("I have rolled the dice for you and you got %d\n",startcheck2);
        printf("\n");
        if(startcheck> startcheck2)
            start=2;//for computer start
        else if(startcheck2>startcheck)
            start=3;//for player start

    }
    for(i=1;i<=round;i++)//In order to play as much as the number of rounds entered by the user
    {

        if (start == 2)//if computer star first
        {
            printf("Round %d my turn\n", i);
            printf("========================================\n");
            comp=playcomp();// play computer function called
            printf("\n\n");

            printf("Round %d your turn\n", i);
            printf("========================================\n");
            player=playerplay(); //play player function called
            comptotal+=comp;// store score for print correctly when round number grater than 1
            playertotal+=player;


        }
        else
        {
            printf("Round %d your turn\n", i);
            printf("========================================\n");
            player=playerplay();//play player function called
            printf("\n\n");

            printf("Round %d my turn\n", i);
            printf("========================================\n");
            comp=playcomp();// play computer function called
            comptotal+=comp;// store score for print correctly when round number grater than 1
            playertotal+=player;

        }
        printf(" \nOur scoresheet after round %d:",i);
        printf("\n",scoresheet(playertotal,comptotal));// send scores  to scoresheet function
    }
    if(i==round+1)// to print who won when the game is over
    {
        if(playertotal>comptotal)
            printf("\nYOU ARE THE WINNER");
        else if(comptotal>playertotal)
            printf("\nI AM THE WINNER");
        else
            printf("\nDRAW");
    }
    return 0;
}
