/* Ali Ozkoca 2585271
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only */


#ifndef CLASSROOM_H
#define CLASSROOM_H
#include "Rooms.h"
class ClassRoom:public Room {
private:
    int Capacity;
public:
    ClassRoom();
    int getCapacity();
    void Setcapacity(int);
    ClassRoom(const ClassRoom &c);
    void operator=(const ClassRoom &r);
    ClassRoom(const char*,int,int);
    bool checkSuitability(int);
    void printRoom();
    int GetROOMtype();
    ~ClassRoom();

};

#endif //CLASSROOM_H
