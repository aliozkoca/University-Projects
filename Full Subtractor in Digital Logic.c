//Ali Özkoca
//2585271
//CNG 140 Section 3

//-----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#define LF 10 //ASCII code for LINE FEED character
int main()
{
    int option, base, d, bout, notA, decimalinp2, decimalinp3, errorcheck, errorcheck2, closer = 30;
    char inp1, inp2, inp3, inp4, ch, ch2;
    while (closer == 30) // this while keeps the program open until option 2 is selected //
        {
        fflush(stdin);// when program start again buffer will cleared
        errorcheck = 80;// i reassign because when the program starts again these variables will be different and the program does not work properly
        errorcheck2 = 84;
        printf("\n");
        printf("-----------------------------------------------\n");
        printf("Welcome to Full Subtractor!\n");
        printf("Press 1 to Compute and Display the outputs\n");
        printf("Press 2 to Quit\n");
        printf("Please enter your choice:");
        scanf("%d", &option);
        if (option != 1)
        {
            printf("See you Later!");
            closer = 52;//change the value of this variable help me to close the program
        }
        else
        {
            printf("You have chosen option %d\n", option);
            printf("Which Base will you use to enter input (base-2 or base-16):");
            scanf("%d", &base);
            if (base == 2)
            {
                while (errorcheck == 80) //if the user enters the wrong input, it stays open until the correct input is entered.
                {
                    fflush(stdin);// when loop start again buffer will cleared
                    printf("Please enter input:");
                    scanf("%c", &ch);
                    inp1 = ch;//i use inp1 as a A
                    while (ch != LF) {
                        if (inp1 != LF) {
                            scanf("%c", &ch);
                            inp2 = ch;//i use inp2 as a B
                            if (inp2 == LF)
                                break;//if i did not use this breaks output will wrong for more than 3 digit conditions
                        }
                        if (inp2 != LF) {
                            scanf("%c", &ch);
                            inp3 = ch;//i use a inp3 as a bin
                            if (inp3 == LF)
                                break;
                        }
                        if (inp3 != LF) {
                            scanf("%c", &ch);
                            inp4 = ch;//taking this variable for check more than 3 bits
                            if (inp4 != LF)
                                break;
                        }
                    }
                    if (inp1 > 49 || inp2 > 49 || inp3 > 49 ) //to check if input include digit greater than 1
                    {
                        printf("Invalid number in base 2! Please try again!\n");
                    } else if (inp1 == LF || inp2 == LF || inp3 == LF) {
                        printf("You entered less than 3 bits! Please try again!\n");
                    } else if (inp4 != LF)
                    {
                        printf("You entered more than 3 bits! Please try again!\n");
                    } else {
                        errorcheck = 56;//changing this variable will help me to run the program from the beginning because the user entered the correct input.
                        if ((inp1 == 48 && inp2 == 49) || (inp1 == 49 && inp2 == 48))//from XOR table in assignment pdf
                            d = 1;//this d product of(A XOR B)
                        else
                            d = 0;
                        if ((d == 1 && inp3 == 48) || (d == 0 && inp3 == 49))
                            d = 1;//this d product of ((A XOR B) XOR BIN))
                        else
                            d = 0;
                        if (inp1 == 49)
                            notA = 0;//i convert char to int for taking correct output from bout operation
                        else
                            notA = 1;
                        if (inp2 == 49)
                            decimalinp2 = 1;//i convert char to int for taking correct output from bout operation
                        else
                            decimalinp2 = 0;
                        if (inp3 == 49)
                            decimalinp3 = 1;//i convert char to int for taking correct output from bout operation
                        else
                            decimalinp3 = 0;
                        bout = (notA && decimalinp3) || (notA && decimalinp2) || (decimalinp2 && decimalinp3);

                        printf("D is %d Bout is %d\n", d, bout);
                    }
                }
            }
            else if (base == 16)
            {
                while (errorcheck2 == 84)//if the user enters the wrong input, it stays open until the correct input is entered.
                {
                    fflush(stdin);// when loop start again buffer will cleared
                    printf("Please enter input:");
                    scanf(" %c%c", &ch, &ch2);// taking second input for check if input >9 such as 10
                    if (ch2 == LF)
                    {
                        if (ch == '0')
                        {
                            inp1 = 0;//i assign this variables for convert base-16 to base-2 according to which hex number equal to which binary number
                            inp2 = 0;
                            inp3 = 0;
                            errorcheck2 = 48;//changing this variable will help me to run the program from the beginning because the user entered the correct input.
                        } else if (ch == '1') {
                            inp1 = 0;
                            inp2 = 0;
                            inp3 = 1;
                            errorcheck2 = 48;
                        } else if (ch == '2') {
                            inp1 = 0;
                            inp2 = 1;
                            inp3 = 0;
                            errorcheck2 = 48;
                        } else if (ch == '3') {
                            inp1 = 0;
                            inp2 = 1;
                            inp3 = 1;
                            errorcheck2 = 48;
                        } else if (ch == '4') {
                            inp1 = 1;
                            inp2 = 0;
                            inp3 = 0;
                            errorcheck2 = 48;
                        } else if (ch == '5') {
                            inp1 = 1;
                            inp2 = 0;
                            inp3 = 1;
                            errorcheck2 = 48;
                        } else if (ch == '6') {
                            inp1 = 1;
                            inp2 = 1;
                            inp3 = 0;
                            errorcheck2 = 48;
                        } else if (ch == '7') {
                            inp1 = 1;
                            inp2 = 1;
                            inp3 = 1;
                            errorcheck2 = 48;
                        } else if (ch == '8' || ch == '9' || ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D' ||
                                   ch == 'E' || ch == 'F')
                            printf("Not possible to convert it to 3-digit binary number. Please try again!\n");
                        else if (ch > 'F')
                            printf("Invalid number in base 16! Please try again!\n");
                    } else//if second input not equal to ENTER(LF)
                        printf("Invalid number in base 16! Please try again!\n");
                    if (errorcheck2 == 48) // if we didn't write this statement Even if user enter wrong input, it will show a result even if it is wrong
                    {
                        bout = (!inp1 && inp3) || (!inp1 && inp2) || (inp2 && inp3);
                        if ((inp1 == 0 && inp2 == 1) || (inp1 == 1 && inp2 == 0))//from XOR table in assignment pdf
                            d = 1;//this d product of(A XOR B)
                        else
                            d = 0;
                        if ((d == 1 && inp3 == 0) || (d == 0 && inp3 == 1))
                            d = 1;//this d product of ((A XOR B)XOR Bin)
                        else
                            d = 0;
                        printf("D is %d Bout is %d\n", d, bout);
                    }
                }
            }
        }
    }
    return 0;
}
