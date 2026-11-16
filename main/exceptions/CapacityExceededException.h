#ifndef CAPACITYEXCEEDEDEXCEPTION_H
#define CAPACITYEXCEEDEDEXCEPTION_H

#include "KPFLExceptions.h"

class CapacityExceededException : public KPFLExceptions
{
public:
    CapacityExceededException()
        : KPFLExceptions("Ticket sales exceed stadium capacity.") {}
};

#endif