//
//  Scripts.h
//  Krkr_GL
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__Scripts__
#define __Krkr_GL__Scripts__

#include "Functions.h"

#define SCRIPT_TYPE_TJS2 1
#define SCRIPT_TYPE_LUA 2

#define SCRIPT_TYPE SCRIPT_TYPE_TJS2

class Scripts
{
public:
    Scripts();
    virtual ~Scripts(){}
    static Scripts* GetInstance();
    static void Delloc();
public:
    virtual void releaseScriptID(long _id)=0;
    virtual void init()=0;
    virtual int exec(const wchar_t* code)=0;
    virtual int eval(const wchar_t* code)=0;
    virtual int execStorage(const char* filepath)=0;
    void pushFile(const wstring& file){m_fileNames.push(file);}
    void popFile(){m_fileNames.pop();}
    wstring getFile(){
        if (m_fileNames.size() == 0) {
            return L"global";
        }
        return m_fileNames.top();
    }
protected:
    stack<wstring> m_fileNames;
};

#endif /* defined(__Krkr_GL__Scripts__) */
