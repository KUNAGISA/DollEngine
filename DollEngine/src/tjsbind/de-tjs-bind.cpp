//
//  de-tjs-bind.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-tjs-bind.h"

void TVPAddLog(const ttstr& var)
{
    DM("%ls",var.AsStdString().c_str());
}

iTJSDispatch2* TVPGetScriptDispatch()
{
    return (iTJSDispatch2*)de::script::script_global();
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

deTJSClass::deTJSClass()
:_self(null)
{
    
}

deTJSClass::~deTJSClass()
{
    
}
