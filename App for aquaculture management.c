#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//----------------------
//          Ali Ozkoca
//            2585271
//           Section-3


struct FishData // structure for store fishes
{
    float  weight;
    float  verticallength;
    float diagonallength;
    float crosslength;
    float height;
    float fishlength;
    int day;
    int mount;// There is a mistake here, normally it should be the month
    int year;
    char city[80];
    struct FishData *next;


};

struct FishSpec  // structure for store species
{
    char fish_name[80];
    struct FishData * data;
    struct FishSpec *next;
    int size;

};

struct FishSpec *initialize(char filename[80]) // this function will read the txt file and initialize the structures
{
    FILE *infile;
    infile= fopen(filename,"r");
    float  weight=0;
    float  verticallength;
    float diagonallength;
    float crosslength;
    float height;
    float fishlength;
    int day;
    int mount;
    int year;
    char city[80];
    char fishname[80];

    struct FishSpec *fishlist,*last;
    fishlist=(struct FishSpec*) malloc(sizeof(struct FishSpec));
    if(fishlist==NULL)
    {
        printf("Error in memory allocation");
        exit(1);
    }
    fishlist->next=NULL;
    last=fishlist;
    fishlist->size=0;
    fishlist->data= (struct FishData*) malloc(sizeof(struct FishData));
    if(fishlist->data==NULL)
    {
        printf("Error in memory allocation");
        exit(1);
    }
    fishlist->data->next=NULL;

    while (fscanf(infile,"%[^;];%f;%f;%f;%f;%f;%f;%d/%d/%d;%[^\n]%*c",fishname,&weight,&verticallength,&diagonallength,&crosslength,&height,&fishlength,&day,&mount,&year,city)!=EOF)
    {                                                                        //%*c for avoid the new line char
        if(strcmp(last->fish_name,fishname)==0)// if we read already exist species
        {
            struct FishData *tmp;
            tmp= (struct FishData*) malloc(sizeof(struct FishData));
            if(tmp==NULL)
            {
                printf("Error in allocation");
                exit(1);
            }
            tmp->weight=weight;tmp->verticallength=verticallength;tmp->diagonallength=diagonallength;tmp->crosslength=crosslength;
            tmp->height=height;tmp->fishlength=fishlength;tmp->day=day;tmp->mount=mount;tmp->year=year;
            strcpy(tmp->city,city);
            last->data->next=tmp;

        }
        else // if we read new species
            {
                struct FishSpec* tempro;
                tempro=(struct FishSpec*) malloc(sizeof(struct FishSpec));
                if(tempro==NULL)
                {
                    printf("Error in memory allocation");
                    exit(1);
                }

                tempro->data=(struct FishData*) malloc(sizeof(struct FishData));
                if(tempro->data==NULL)
                {
                    printf("Error in memory allocation");
                    exit(1);
                }
                strcpy(tempro->fish_name,fishname);
                tempro->data->weight=weight;tempro->data->verticallength=verticallength;tempro->data->diagonallength=diagonallength;tempro->data->crosslength=crosslength;
                tempro->data->height=height;tempro->data->fishlength=fishlength;tempro->data->day=day;tempro->data->mount=mount;tempro->data->year=year;
                strcpy(tempro->data->city,city);

                last->next=tempro;
                last=tempro;
                fishlist->size++;
            }
    }
    fclose(infile);
    return fishlist;
}
void deletefish(struct FishSpec *fishs,float threshold)
{
    int count=0;
    struct FishSpec*tmp,*prev;
    tmp=fishs->next;//for traversing species
    prev=fishs;
    while (tmp!=NULL)
    {
        struct FishData *tmpdata,*prevdata;
        tmpdata=tmp->data;// for traversing datas
        prevdata=NULL;
        while (tmpdata!=NULL)
        {
            if(tmpdata->weight<threshold)
            {
                if(prevdata==NULL)
                {
                    tmp->data=tmpdata->next;// for not lose the lists
                    free(tmpdata);
                    tmpdata=tmp->data;
                    count++;
                } else
                {
                    prevdata->next=tmpdata->next;// for not lose the lists
                    free(tmpdata);
                    tmpdata=prevdata->next;
                    count++;
                }
            } else
            {
                prevdata=tmpdata;
                tmpdata=tmpdata->next;
            }
        }
        tmp=tmp->next;
    }
    printf("%d fish data was deleted from your list!",count);
}

