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
    virtual void catchError(void* error){}
    virtual void addAsyncScripts(const wstring& code){
        m_asyncScripts += code;
        if (code.back() != L';') {
            m_asyncScripts.push_back(L';');
        }
    }
    virtual void evalAsyncScripts(){}
    virtual void print(const wstring& text){}
    
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
    stack<string> m_fileStack;
    wstring m_asyncScripts;
};

DE_END

#endif
