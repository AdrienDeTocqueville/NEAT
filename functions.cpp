#include "functions.h"
#include <sstream>

std::string toString(int _number)
{
    std::stringstream os;
    os << _number;

    return os.str();
}

std::string toStringF(float _number)
{
    std::stringstream os;
    os << _number;

    return os.str();
}

float random(float _min, float _max)
{
    return _min +  rand() / (RAND_MAX/(_max-_min));
}

int randomInt(int _min, int _max)
{
    return _min + (rand() % static_cast<int>(_max - _min + 1));
}