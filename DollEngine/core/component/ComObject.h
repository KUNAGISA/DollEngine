#ifndef COMOBJECT_H
#define COMOBJECT_H

#include "CoreTypes.h"

DE_BEGIN

class ComObject
{
public:
    ComObject();
    ~ComObject();
    
    PROPERTY(bool, Enabled, m_enabled){m_enabled=v;}
    PROPERTY(int, Interval,m_interval){m_interval=v;}
    PROPERTY_CONST(QString, Name,m_name){m_name=v;}
    void startUpdate(int interval=0);
    void stopUpdate();
    
    void update(float dt);
};

DE_END

#endif // COMOBJECT_H
