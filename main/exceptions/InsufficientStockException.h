#ifndef INSUFFICIENTSTOCKEXCEPTION_H
#define INSUFFICIENTSTOCKEXCEPTION_H

#include "KPFLExceptions.h"

class InsufficientStockException : public KPFLExceptions
{
public:
    InsufficientStockException()
        : KPFLExceptions("Requested quantity exceeds available stock.") {}
};

#endif