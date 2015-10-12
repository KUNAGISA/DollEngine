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
#include "Console.h"

DE_BEGIN

//struct KAGStack
//{
//    KAGStorage* storage;
//    String labelKey;
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
    KAGStorage* loadScenario(const String& filepath);
    void clearScenario();
    KAGLabel* startMacro(const String& name);
    void pushMacro(KAGTag* tag);
    void endMacro();
protected:
    wchar_t* parseLine(wchar_t* text,bool is_scripts);
    wchar_t* parseLabel(wchar_t* text);
    wchar_t* parseTagAt(wchar_t* text);
    wchar_t* parseTag(wchar_t* text,bool is_at);
    wchar_t* parseTagName(wchar_t* text,bool is_at);
    wchar_t* parseTagParamKey(wchar_t* text,bool is_at);
    wchar_t* parseTagParamValue(wchar_t* text,bool is_at,String& value,bool& entity,bool& macroarg);
    wchar_t* parseEmpty(wchar_t* text);
    wchar_t* parseString(wchar_t* text,String& str,bool& entity);
    wchar_t* parseCh(wchar_t* text);
protected:
    wchar_t* containText(wchar_t* text, const wchar_t* data,bool is_end);
    void createStorage(const String& file,const String& fullpath);
    void createLabel(const String& key,const String& name);
    void createTag(const String& name);
protected:
    int m_errorLine;
    map<String,KAGStorage*> m_allStorage;
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
