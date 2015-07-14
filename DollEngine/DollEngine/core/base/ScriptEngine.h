//
//  ScriptEngine.h
//  DollEngine
//
//  Created by DollStudio on 15/6/20.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef DollEngine_ScriptEngine_h
#define DollEngine_ScriptEngine_h

#include "CoreUnits.h"

DE_BEGIN

class ScriptEngine
{
public:
    static ScriptEngine* Engine;
    static ScriptEngine* GetInstance(){
        return ScriptEngine::Engine;
    }
    virtual bool eval(const wstring& code,void* ret){return false;}
    virtual bool exec(const wstring& code,void* ret){return false;}
};

DE_END

#endif
