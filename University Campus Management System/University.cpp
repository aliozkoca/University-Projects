/* Ali Ozkoca 2585271
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only */

#include <iostream>
#include <cstring>
#include "University.h"
using namespace std;
University::University() {
    this->UniversityName=new char;
    strcpy(this->UniversityName,"UNDEFINED");
    this->NumberOFbuilding=0;
}
University::University(const char *name) {
    this->UniversityName=new char[strlen(name)+1];
    strcpy(this->UniversityName,name);
    this->NumberOFbuilding=0;
}
char *University::getUniversityName() {
    return this->UniversityName;
}
void University::setUniversityName(const char *name ) {
    this->UniversityName=new char[strlen(name)+1];
    strcpy(this->UniversityName,name);
}
int University::getNumberOFbuilding() {
    return this->NumberOFbuilding;
}
void University::addBuilding(const char * name, int size) {
    if(NumberOFbuilding<20) {//it only addBuilding when uni doesn't reached it building capactiy
        buildings[NumberOFbuilding]=new Building(name,size);
        NumberOFbuilding++;
    }

}
void University::printBuildings() {
    cout<<endl<<"Buildings in "<< this->UniversityName << " university: "<<endl;
    for (int i=0;i<NumberOFbuilding;i++) {
        cout<<endl<<"["<<i+1<<"]"<< "Building name = "<<buildings[i]->getBuildingName()<<endl;
        cout<<"Building Size ="<<buildings[i]->getBuildingsize()<<endl;
        cout<<"Building number of rooms ="<<buildings[i]->getNumOFroom()<<endl;

    }
}
void University::printRooms() {
    cout<<"Rooms in "<< this->UniversityName << " university:";
    for (int i=0;i<NumberOFbuilding;i++) {
        cout<<endl<<"All rooms in "<<buildings[i]->getBuildingName()<<" building:"<<endl;
        buildings[i]->printRooms();
    }
}
void University::printRoomsByType(int t) {
    if(t==1) {
        cout<<"Classrooms in "<< this->UniversityName << " university:"<<endl;
    }else if(t==2) {
        cout<<"Offices in "<< this->UniversityName << " university:"<<endl;
    }
    for (int i=0;i<NumberOFbuilding;i++) {
        if(t==1) {
            cout<<endl<<"All classrooms in "<<buildings[i]->getBuildingName()<<" building:"<<endl;
        }else if(t==2) {
            cout<<endl<<"All offices in "<<buildings[i]->getBuildingName()<<" building:"<<endl;
        }
        buildings[i]->printRoomsByType(t);
    }
}
void University::printRoomTypeStatistics() {
    cout<<"Room Type statistics for "<< this->UniversityName << " university:"<<endl;
    int offCount=0;
    int ClassCount=0;
    for (int i=0;i<NumberOFbuilding;i++) {
        offCount+=buildings[i]->getNumberOfOffices();
        ClassCount+=buildings[i]->getNumberOfClassrooms();
    }
    cout<<"Number of offices="<<offCount<<endl;
    cout<<"Number of classrooms="<<ClassCount<<endl;
}
void University::printAvailableOffices() {
    cout<<"Available offices in "<< this->UniversityName << " university:"<<endl;
    for (int i=0;i<NumberOFbuilding;i++) {
        cout<<"Available offices in  "<<buildings[i]->getBuildingName()<<" building"<<endl;
        buildings[i]->printAvailableOffices();
    }
}
void University::printTotalCapacityOfOffices() {
    cout<<"Office capacity in "<< this->UniversityName << " university:"<<endl;
    for (int i=0;i<NumberOFbuilding;i++) {
        cout<<"Office capacity in "<<buildings[i]->getBuildingName()<<" building="<< buildings[i]->getTotalCapacity()<<endl;
    }
}
void University::printSuitableClassrooms(int NumOfstudent) {
    cout<<"Suitable classes in "<< this->UniversityName << " for "<<NumOfstudent<< " student:"<<endl;
    for (int i=0;i<NumberOFbuilding;i++) {
        cout<<"Classrooms which are suitable for "<<NumOfstudent<<" student in "<<buildings[i]->getBuildingName()<<" building"<<endl;
        buildings[i]->printSuitableClassrooms(NumOfstudent);
    }
}
void University::addRoom(int buil,int typee,const char *name,int flor,int cap,int numofpeopleoffic) {
//this extra func in University help us to reach the addRoom func in the Building
    if(buildings[buil-1]->getNumOFroom()<100) {// addRoom only when Building[buil-1] does not reach capacity for room
        buildings[buil-1]->addRoom(typee,name,flor,cap,numofpeopleoffic);
        //            build-1 because buil come here grater or equal than 1
    }else {
        cout<<buildings[buil-1]->getBuildingName()<<" Reached its capacity for Room"<<endl;
    }

}
University::University(const University &u) {
    this->UniversityName=new char[strlen(u.UniversityName)+1];
    strcpy(this->UniversityName,u.UniversityName);
    this->NumberOFbuilding=u.NumberOFbuilding;
    for (int i=0;i<u.NumberOFbuilding;i++) {
        this->buildings[i]=u.buildings[i];
    }
}
void University::operator=(const University &u) {
    delete[] this->UniversityName;
    this->UniversityName=new char[strlen(u.UniversityName)+1];
    strcpy(this->UniversityName,u.UniversityName);
    this->NumberOFbuilding=u.NumberOFbuilding;
    for (int i=0;i<u.NumberOFbuilding;i++) {
        this->buildings[i]=u.buildings[i];
    }
}
University::~University() {
    delete[] this->UniversityName;
    for(int i=0;i<this->NumberOFbuilding;i++) {
        delete buildings[i];
    }

}













