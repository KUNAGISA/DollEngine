//
//  de-tjs-bind.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "TjsBind.h"
#include "ScriptEngine.h"

using namespace DE;

void TVPAddLog(const ttstr& var)
{
    ScriptEngine::Global()->OutputToConsole(var.c_str());
}

iTJSDispatch2* TVPGetScriptDispatch()
{
    ScriptEngine* engine = (ScriptEngine*)ScriptEngine::GetInstance();
    return engine->Global()->GetGlobal();
}

void TVPThrowExceptionMessage(const ttstr& var)
{
    
}

void TVPThrowExceptionMessage(const ttstr& var1,const ttstr& var2)
{
    
}

void TVPThrowExceptionMessage(const ttstr&, const ttstr&, tjs_int)
{
    
}

void TVPThrowExceptionMessage(const ttstr&, const ttstr&, const ttstr&)
{
    
}

void TVPThrowExceptionMessage(const tTJSMessageHolder&)
{
    
}

void TVPExecuteExpression(const ttstr& var1,void*)
{
    
}
