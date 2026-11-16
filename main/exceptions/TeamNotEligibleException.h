#ifndef TEAMNOTELIGIBLEEXCEPTION_H
#define TEAMNOTELIGIBLEEXCEPTION_H

#include "KPFLExceptions.h"

class TeamNotEligibleException : public KPFLExceptions
{
public:
    TeamNotEligibleException()
        : KPFLExceptions("Unregistered or suspended team assigned to fixture.") {}
};

#endif