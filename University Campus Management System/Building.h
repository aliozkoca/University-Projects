/* Ali Ozkoca 2585271
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only */


#ifndef BUILDING_H
#define BUILDING_H
#include "Rooms.h"


class Building {
private:
    char * buildingNAME;
    int Size;//m^2
    Room *rooms[100];
    int numOFroom;
public:
    Building();
    Building(const char*,int);
    Building(const Building &b);
    void operator=(const Building &b);
    char *getBuildingName();
    void setBuildingName(const char*);
    int getBuildingsize();
    void setbuildingsize(int);
    int getNumOFroom();
    void addRoom(int,const char *,int,int,int);
    void printBuilding();
    void printRooms();
    void printRoomsByType(int);
    int getNumberOfClassrooms();
    int getTotalCapacity();
    int getNumberOfOffices();
    void printAvailableOffices();
    void printSuitableClassrooms(int);
    ~Building();

};

#endif //BUILDING_H
