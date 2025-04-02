/* Ali Ozkoca 2585271
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only */


#include <iostream>
#include "University.h"
using namespace std;
int main() {
    University uni("METU NCC");
    int option;// option variable for menu iteam
    do {
        option=-1;//after one loop finish we should restart the option
        cout<<endl<<"[1] Add a new building to the university"<<endl;
        cout<<"[2] Add a new room to a selected building"<<endl;
        cout<<"[3] Print the buildings in the university"<<endl;
        cout<<"[4] Print the rooms in each building in the university"<<endl;
        cout<<"[5] Print the rooms in each building in the university based on type"<<endl;
        cout<<"[6] Print the total number of classrooms and offices in the university"<<endl;
        cout<<"[7] Print the available offices in each building in the university"<<endl;
        cout<<"[8] Print the total capacity of all the offices"<<endl;
        cout<<"[9] Print the suitable classrooms in the university based on the given number of students"<<endl;
        cout<<"[0] Exit"<<endl;
        cout<<"Please enter your choice: ";
        scanf("%d",&option);
        if(option==1) {
            if(uni.getNumberOFbuilding()<20) {
                int size;
                char name[200];//temporary name for sending the calling addBuilding function
                cout<<"Please enter name of building:";
                scanf("%s",name);
                cout<<"Please enter size of building:";
                scanf("%d",&size);
                uni.addBuilding(name,size);
            }else {
                cout<<uni.getUniversityName()<<" Reached it capacity for the buildings"<<endl;
            }

        }
        else if(option==2) {
            uni.printBuildings();
            int buil,type,flor,cap,numpeople;//temporary variable for the calling addRoom function
            char name[200];//temporary name for the calling addRoom function

            cout<<endl<<"Please enter the number of building to which the room should be added:";
            scanf("%d",&buil);
            cout<<"Please enter the type of room(1: Classroom/ 2: Office):";
            scanf("%d",&type);
            cout<<"Please enter the name of the new room:";
            scanf("%s",name);
            cout<<"Please enter the floor number of the new room: ";
            scanf("%d",&flor);
            if(type==2) {
                cout<<endl<<"[1] Coordinator Office"<<endl<<"[2] Standard Office"<<endl;
                cout<<"[3] Shared Office for 2 people"<<endl<<"[4] Shared Office for 3 people"<<endl;
                cout<<"[5] Shared Office for 10 people"<<endl<<"Please enter type of office:";
                scanf("%d",&cap); // in office cap work as office type
                cout<<"Please enter number of people in the office: ";
                scanf("%d",&numpeople);
                uni.addRoom(buil,type,name,flor,cap,numpeople);

            }
            else if(type==1) {
                cout<<"Please enter capacity of classroom: ";
                scanf("%d",&cap); // in the classroom cap work as Capacity
                uni.addRoom(buil,type,name,flor,cap,numpeople);//when we are adding classroom numpeople variable will be useless
            }
        }else if(option==3) {
            uni.printBuildings();
        }else if(option==4) {
            uni.printRooms();
        }
        else if(option==5) {
            int type;
            cout<<endl<<"Please enter type of room to display:";
            cout<<endl<<"[1] Classrooms"<<endl;
            cout<< "[2] Offices"<<endl;
            scanf("%d",&type);
            uni.printRoomsByType(type);
        }else if(option==6) {
            uni.printRoomTypeStatistics();
        }else if(option==7) {
            uni.printAvailableOffices();
        }else if(option==8) {
            uni.printTotalCapacityOfOffices();
        }else if(option==9) {
            int num;
            cout<<"Please enter number of students:";
            scanf("%d",&num);
            uni.printSuitableClassrooms(num);
        }else if(option==0) {
            cout<<"Thank you for using the university campus management system";
            return 0;
        }else {
            cout<<"Please enter the option again"<<endl;
        }
    } while (option!=0);
    return 0;
}
