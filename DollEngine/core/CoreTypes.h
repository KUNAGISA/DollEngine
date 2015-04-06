#ifndef CORETYPES_H
#define CORETYPES_H

#include "Macros.h"
#include "Debug.h"

DE_BEGIN

struct GradientColor
{
    quint32 begin;
    quint32 end;
    void reset() 
    {
        begin = 0xffffffff;
        end = begin;
    }
};

static QRect RectZero=QRect(0,0,0,0);

DE_END
        
#endif // CORETYPES_H
