//
//  ScriptEngine.h
//  DollEngine
//
//  Created by DollStudio on 15/6/20.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__ScriptEngine__
#define __DollEngine__ScriptEngine__

#include "CoreUnits.h"

namespace TJS{
    class tTJS;
    class tTJSInterCodeContext;
    class iTJSDispatch2;
}

DE_BEGIN

struct AsyncFunction
{
    int priority;
    TJS::iTJSDispatch2* objthis;
    TJS::tTJSInterCodeContext* handler;
};

class ScriptEngine
{
public:
    ScriptEngine();
    Shared(ScriptEngine)
    static TJS::tTJS* Global();
    virtual bool eval(const wstring& code,void* ret);
    virtual bool exec(const wstring& code,void* ret);
    virtual void catchError(void* error);
    void doAsyncFunctions();
    void addAsyncFunction(const AsyncFunction& func);
    void print(const wstring& text);
    void setConsoleVisible(bool v);
    bool getConsoleVisible();
    
    string topFile(){return m_fileStack.top();}
    void pushFile(const string& path)
    {
        m_fileStack.push(path);
    }
    
    void popFile()
    {
        m_fileStack.pop();
    }
    
protected:
    vector<AsyncFunction> m_allAsyncFunctions;
    stack<string> m_fileStack;
};

DE_END

#endif /* defined(__DollEngine__ScriptEngine__) */
