//
//  ScriptsTJS.h
//  DollEngine
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__ScriptsTJS__
#define __DollEngine__ScriptsTJS__

#include "Scripts.h"
#include "tjs.h"

class TJSTextReadStream;
extern iTJSDispatch2* TVPGetScriptDispatch();
extern void TVPThrowExceptionMessage(const tjs_char*);
extern void TVPThrowExceptionMessage(const tjs_char*, const ttstr&);
extern void TVPThrowExceptionMessage(const tjs_char*, const ttstr&, tjs_int);
extern void TVPThrowExceptionMessage(const tjs_char*, const ttstr&, const ttstr&);
extern void TVPExecuteExpression(const ttstr & , tTJSVariant*);

class ScriptsTJS : public Scripts
{
public:
    ScriptsTJS();
    ~ScriptsTJS();
    virtual void releaseScriptID(long _id);
    virtual void init();
    virtual int exec(const wchar_t* code);
    virtual int eval(const wchar_t* code);
    virtual int execStorage(const char* filePath);
    
    static tTJS* GetTjs();
private:
    tTJS* m_tjs;
};

#endif /* defined(__DollEngine__ScriptsTJS__) */
