#ifndef SYSTEMDELEGATE_H
#define SYSTEMDELEGATE_H

#include "CoreTypes.h"

DE_BEGIN

class SystemDelegate
{
public:
    SystemDelegate();
    
    virtual void onMainLoop(){}
    
    virtual void onMouseDown(float x,float y){}
    virtual void onMouseUp(float x,float y){}
    virtual void onMouseMove(float x,float y){}
    virtual void onClick(float x,float y){}

};

DE_END

#endif // SYSTEMDELEGATE_H
