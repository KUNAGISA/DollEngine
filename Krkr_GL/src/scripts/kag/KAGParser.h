//
//  KAGParser.h
//  Krkr_GL
//
//  Created by DollStudio on 14/11/14.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__KAGParser__
#define __Krkr_GL__KAGParser__

#include "KAGData.h"
#include "COM.h"

class KAGParser : public COM
{
public:
    KAGParser();
    virtual ~KAGParser();
    virtual void jumpTo(const wstring& filepath,const wstring& key=L"_def_");
    virtual void wait(float time);
    virtual void doNext();//立刻执行下一个
    virtual void onScenarioEnded(){}
    virtual KAGStorage* loadScenario(const wstring& filepath);
    virtual void callLabel(const wstring& filepath, const wstring& key);
    virtual void clearCallStack();
    virtual void returnCall();
    virtual bool callMacro(const wstring& name);
    virtual void trigger();
    virtual int execute(KAGTag* tag);
    PROPERTY(float, WaitTime, m_waitTime){m_waitTime=v;}
    PROPERTY(bool, IsProcessed, m_isProcssed){m_isProcssed=v;}
    PROPERTY(bool, IsMakeMacro, m_isMakeMacro){m_isMakeMacro=v;}
protected:
    kagchar* parseLine(kagchar* text,bool is_scripts);
    kagchar* parseLabel(kagchar* text);
    kagchar* parseTagAt(kagchar* text);
    kagchar* parseTag(kagchar* text,bool is_at);
    kagchar* parseTagName(kagchar* text,bool is_at);
    kagchar* parseTagParamKey(kagchar* text,bool is_at);
    kagchar* parseTagParamValue(kagchar* text,bool is_at,wstring& value,bool& entity,bool& macroarg);
    kagchar* parseEmpty(kagchar* text);
    kagchar* parseString(kagchar* text,wstring& str,bool& entity);
    kagchar* parseCh(kagchar* text);
protected:
    kagchar* containText(kagchar* text, const wchar_t* data,bool is_end);
protected:
    void createStorage(const wstring& file,const wstring& fullpath);
    void createLabel(const wstring& key,const wstring& name);
    void createTag(const wstring& name);
protected:
    int m_errorLine;
    vector<KAGStack> m_callStack;
    map<wstring,KAGStorage*> m_allStorage;
    KAGStorage* m_macros;
    KAGStack m_nextKAG;
    
    KAGStorage* m_currentStorage;
    wstring m_currentLabelKey;
    int m_currentTagIndex;
    int m_currentLine;
    
    KAGStorage* m_storage;
    KAGLabel* m_label;
    KAGTag* m_tag;
    bool m_isScripts;
    int m_parseLine;
    TEXT_ENCODING m_encoding;
    ERROR_INFOS m_errorInfo;
    
    friend class KAGStorage;
    friend class KAGLabel;
    friend class KAGTag;
    
};

#endif /* defined(__Krkr_GL__KAGParser__) */
