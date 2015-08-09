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

//enum DEBUG_MSG
//{   
//    ERROR_KAG_UNKONW = 6000, //KAG解析发生未知错误
//    ERROR_KAG_LABELKEY_NULL, //标签的名字不能为空
//    ERROR_KAG_VALUE_STRING_ENDED, //字符串没有结尾，可能缺少 \" 或 \' ，请检查
//    ERROR_KAG_TAG_ENDED, //Tag没有结尾，可能缺少 ] ，请检查
//    ERROR_KAG_LABEL_FIND_FAIL, //未找到名为%ls的标签
//    ERROR_KAG_TAG_FIND_FAIL, //未找到名为%ls的指令
//    ERROR_KAG_TOO_MANY_RETURN, //过多的Return指令，与Call指令无法形成对应
//    ERROR_KAG_MACRONAME_EMPTY, //Macro的name属性为空
//    ERROR_KAG_MACRO_NESTING, //Macro不可嵌套
//    ERROR_KAG_IF_FAIL, //if、elsif、else、endif不对应
//}

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
