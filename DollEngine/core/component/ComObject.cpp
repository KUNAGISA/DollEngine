#include "ComObject.h"
#include "Scheduler.h"

DE_BEGIN

ComObject::ComObject()
    :m_interval(0)
    ,m_enabled(false)
    ,m_name("ComObject")
{
    
}

ComObject::~ComObject()
{
    stopUpdate();
}

void ComObject::startUpdate(int interval)
{
    Scheduler::GetInstance()->addCom(this);
}

void ComObject::stopUpdate()
{
    Scheduler::GetInstance()->removeCom(this);
}

void ComObject::update(float dt)
{
    
}

DE_END
