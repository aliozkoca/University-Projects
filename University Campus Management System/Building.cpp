/* Ali Ozkoca 2585271
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only */


#include "Building.h"
#include "Rooms.h"
#include "Office.h"
#include "ClassRoom.h"
#include <cstring>
#include <iostream>

using namespace std;

Building::Building() {
    this->buildingNAME=new char;
    strcpy(this->buildingNAME,"UNDEFINED");
    this->Size=-1;
    this->numOFroom=0;
}
Building::Building(const char *name, int size) {
    this->buildingNAME=new char[strlen(name)+1];
    strcpy(this->buildingNAME,name);
    this->Size=size;
    this->numOFroom=0;
}
int Building::getBuildingsize() {
    return this->Size;
}
void Building::setbuildingsize(int size) {
    this->Size=size;
}
char *Building::getBuildingName() {
    return  this->buildingNAME;
}
void Building::setBuildingName(const char * name) {
    this->buildingNAME=new char[strlen(name)+1];
    strcpy(this->buildingNAME,name);
}
int Building::getNumOFroom() {
    return  this->numOFroom;
}
void Building::addRoom(int typee,const char *name,int flor,int cap,int numofpeopleoffice) {
    if(typee==1) {//when  type is classroom cap woek as classroom capacity
        rooms[numOFroom]=new ClassRoom(name,flor,cap);
    }
    else if(typee==2) {

        rooms[numOFroom]=new Office(name,flor,cap,numofpeopleoffice);//when type is office cap work as office type
    }else {
        cout<<"Wrong Type for addRoom function"<<endl;
    }
    numOFroom++;
}
void Building::printBuilding() {
    cout<<endl<<"Building Name ="<<this->buildingNAME<<endl;
    cout<<"Building Size="<<this->Size<<endl;
    cout<<"Building number of rooms="<<this->numOFroom<<endl;
}
void Building::printRooms() {
    for (int i=0;i<this->numOFroom;i++) {
        rooms[i]->printRoom();
    }
}
void Building::printRoomsByType(int t) {
    for (int i=0;i<this->numOFroom;i++) {
        if(rooms[i]->GetROOMtype()==t) {
            rooms[i]->printRoom();
        }
    }
}
int Building::getNumberOfClassrooms() {
    int count=0;
    for (int i=0;i<this->numOFroom;i++) {
        if(rooms[i]->GetROOMtype()==1) {
            count++;
        }
    }
    return count;
}

int Building::getTotalCapacity() {
    int sum=0;
    for (int i=0;i<this->numOFroom;i++) {
        if(rooms[i]->GetROOMtype()==2) {
            sum+=rooms[i]->getCapacity();
        }
    }
    return sum;
}
int Building::getNumberOfOffices() {
    int count=0;
    for (int i=0;i<this->numOFroom;i++) {
        if(rooms[i]->GetROOMtype()==2) {
            count++;
        }
    }
    return count;
}
void Building::printAvailableOffices() {
    for (int i=0;i<this->numOFroom;i++) {
        if(rooms[i]->GetROOMtype()==2) {
            if(rooms[i]->isFull()==false) {
                rooms[i]->printRoom();
            }
        }
    }
}
void Building::printSuitableClassrooms(int studetnum) {
    for (int i=0;i<this->numOFroom;i++) {
        if(rooms[i]->GetROOMtype()==1) {
            if(rooms[i]->checkSuitability(studetnum)==true) {
                rooms[i]->printRoom();
            }
        }
    }
}
Building::Building(const Building &b) {
    this->buildingNAME=new char[strlen(b.buildingNAME)+1];
    strcpy(this->buildingNAME,b.buildingNAME);
    this->Size=b.Size;
    this->numOFroom=b.numOFroom;
    for (int i=0;i<b.numOFroom;i++) {
        this->rooms[i]=b.rooms[i];
    }
}
void Building::operator=(const Building &b) {
    delete [] this->buildingNAME;
    this->buildingNAME=new char[strlen(b.buildingNAME)+1];
    strcpy(this->buildingNAME,b.buildingNAME);
    this->Size=b.Size;
    this->numOFroom=b.numOFroom;
    for (int i=0;i<b.numOFroom;i++) {
        this->rooms[i]=b.rooms[i];
    }
}
Building::~Building() {
    delete[]this->buildingNAME;
    for(int i=0;i<this->numOFroom;i++) {
        delete rooms[i];
    }
}

















