#include "Scheduler.h"

DE_BEGIN

Scheduler::Scheduler()
{
    
}

Scheduler::~Scheduler()
{
    
}

void Scheduler::addCom(ComObject* obj)
{
    m_allComs.insert(obj);
}

void Scheduler::removeCom(ComObject* obj)
{
    m_allComs.remove(obj);
}

DE_END
