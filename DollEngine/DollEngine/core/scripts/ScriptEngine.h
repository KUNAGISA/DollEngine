//
//  ScriptEngine.h
//  DollEngine
//
//  Created by DollStudio on 15/6/20.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef DollEngine_ScriptEngine_h
#define DollEngine_ScriptEngine_h

#include "Units.h"

DE_BEGIN

class ScriptEngine
{
public:
    virtual bool eval(const wstring& code,void* ret)=0;
    virtual bool exec(const wstring& code,void* ret)=0;
};

DE_END

#endif
