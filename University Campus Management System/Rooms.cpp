/* Ali Ozkoca 2585271
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only */

#include "Rooms.h"
#include <iostream>
#include <cstring>
using namespace std;
Room::Room() {
        this->name=new char;
        strcpy(this->name,"UNDEFINED");
        this->floorNO=-1;
}
Room::Room(const char *name, int no) {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->floorNO=no;
}
char *Room::getterNAme() {
        return this->name;
}
char Room::setterName(const char *name) {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
}
int Room::getterNO() {
        return this->floorNO;
}
int Room::setterNO(int no) {
        this->floorNO=no;
}
void Room::printRoom() {
        cout<<"Room name ="<<this->name<<endl<<"Room Flor ="<<this->floorNO<<endl;
}
Room::~Room() {
        delete[] this->name;
}
Room::Room(const Room &r) {
        this->name=new char[strlen(r.name)+1];
        strcpy(this->name,r.name);
        this->floorNO=r.floorNO;
}
void Room::operator=(const Room &r) {
        delete[]this->name;
        this->name=new char[strlen(r.name)+1];
        strcpy(this->name,r.name);
        this->floorNO=r.floorNO;
}




































