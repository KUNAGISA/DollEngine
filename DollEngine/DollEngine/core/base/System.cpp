//
//  DESystem.cpp
//  DECore
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "System.h"
#include "Storages.h"
#include "FontInterface.h"
#include "GLCanvas.h"
#include "Character.h"
#include "ScriptEngine.h"
#include "Window.h"
#include "System.h"
#include "IOData.h"
#include "TjsBind.h"

DE_BEGIN

bool System::NeedRedraw=true;
bool System::NeedSortTouches=true;


System::~System()
{
}

void System::startup()
{
    System::GetInstance();
    ScriptEngine::GetInstance();
    try{
        FontInterface::GetInstance()->addFont("WenQuanYiMicroHei.ttc");
        
        String code;
        code.loadFromFile("startup.tjs");
        ScriptEngine::GetInstance()->pushFile("【GLOBAL】");
        ScriptEngine::GetInstance()->pushFile("startup.tjs");
        ScriptEngine::GetInstance()->exec(code, NULL);
        ScriptEngine::GetInstance()->popFile();
        
    }
    TJS_CATCH
}

int64_t System::getMilliSeconds()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

double System::getSeconds()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec/1000000.0f;
}

void System::setDebugMode(int v)
{
    m_debugMode = v;
}


DE_END
