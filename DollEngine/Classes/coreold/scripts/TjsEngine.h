//
//  TjsEngine.h
//  DollEngine
//
//  Created by DollStudio on 15/6/20.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__TjsEngine__
#define __DollEngine__TjsEngine__

#include "ScriptEngine.h"

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

class TjsEngine : public ScriptEngine
{
public:
    TjsEngine();
    static TjsEngine* GetSelf();
    static TJS::tTJS* Global();
    virtual bool eval(const wstring& code,void* ret);
    virtual bool exec(const wstring& code,void* ret);
    virtual void catchError(void* error);
    void doAsyncFunctions();
    void addAsyncFunction(const AsyncFunction& func);
    void print(const wstring& text);
    void setConsoleVisible(bool v);
    bool getConsoleVisible();
protected:
    vector<AsyncFunction> m_allAsyncFunctions;
};

DE_END

#endif /* defined(__DollEngine__TjsEngine__) */
