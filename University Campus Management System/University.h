/* Ali Ozkoca 2585271
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only */


#ifndef UNIVERSITY_H
#define UNIVERSITY_H
#include"Building.h"
class University {
private:
    char * UniversityName;
    Building *buildings[20];
    int NumberOFbuilding;
public:
    University();
    University(const char*);
    University(const University &u);
    void operator=(const University &u);
    void setUniversityName(const char*);
    char * getUniversityName();
    int getNumberOFbuilding();
    void addBuilding(const char *,int);
    void printBuildings();
    void printRooms();
    void printRoomsByType(int);
    void printRoomTypeStatistics();
    void printAvailableOffices();
    void printTotalCapacityOfOffices();
    void printSuitableClassrooms(int);
    void addRoom(int,int,const char *,int,int,int);
    ~University();


};
#endif //UNIVERSITY_H
