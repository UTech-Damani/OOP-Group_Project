#ifndef INVALIDSCOREEXCEPTION_H
#define INVALIDSCOREEXCEPTION_H

#include "KPFLExceptions.h"

class InvalidScoreException : public KPFLExceptions
{
public:
    InvalidScoreException()
        : KPFLExceptions("Score or quantity cannot be negative.") {}
};

#endif