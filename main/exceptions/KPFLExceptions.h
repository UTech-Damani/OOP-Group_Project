#ifndef KPFLEXCEPTIONS_H
#define KPFLEXCEPTIONS_H

#include <iostream>
#include <string>

using namespace std;

class KPFLExceptions
{
    protected:
        string message;

    public:
        KPFLExceptions(string msg){
            message = msg;
        }
        virtual ~KPFLExceptions() = default;

        virtual string getMessage() const{
            return message;
        }
};



#endif



