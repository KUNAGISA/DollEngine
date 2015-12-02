//
//  ScriptEngine.h
//  DollEngine
//
//  Created by DollStudio on 15/6/20.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__ScriptEngine__
#define __DollEngine__ScriptEngine__

#include "CoreTypes.h"

namespace TJS{
    class tTJS;
    class tTJSInterCodeContext;
    class iTJSDispatch2;
}

DE_BEGIN

class DE_TJSTextReadStream : public iTJSTextReadStream
{
public:
    String path;
    String mode;
    virtual tjs_uint TJS_INTF_METHOD Read(tTJSString & targ, tjs_uint size) {
        DE::String str;
        str.loadFromFile(path);
        targ = str.c_str();
    }
    virtual void TJS_INTF_METHOD Destruct(){delete this;}
};

class DE_TJSTextWriteStream : public iTJSTextWriteStream
{
public:
    String path;
    String str;
    String mode;
    virtual void TJS_INTF_METHOD Write(const tTJSString & targ);
    virtual void TJS_INTF_METHOD Destruct();
};

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
    virtual bool eval(const String& code,void* ret);
    virtual bool exec(const String& code,void* ret);
    virtual void catchError(void* error);
    void doAsyncFunctions();
    void addAsyncFunction(const AsyncFunction& func);
    
    String topFile(){return m_fileStack.top();}
    void pushFile(const String& path)
    {
        m_fileStack.push(path);
    }
    
    void popFile()
    {
        m_fileStack.pop();
    }
    
    void clearFile()
    {
        while(!m_fileStack.empty()) {
            m_fileStack.pop();
        }
    }
protected:
    vector<AsyncFunction> m_allAsyncFunctions;
    stack<String> m_fileStack;
};

DE_END

#endif /* defined(__DollEngine__ScriptEngine__) */
