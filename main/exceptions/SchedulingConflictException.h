#ifndef SCHEDULINGCONFLICTEXCEPTION_H
#define SCHEDULINGCONFLICTEXCEPTION_H

#include "KPFLExceptions.h"

class SchedulingConflictException : public KPFLExceptions
{
public:
    SchedulingConflictException()
        : KPFLExceptions("Team or official is already booked at that time.") {}
};

#endif