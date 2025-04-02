/* Ali Ozkoca 2585271
I read and accept the submission rules and the extra rules specified in each
question. This is my own work that is done by myself only */


#ifndef ROOMS_H
#define ROOMS_H


class Room {
protected:
    char * name;
    int floorNO;
public:
    Room();
    Room(const char*,int);
    char * getterNAme();
    char  setterName(const char*);
    int getterNO();
    int setterNO(int);
    virtual int GetROOMtype(){};
    virtual int getCapacity(){};
    virtual void printRoom();
    virtual bool isFull(){};
    virtual bool checkSuitability(int){};
    Room(const Room &r);
    void operator=(const Room &r);
    virtual ~Room();

};



#endif //ROOMS_H
