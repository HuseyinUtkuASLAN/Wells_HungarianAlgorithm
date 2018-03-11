#include "well.h"

int Well::getX() const
{
    return x;
}

void Well::setX(int value)
{
    x = value;
}

int Well::getY() const
{
    return y;
}

void Well::setY(int value)
{
    y = value;
}

std::string Well::getTag() const
{
    return tag;
}

void Well::setTag(const std::string &value)
{
    tag = value;
}

bool Well::connect(House *h)
{
    if(this->connectionCount + 1 > this->connectionLimit){
        return false;
    }

    // distance
    int hX = h->getX();
    int hY = h->getY();

    double distance = sqrt(pow(hX - x,2) + pow(hY - y,2));

    weight += distance;

    connectionCount ++;

    this->connections->push_back(h);

    return true;

}


Well::~Well()
{
    //delete(this->connections);
}

std::list<House *> *Well::getConnections() const
{
    return connections;
}

Well::Well(int x, int y, std::string tag, int connectionLimit)
{
    this->setX(x);
    this->setY(y);
    this->setTag(tag);
    this->connectionLimit = connectionLimit;
    this->connections = new std::list<House*>();
    // House *h = new House(1,2,"hello");
    // this->connections->push_back(h);
}
