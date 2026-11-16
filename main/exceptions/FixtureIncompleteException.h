#ifndef FIXTUREINCOMPLETEEXCEPTION_H
#define FIXTUREINCOMPLETEEXCEPTION_H

#include "KPFLExceptions.h"

class FixtureIncompleteException : public KPFLExceptions
{
public:
    FixtureIncompleteException()
        : KPFLExceptions("Fixture cannot be completed without a valid result.") {}
};

#endif