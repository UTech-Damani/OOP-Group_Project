#ifndef DUPLICATEREGISTRATIONEXCEPTION_H
#define DUPLICATEREGISTRATIONEXCEPTION_H

#include "KPFLExceptions.h"

class DuplicateRegistrationException : public KPFLExceptions
{
    public:
        DuplicateRegistrationException()
            : KPFLExceptions("A team registration number or name already exists.") {
            }

};

#endif