#ifndef WELL_H
#define WELL_H
#include <string>
#include <house.h>
#include <math.h>
#include <list>
#include <algorithm>

class Well
{
private:
    int x;//coordinate
    int y;//coordinate
    int connectionLimit;
    int connectionCount;
    double weight = 0;
    std::string tag;
    // std::list<House> connections;
    std::list<House*> *connections;
public:
    Well(int x, int y, std::string tag, int connectionLimit);
    int getX() const;
    void setX(int value);
    int getY() const;
    void setY(int value);
    std::string getTag() const;
    void setTag(const std::string &value);
    bool connect(House *h);


    ~Well();
    std::list<House *> *getConnections() const;
};

#endif // WELL_H
