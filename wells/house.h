#ifndef HOUSE_H
#define HOUSE_H
#include <string>

class House
{
private:
    int x;//coordinate
    int y;//coordinate
    std::string tag;

public:
    House(int x, int y, std::string tag);
    int getX() const;
    void setX(int value);
    int getY() const;
    void setY(int value);
    std::string getTag() const;
    void setTag(const std::string &value);
};

#endif // HOUSE_H
