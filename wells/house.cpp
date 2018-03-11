#include "house.h"

int House::getX() const
{
    return x;
}

void House::setX(int value)
{
    x = value;
}

int House::getY() const
{
    return y;
}

void House::setY(int value)
{
    y = value;
}

std::string House::getTag() const
{
    return tag;
}

void House::setTag(const std::string &value)
{
    tag = value;
}

House::House(int x, int y, std::string tag)
{
    this->setX(x);
    this->setY(y);
    this->setTag(tag);
}
