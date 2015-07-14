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
}

DE_BEGIN


class TjsEngine : public ScriptEngine
{
public:
    TjsEngine();
    static TjsEngine* GetSelf();
    static TJS::tTJS* Global();
    virtual bool eval(const wstring& code,void* ret);
    virtual bool exec(const wstring& code,void* ret);
    
    wstring topFile(){return m_fileStack.top();}
    void pushFile(const wstring& path);
    void popFile();
protected:
    stack<wstring> m_fileStack;
};

DE_END

#endif /* defined(__DollEngine__TjsEngine__) */
