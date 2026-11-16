#ifndef INSUFFICIENTPAYMENTEXCEPTION_H
#define INSUFFICIENTPAYMENTEXCEPTION_H

#include "KPFLExceptions.h"

class InsufficientPaymentException : public KPFLExceptions
{
public:
    InsufficientPaymentException()
        : KPFLExceptions("Payment is less than the total amount due.") {}
};

#endif