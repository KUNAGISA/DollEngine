#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "CoreTypes.h"
#include "ComObject.h"

DE_BEGIN


class Scheduler
{
public:
    Scheduler();
    ~Scheduler();
    Shared(Scheduler)
    
    void addCom(ComObject* obj);
    void removeCom(ComObject* obj);
protected:
    QSet<ComObject*> m_allComs;
};

DE_END
#endif // SCHEDULER_H
