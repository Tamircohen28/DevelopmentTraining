#pragma once
using namespace std;
#include "bird.h"

class Pigeon : public Bird
{
private:
    string m_color; 
    bool m_loves_bread;
 
public:
    Pigeon(string color, bool loves_bread, bool flying);
    
    string get_color();
    void set_color(string color);

    bool get_bread();
    void set_bread(bool loves_bread);
};