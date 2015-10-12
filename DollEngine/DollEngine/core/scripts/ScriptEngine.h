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

struct AsyncFunction
{
    int priority;
    TJS::iTJSDispatch2* objthis;
    TJS::tTJSInterCodeContext* handler;
};

enum DEBUG_MSG
{
    ERROR_NONE = 0,
    
    ERROR_IMAGE_LOAD_FAILD = 1001,
    ERROR_FILE_NOT_EXIST = 1002,
    ERROR_ADDFONT_FAILD = 1003,
    
    ERROR_OPENGL_ERROR = 4001,
    
    ERROR_KAG_UNKONW = 6000,
    ERROR_KAG_LABELKEY_NULL,
    ERROR_KAG_VALUE_STRING_ENDED,
    ERROR_KAG_TAG_ENDED,
    ERROR_KAG_LABEL_FIND_FAIL,
    ERROR_KAG_TAG_FIND_FAIL,
    ERROR_KAG_TOO_MANY_RETURN,
    ERROR_KAG_MACRONAME_EMPTY,
    ERROR_KAG_MACRO_NESTING,
    ERROR_KAG_IF_FAIL,
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
    void log(const String& text);
    void throwMsg(const String& v);
    void throwMsg(DEBUG_MSG msg,const String& v1);
    void throwMsg(DEBUG_MSG msg,int v1,const String& v2);
    void setConsoleVisible(bool v);
    bool getConsoleVisible();
    
    String topFile(){return m_fileStack.top();}
    void pushFile(const String& path)
    {
        m_fileStack.push(path);
    }
    
    void popFile()
    {
        m_fileStack.pop();
    }
    
protected:
    vector<AsyncFunction> m_allAsyncFunctions;
    stack<String> m_fileStack;
};

DE_END

#endif /* defined(__DollEngine__ScriptEngine__) */