void printStatistic(struct FishSpec  *fish)
{
    char fishname[80];
    int count=0;
    struct FishSpec *tmp=fish->next;
    printf("Provide the fish name");
    scanf("%s",fishname);
    for(;(tmp!=NULL)&&(strcmp(tmp->fish_name,fishname)!=0);tmp=tmp->next)//to travers until the correct species
    {
    }
    if(strcmp(tmp->fish_name,fishname)==0)
    {
        struct FishData * data=tmp->data;
        for(;data!=NULL;data=data->next)
        {
            count=count+1;
        }
    }
    printf("The number of available fish data is %d",count);
}

void searchFishData(struct FishSpec *fish)
{
    char option;
    char city[80];
    int month,check=0;
    fflush(stdin);

    printf("Enter your search option (C for city/M for month):");
    scanf(" %c",&option);
    struct FishSpec * tmp;
    tmp=fish->next;// for travers the through species

    if(option=='C')
    {
        printf("Enter the city:");
        scanf("%s",city);

        for(;tmp!=NULL;tmp=tmp->next)
        {
            struct FishData * data=tmp->data;// for traversing the through datas
            for(;data!=NULL;data=data->next)
            {
                if(strcmp(data->city,city)==0)
                {
                    printf("\n%s;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%d/%d/%d;%s",tmp->fish_name,data->weight,data->verticallength,data->diagonallength,
                           data->crosslength,data->height,data->fishlength,data->day,data->mount,data->year,data->city);

                }

            }
        }

    }
    if(option=='M')
    {
        printf("Enter the month number:");
        scanf("%d",&month);

        do
        {
            if((month<=12&&month>=0)!=1)
            {
                printf("Enter the month number:");
                scanf("%d",&month);

            }
            for(;tmp!=NULL;tmp=tmp->next)//traversing through species
            {
                struct FishData * data=tmp->data;
                for(;data!=NULL;data=data->next)// traversing through datas
                {
                    if(data->mount==month)
                    {
                        printf("\n%s;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%d/%d/%d;%s",tmp->fish_name,data->weight,data->verticallength,data->diagonallength,
                               data->crosslength,data->height,data->fishlength,data->day,data->mount,data->year,data->city);
                        check=1;//for ending do while loop
                    }
                }
            }
        } while ((month<=12&&month>=0)&&check==0);
    }



}

void addSpeciesList(struct FishSpec * fish)
{
    struct FishSpec*tmp,*add;
    add=(struct FishSpec*) malloc(sizeof (struct FishSpec));
    if(add==NULL)
    {
        printf("Error in allocation");
        exit(1);
    }
    add->data=(struct FishData*) malloc(sizeof(struct FishData));
    if(add->data==NULL)
    {
        printf("Error in allocation");
        exit(1);
    }
    tmp=fish->next;
    char option;
    do
    {

        printf("The new species is:");
        scanf("%s",add->fish_name);
        printf("\nProvide the following info:");
        printf("\nWeight of the fish in grams:");
        scanf("%f",&add->data->weight);
        printf("\nVertical length in CM:");
        scanf("%f",&add->data->verticallength);
        printf("\nDiagonal length in CM:");
        scanf("%f",&add->data->diagonallength);
        printf("\nCross length in CM:");
        scanf("%f",&add->data->crosslength);
        printf("\nHeight in CM:");
        scanf("%f",&add->data->height);
        printf("Fish Length in CM:");
        scanf("%f",&add->data->fishlength);
        printf("\nFishing date:");
        scanf("%d/%d/%d",&add->data->day,&add->data->mount,&add->data->year);
        printf("\nCity:");
        scanf("%s",add->data->city);
        printf("\nDo you want to add more fish (Y/N):");
        scanf(" %c",&option);

    } while (option=='Y');
    for(;tmp->next!=NULL;tmp=tmp->next)
    {
    }
    tmp->next=add;//for add this species add to end of species list


}

