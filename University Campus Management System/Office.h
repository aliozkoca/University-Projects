
/* Ali Ozkoca 2585271
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only */

#ifndef OFFICE_H
#define OFFICE_H
#include"Rooms.h"
class Office:public  Room {
private:
    enum officeType {None, CoordinatorOffice, StandardOffice,
                SharedOfficeFor2People, SharedOfficeFor3People, SharedOfficeFor10People};
    officeType type;
    int NumOfPeople;
public:
    Office();
    Office(const char*,int,int,int);
    int getOfficeType();
    void setOfficeType(officeType);
    bool isFull();
    int getCapacity();
    void printRoom();
    int GetROOMtype();
    Office(const Office &o);
    void operator=(const Office &o);
    ~Office();
    friend class Building;
};

#endif //OFFICE_H
