#ifndef DATAFILEEXCEPTION_H
#define DATAFILEEXCEPTION_H

#include "KPFLExceptions.h"

class DataFileException : public KPFLExceptions
{
public:
    DataFileException()
        : KPFLExceptions("Data file is missing or malformed.") {}
};

#endif