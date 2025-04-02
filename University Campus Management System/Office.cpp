/* Ali Ozkoca 2585271
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only */

#include "Office.h"
#include <iostream>
#include <cstring>
using namespace std;
//function of Office Class

Office::Office() {
        this->type=None;
        this->NumOfPeople=0;
}
Office::Office(const char * n, int f, int t, int num):Room(n,f){
        if(t==1) {
                this->type=CoordinatorOffice;
        }
        else if(t==2) {
                this->type=StandardOffice;
        }
        else if(t==3) {
                this->type=SharedOfficeFor2People;
        }
        else if(t==4) {
                this->type=SharedOfficeFor3People;
        }
        else if(t==5){
                this->type=SharedOfficeFor10People;
        }
        this->NumOfPeople=num;
}

int Office::getOfficeType() {
        return this->type;
}
void Office::setOfficeType(officeType a) {
        this->type=a;
}
bool Office::isFull() {
        if(this->NumOfPeople==this->getCapacity()) {
                return true;
        }

        return false;


}
int Office::getCapacity() {
        if(this->type==None) {
                return 0;
        }
        if(this->type==CoordinatorOffice) {
                return 1;
        }if(this->type==StandardOffice) {
                return 1;
        }if(this->type==SharedOfficeFor2People) {
                return 2;
        }if(this->type==SharedOfficeFor3People) {
                return 3;
        }if(this->type==SharedOfficeFor10People) {
                return 10;
        }

}
void Office::printRoom() {
        cout<<endl<<"Office name ="<<this->name<<endl;
        cout<<"Office floor number ="<<this->floorNO<<endl;
        if(type==1) {
                cout<<"Office type ="<<"CoordinatorOffice"<<endl;
        }
        else if(type==2) {
                cout<<"Office type ="<<"StandardOffice"<<endl;
        }
        else if(type==3) {
                cout<<"Office type ="<<"SharedOfficeFor2People"<<endl;
        }else if(type==4) {
                cout<<"Office type ="<<"SharedOfficeFor3People"<<endl;
        }else if (type==5) {
                cout<<"Office type ="<<"SharedOfficeFor10People"<<endl;
        }
        cout<<"Number of people in office = "<<this->NumOfPeople<<endl;
        cout<<"Office capacity = "<<this->getCapacity()<<endl;
        if(isFull()==true) {
                cout<<"Office is full"<<endl<<endl;
        }
        else {
                cout<<"Office is not full"<<endl<<endl;
        }


}
Office::Office(const Office &o) {
        this->name=new char[strlen(o.name)+1];
        strcpy(this->name,o.name);
        this->floorNO=o.floorNO;
        this->type=o.type;
        this->NumOfPeople=o.NumOfPeople;

}
void Office::operator=(const Office &o) {
        delete[]this->name;
        this->name=new char[strlen(o.name)+1];
        strcpy(this->name,o.name);
        this->floorNO=o.floorNO;
        this->type=o.type;
        this->NumOfPeople=o.NumOfPeople;
}
int Office::GetROOMtype() {
        return 2;
}
Office::~Office() {
        delete[]this->name;
}