void addfishdata(struct FishSpec* fishs) 
{
    struct FishSpec* tmp,*tmp1;
    tmp1=fishs->next;

    tmp=(struct FishSpec*) malloc(sizeof(struct FishSpec));
    if(tmp==NULL)
    {
        printf("Error in allocation");
        exit(1);
    }
    tmp->data=(struct FishData*) malloc(sizeof(struct FishData));
    if(tmp==NULL)
    {
        printf("Error in allocation");
        exit(1);
    }

    printf("Species:");
    scanf("%s",tmp->fish_name);


    for(;(tmp1->next!=NULL) && (strcmp(tmp->fish_name,tmp1->fish_name)!=0);tmp1=tmp1->next)//traversing through species until last element or correct condition
    {
    }
    if(strcmp(tmp->fish_name,tmp1->fish_name)==0)
    {
        printf("Weight of the fish in grams:");
        scanf("%f",&tmp->data->weight);
        printf("Vertical length in CM:");
        scanf("%f",&tmp->data->verticallength);
        printf("Diagonal length in CM:");
        scanf("%f",&tmp->data->diagonallength);
        printf("Cross length in CM:");
        scanf("%f",&tmp->data->crosslength);
        printf("Height in CM:");
        scanf("%f",&tmp->data->height);
        printf("Fish Length in CM:");
        scanf("%f",&tmp->data->fishlength);
        printf("Fishing date:");
        scanf("%d/%d/%d",&tmp->data->day,&tmp->data->mount,&tmp->data->year);
        printf("City:");
        scanf("%s",tmp->data->city);
        tmp1->data->next=tmp->data;
    } else // if the input species not exist already than the addspecieslist function will add new species
    {
        addSpeciesList(fishs);
    }



}
void saveUpdatedList(struct FishSpec*fish,char filename[])
{
    struct FishSpec*tmp;
    tmp=fish->next;
    FILE *outfile;
    outfile= fopen(filename,"w");
    if(outfile ==NULL)
    {
        printf("Error in opening file");
        exit(1);
    }
    for(;tmp!=NULL;tmp=tmp->next)
    {
        struct FishData * data=tmp->data;
        if(tmp->data!=NULL)// for not print deleted species
        {
            for(;data!=NULL;data=data->next)
            {
                fprintf(outfile,"%s;%f;%f;%f;%f;%f;%f;%d/%d/%d;%s\n",tmp->fish_name,data->weight,data->verticallength,data->diagonallength,
                        data->crosslength,data->height,data->fishlength,data->day,data->mount,data->year,data->city);
            }
        } else
            continue;
    }
    fclose(outfile);
}

int main() {
    int option;
    char filename[80] ="fishingArchive.txt";
    float threshold;
    struct FishSpec *fishs ;
    fishs= initialize(filename);//
    do
    {
        printf("\n------------MENU--------------");
        printf("\n1. Add Fish Data");
        printf("\n2. Delete Fish Data");
        printf("\n3. Print Fish Statistics");
        printf("\n4. Search Fish Data");
        printf("\n5. Add Species List");
        printf("\n6. Exit");
        printf("\nPlese enter your option");
        scanf("%d",&option);
        if(option==1)
        {
            addfishdata(fishs);
        }
        else if (option==2)
        {
            printf("Provide fish weight threshold in grams:");
            scanf("%f",&threshold);
            deletefish(fishs,threshold);
        } else if(option==3)
        {
            printStatistic(fishs);
        } else if(option==4)
        {
            searchFishData(fishs);
        } else if(option==5)
        {
            addSpeciesList(fishs);
        } else if (option==6)
        {
            saveUpdatedList(fishs,filename);
            printf("The %s file has been updated successfully!!",filename);
        }

    }while(option!=6);
    return 0;
}
