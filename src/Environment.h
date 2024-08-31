#ifndef ENVIRONMENT
#define ENVIRONMENT

#include "constants.h"

class Environment
{
    public:
        Environment(float width, float height);
        ~Environment();
        Dimension GetBoundaries();
        float GetWidth();
        float GetHeight();

    private:
        Dimension d;

};


#endif // ENVIRONMENT