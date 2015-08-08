//
//  KAGParser.h
//  DollEngine
//
//  Created by DollStudio on 15/8/8.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__KAGParser__
#define __DollEngine__KAGParser__

#include "KAGStorage.h"
#include "Timer.h"

DE_BEGIN

//struct KAGStack
//{
//    KAGStorage* storage;
//    wstring labelKey;
//    int tagIndex;
//};

class KAGParser
{
public:
    KAGParser();
    Shared(KAGParser)
    KAGStorage* loadScenario(const wstring& filepath);
    void clearScenario();
    KAGLabel* startMacro(const wstring& name);
    void pushMacro(KAGTag* tag);
    void endMacro();
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
    kagchar* containText(kagchar* text, const kagchar* data,bool is_end);
    void createStorage(const wstring& file,const wstring& fullpath);
    void createLabel(const wstring& key,const wstring& name);
    void createTag(const wstring& name);
protected:
    int m_errorLine;
    map<wstring,KAGStorage*> m_allStorage;
    KAGStorage* m_macros;
    
    KAGStorage* m_storage;
    KAGLabel* m_label;
    KAGTag* m_tag;
    KAGLabel* m_curMacroLabel;
    bool m_isScripts;
    int m_parseLine;
    DEBUG_MSG m_errorInfo;
    
    friend class KAGStorage;
    friend class KAGLabel;
    friend class KAGTag;
    
};

DE_END


#endif /* defined(__DollEngine__KAGParser__) */
