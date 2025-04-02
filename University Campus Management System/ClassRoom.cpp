/* Ali Ozkoca 2585271
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only */

#include "ClassRoom.h"
#include <iostream>
#include <cstring>
using namespace std;

//Function OF ClassRoom Class
ClassRoom::ClassRoom():Room(){
    this->Capacity=-1;
}
ClassRoom::ClassRoom(const char *a, int b, int c):Room(a,b){
    this->Capacity=c;
}
int ClassRoom::getCapacity() {
    return this->Capacity;
}
void ClassRoom::Setcapacity(int a) {
    this->Capacity=a;
}
ClassRoom::ClassRoom(const ClassRoom &c) {
    this->name=new char[strlen(c.name)+1];
    strcpy(this->name,c.name);
    this->floorNO=c.floorNO;
    this->Capacity=c.Capacity;
}
void ClassRoom::operator=(const ClassRoom &c) {
    delete[]this->name;
    this->name=new char[strlen(c.name)+1];
    strcpy(this->name,c.name);
    this->floorNO=c.floorNO;
    this->Capacity=c.Capacity;
}
bool ClassRoom::checkSuitability(int NumStudent) {
    if(NumStudent<=this->Capacity) {
        return true;
    }
        return false;


}
ClassRoom::~ClassRoom() {
    delete[]this->name;
}

void ClassRoom::printRoom() {
    cout<<endl<<"Classroom name = "<<this->name<<endl;
    cout <<"Classroom floor number ="<<this->floorNO<<endl;
    cout << "Classroom capacity ="<<this->Capacity<<endl;
}
int ClassRoom::GetROOMtype() {
    return 1;
}