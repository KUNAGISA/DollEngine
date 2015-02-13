//
//  COM.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/11/9.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "COM.h"
#include "Object.h"
#include "COMManager.h"
#include "TouchEvent.h"

COM::COM()
:m_object(null)
,m_autoRelease(false)
,m_time(0)
,m_iter(COMManager::GetInstance()->end())
,m_enabled(false)
,m_triggerType(COM::TRIGGER_NONE)
{
    setComName(L"COM");
}

COM::~COM()
{
    setEnabled(false);
}

COM* COM::clone()
{
    COM* ret = new COM();
    ret->assign(this);
    return ret;
}

void COM::assign(COM* src)
{
    setComName(src->getComName());
    setTriggerType(src->getTriggerType());
    setEnabled(src->getEnabled());
}

void COM::release()
{
    if (!m_autoRelease)
    {
        setObject(null);
        setEnabled(false);
        setAutoRelease(true);
        COMManager::GetInstance()->addRelease(this);
    }
}

void COM::setEnabled( bool v)
{
    if (m_enabled != v)
    {
        m_enabled = v;
        if (v)
        {
            switch (m_triggerType)
            {
                case TRIGGER_UPDATE:
                    COMManager::GetInstance()->addUpdate(this);
                    break;
                case TRIGGER_TOUCH:
                {
                    auto obj = dynamic_cast<TouchEvent*>(this);
                    ASSERT(obj);
                    COMManager::GetInstance()->addTouch(obj);
                }
                default:
                    break;
            }
        }
        else
        {
            switch (m_triggerType)
            {
                case TRIGGER_UPDATE:
                    COMManager::GetInstance()->removeUpdate(this);
                    break;
                case TRIGGER_TOUCH:
                {
                    auto obj = dynamic_cast<TouchEvent*>(this);
                    ASSERT(obj);
                    COMManager::GetInstance()->removeTouch(obj);
                }
                    break;
                default:
                    break;
            }
        }
        System::GetInstance()->setTransChanged(true);
        System::GetInstance()->setOrderChanged(true);
    }
}

