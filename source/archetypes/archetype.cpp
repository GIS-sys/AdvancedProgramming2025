#include "archetype.h"

static int counter = 0;

int Archetype::getNextCounter()
{
    return counter++;
}
