#ifndef UNDERAGEEXCEPTION_H
#define UNDERAGEEXCEPTION_H

#include "KPFLExceptions.h"

class UnderageException : public KPFLExceptions
{
public:
    UnderageException()
        : KPFLExceptions("Player age is below the league minimum.") {}
};

#endif