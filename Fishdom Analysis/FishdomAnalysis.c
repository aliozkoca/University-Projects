#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avltree.h"
//         Ali Ozkoca
//          2585271
//         Section-3
tree insert(tree t,float weight,float lenght,char name[],char date[],char city[])
{
    if(t==NULL)
    {
        t=(tree) malloc(sizeof(struct Avltree));
        if(t==NULL)
        {
            printf("Error in allocation");
            exit(1);
        }
        t->data=(struct data*) malloc(sizeof(struct data));
        if(t->data==NULL)
        {
            printf("Error in allocation");
            exit(1);
        }
        else
        {
            t->weight=weight;t->data->lenght=lenght;
            strcpy(t->data->city,city);
            strcpy(t->data->date,date);
            strcpy(t->data->name,name);
            t->height=0;
            t->left=NULL;
            t->right=NULL;
            t->data->next=NULL;
        }
    } else if(weight<t->weight)
    {
        t->left= insert(t->left,weight,lenght,name,date,city);
        if(AVLTreeHeight(t->left)- AVLTreeHeight(t->right)==2)
        if(weight<t->left->weight)
            t= SingleRotateWithLeft(t);
        else
        {
            t= DoubleRotateWithLeft(t);
        }

    }else if (weight > t->weight)
    {
        t->right = insert(t->right,weight,lenght,name,date,city);
        if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2)
        if (weight > t->right->weight)
            t = SingleRotateWithRight(t);
        else
            t = DoubleRotateWithRight(t);
    }
    else
    {// if there is a same fish add the data to fishes data list
        struct data *tmp=t->data;
        struct data *tmp2;
        for(;tmp->next!=NULL;tmp=tmp->next)
        {
        }
        tmp2=(struct data*) malloc(sizeof(struct data));
        if(tmp2==NULL)
        {
            printf("Error in allocation");
            exit(1);
        }
        tmp2->lenght=lenght;
        strcpy(tmp2->city,city);
        strcpy(tmp2->date,date);
        strcpy(tmp2->name,name);
        tmp2->next=NULL;
        tmp->next=tmp2;


    }
    t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;
    return t;


}
tree readData(char filename[])
{
    FILE * infile;
    infile=fopen(filename,"r");
    if(infile==NULL)
    {
        printf("Error in opening file");
    }
    tree mytree=NULL;
    float weight,lenght;
    char name[80],date[80],city[80],tmp[100];
    fgets(tmp,100,infile);//avoiding the first line in the file which is Name,Weight,Lenght,Date,City
    while(fscanf(infile,"%[^,],%f,%f,%[^,],%[^\n]%*c",name,&weight,&lenght,date,city)!=EOF)
    {                                                         //%*c for avoid the new line char
        mytree=insert(mytree,weight,lenght,name,date,city);

    }
    return mytree;

}
void displayfullindex(tree t)
{
    if (t != NULL)
    {
        displayfullindex(t->left);
        struct data*tmp=t->data;
        for(;tmp!=NULL;tmp=tmp->next)
        {
            printf("%s,%.2f,%.2f,%s,%s\n", tmp->name,t->weight,tmp->lenght,tmp->date,tmp->city);
        }
        displayfullindex(t->right);
    }
}

void heaviestFish(tree t)
{
    if(t!=NULL)        //the function will go to most right and print the data of heaviest fish
    {
        if(t->right==NULL)   // complexity of for loop is O(k) the recursive part of this function complexity is O(logN) the worst case is k=N
        {                                 //so the complexity of heaviest fish O(NlogN) actually i do not know the better way for this problem
            struct data*tmp=t->data;
            for(;tmp!=NULL;tmp=tmp->next)
            {
                printf("%s,%.2f,%.2f,%s,%s\n", tmp->name,t->weight,tmp->lenght,tmp->date,tmp->city);
            }
        }
        else
            heaviestFish(t->right);
    }
}

tree longestfish(tree t,tree x)
{
    // this function will travers the all the fishes and datas and find the longest fish and return it
         // complexity of for loop is O(k) the recursive part of this function complexity is O(logN) the worst case is k=N
         //so the complexity of longestfish is O(NlogN) actually i do not know the better way for this problem
    if (t != NULL)
    {
        longestfish(t->left,x);
        struct data*tmp=t->data;
        for(;tmp!=NULL;tmp=tmp->next)
        {
            if(tmp->lenght>x->data->lenght)
            {
                x->data->lenght=tmp->lenght;
                strcpy(x->data->name,tmp->name);
                strcpy(x->data->city,tmp->city);
                strcpy(x->data->date,tmp->date);
                x->weight=t->weight;
            }
        }
        longestfish(t->right,x);
    }
    return x;

}


int main(int argc, char *argv[]) {
    int option=0;
    tree mytree;
    tree longfish=NULL;//for keeping the longest fish data
    longfish= insert(longfish,0,0,"a","a","a");
    mytree= readData(argv[1]);
    printf("********Welcome to Fishdom Analysis********\n");
    while (option!=4)
    {
        printf("*******************************************\n");
        printf("MENU:\n");
        printf("1. Display the full index of fishdom\n");
        printf("2. Display the heaviest fishes\n");
        printf("3. Display the longest fishes\n");
        printf("4.Exit\n");
        printf("*******************************************\n");
        printf("\n");
        printf("Enter your option:");
        scanf("%d",&option);
        if(option==1)
        {
            displayfullindex(mytree);
        }
        else if(option==2)
        {
            heaviestFish(mytree);
        } else if(option==3)
        {
            longfish=longestfish(mytree,longfish);
            printf("%s,%.2f,%.2f,%s,%s\n",longfish->data->name,longfish->weight,longfish->data->lenght,longfish->data->date,longfish->data->city);
        } else if(option==4)
        {
            printf("bye!");
        } else
        {
            printf("Please enter your option again!\n");
        }
    }
    return 0;
}
