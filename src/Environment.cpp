#include "Environment.h"

Environment::Environment(float width, float height)
{
    d.width = width;
    d.height = height;
}

Environment::~Environment()
{

}

Dimension Environment::GetBoundaries()
{
    return d;
}

float Environment::GetWidth()
{
    return d.width;
}

float Environment::GetHeight()
{
    return d.height;
}

const Vector Environment::GetGlobalAcceleration()
{
    return GRAVITY;
}