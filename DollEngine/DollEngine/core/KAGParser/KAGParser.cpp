//
//  KAGParser.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/8.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "KAGParser.h"
#include "Storages.h"

DE_BEGIN

KAGParser::KAGParser()
:m_errorLine(-1)
,m_storage(NULL)
,m_label(NULL)
,m_tag(NULL)
,m_isScripts(false)
,m_errorInfo(ERROR_NONE)
,m_parseLine(0)
,m_curMacroLabel(NULL)
{
    m_macros = new KAGStorage();
    m_macros->fileName = L"MACRO";
    m_macros->fullPath = L"MACRO";
    m_allStorage[L"MACRO"] = m_macros;
}

KAGStorage* KAGParser::loadScenario(const String& filepath)
{
    if (filepath == L"MACRO") {
        return m_macros;
    }
    String fullpath;
    if (filepath != L"MACRO")
    {
        fullpath = Storages::GetInstance()->getFullPath(filepath);
        if (fullpath.empty())
        {
            EM(ERROR_FILE_NOT_EXIST,filepath.c_nstr());
            return NULL;
        }
    }
    else
    {
        fullpath = L"MACRO";
    }
    auto storage_iter = m_allStorage.find(fullpath);
    if (storage_iter != m_allStorage.end())
    {
        return storage_iter->second;
    }
    String kagcode;
    if(!kagcode.loadFromFile(fullpath)){
        m_errorLine = -1;
        return NULL;
    }
    wchar_t* ntext = (wchar_t*)kagcode.c_str();
    
    m_errorLine=0;
    m_parseLine=1;
    m_isScripts=false;
    createStorage(filepath,fullpath);
    createLabel(L"_def_",L"");
    
    while (ntext)
    {
        ntext = parseLine(ntext,false);
        if (m_errorLine != 0)
        {
            SAFF_DELETE(m_storage);
            m_label = NULL;
            m_tag = NULL;
            EM(m_errorInfo,m_errorLine);
            break;
        }
    }
    auto ret = m_storage;
    m_storage = NULL;
    m_label = NULL;
    m_tag = NULL;
    if (m_errorLine == 0)
    {
        m_allStorage[fullpath] = ret;
        return ret;
    }
    else
    {
        return NULL;
    }
}

void KAGParser::clearScenario()
{
    for (auto iter = m_allStorage.begin();
         iter != m_allStorage.end(); ++iter) {
        delete iter->second;
    }
    m_allStorage.clear();
    delete m_macros;
    m_macros = new KAGStorage();
    m_macros->fileName = L"MACRO";
    m_macros->fullPath = L"MACRO";
    m_allStorage[L"MACRO"] = m_macros;
}

KAGLabel* KAGParser::startMacro(const String& name)
{
    KAGLabel* lb = m_macros->getLabel(name);
    if (lb) {
        delete lb;
    }
    lb = new KAGLabel();
    lb->key = name;
    lb->isMacro = true;
    lb->storage = m_macros;
    m_macros->addLabel(lb);
    m_curMacroLabel = lb;
    return lb;
}

void KAGParser::pushMacro(KAGTag* tag)
{
    m_curMacroLabel->addTag(tag);
    tag->label = m_curMacroLabel;
    tag->storage = m_macros;
}

void KAGParser::endMacro()
{
    m_curMacroLabel = NULL;
}
wchar_t* KAGParser::parseLine(wchar_t* text,bool is_scripts)
{
    bool _is_note = false;
    while (text && *text)//*text != '\0' && *text != '\n' && *text != '\r')
    {
        if (m_errorLine!=0) {
            return NULL;
        }
        if (*text == '\r' && *(text+1) != '\n')
        {
            *text = '\n';
        }
        else if (*text == '\r' && *(text+1) == '\n')
        {
            ++text;
        }
        if (*text == '\n')
        {
            ++m_parseLine;
        }
        if (is_scripts)
        {
            ASSERT(m_tag->name == L"iscript");
            wchar_t* ntext = containText(text, L"[endscript]",false);
            if (ntext == text)
            {
                ntext = containText(text, L"@endscript",true);
                if (ntext == text)
                {
                    if (m_tag->params.size()==0) {
                        m_tag->addParam(L"exp", L"");
                    }
                    m_tag->params[0].value.push_back(*text);
                    ++text;
                    continue;
                }
            }
            createTag(L"endscript");
            m_tag = NULL;
            is_scripts=false;
            text = ntext;
            continue;
        }
        if (_is_note)
        {
            if (*text == '\n')
            {
                return ++text;
            }
            ++text;
            continue;
        }
        switch (*text)
        {
            case '\0':
                return NULL;
                break;
            case '\n':
            case '\r':
                return ++text;
                break;
            case '*':
                return parseLabel(text);
                break;
            case '@':
                text = parseTagAt(text+1);
                break;
            case '[':
            {
                if (*(text+1) != '[') {
                    text = parseTag(text+1,false);
                }
                else
                {
                    text = parseCh(text+1);
                }
            }
                break;
            case ';':
            {
                _is_note = true;
                ++text;
            }
                break;
            default:
            {
                if(*text < 0x21)
                {
                    text = parseEmpty(text+1);
                }
                else
                {
                    text = parseCh(text);
                }
            }
                break;
        }
        if (m_tag&&m_tag->name == L"iscript")
        {
            is_scripts = true;
        }
    }
    return NULL;
}

wchar_t* KAGParser::parseLabel(wchar_t* text)
{
    wchar_t* ntext=text;
    ++ntext;
    ntext = parseEmpty(ntext);
    String key=L"*";
    String name;
    while (true)
    {
        if (*ntext < 0x21||
            *ntext == '|')
        {
            if (key == L"*")
            {
                m_errorInfo = ERROR_KAG_LABELKEY_NULL;
                m_errorLine = m_parseLine;
                return NULL;
            }
            break;
        }
        key.push_back(*ntext);
        ++ntext;
    }
    ntext = parseEmpty(ntext);
    if (*ntext == '|')
    {
        ++ntext;
        while (true)
        {
            if (*ntext < 0x21)
            {
                break;
            }
            name.push_back(*ntext);
            ++ntext;
        }
    }
    createLabel(key, name);
    return ntext;
}

wchar_t* KAGParser::parseTagAt(wchar_t* text)
{
    return parseTag(text,true);
}

wchar_t* KAGParser::parseTag(wchar_t* text,bool is_at)
{
    text = parseEmpty(text);
    wchar_t* ttext = parseTagName(text,is_at);
    if (!ttext) {
        return NULL;
    }
    String name;
    name.assign(text, ttext-text);
    createTag(name);
    text = ttext;
    String key,value;
    while (true)
    {
        key = L"",value=L"";
        text = parseEmpty(text);
        wchar_t* ntext = parseTagParamKey(text,is_at);
        if (ntext != text)
        {
            key.assign(text, ntext-text);
            text = ntext;
            text = parseEmpty(text);
            bool entity=false;
            bool macroarg = false;
            ntext = parseTagParamValue(text, is_at,value,entity,macroarg);
            if (ntext == NULL) {
                return ntext;
            }
            m_tag->addParam(key, value,entity,macroarg);
            text = ntext;
        }
        else
        {
            if(*ntext == ']') ++text;
            break;
        }
    }
    return text;
}

wchar_t* KAGParser::parseTagName(wchar_t* text,bool is_at)
{
    wchar_t* ntext = text;
    while (true)
    {
        if (is_at == false&&*ntext == ']')
        {
            return ntext;
        }
        if (*ntext < 0x21)
        {
            return ntext;
        }
        else
        {
            ++ntext;
        }
    }
}

wchar_t* KAGParser::parseTagParamKey(wchar_t* text,bool is_at)
{
    wchar_t* ntext = text;
    while (true)
    {
        if (*ntext < 0x21 || *ntext == '=' || *ntext == ']')
        {
            return ntext;
        }
        else
        {
            ++ntext;
        }
    }
}

wchar_t* KAGParser::parseTagParamValue(wchar_t* text,bool is_at,String& value,bool& entity,bool& macroarg)
{
    wchar_t* ntext = text;
    if (*ntext == '\0' || *ntext == '\n' || *ntext == '\r')
    {
        value = L"true";
        return text;
    }
    else if (*ntext == '=')
    {
        ++ntext;
        ntext = parseEmpty(ntext);
    }
    else
    {
        value = L"true";
        return text;
    }
    if (*ntext == '%') {
        macroarg = true;
    }
    if (*ntext == '&') {
        entity = true;
    }
    while (true)
    {
        if (*ntext == '\\') {
            value.push_back(*ntext);
            ++ntext;
            value.push_back(*ntext);
            ++ntext;
            continue;
        }
        if (*ntext == '\'' || *ntext == '"')
        {
            String str;
            ntext = parseString(ntext,str,entity);
            if (!ntext) {
                return NULL;
            }
            value.append(str);
            continue;
        }
        if (*ntext == '\0' || *ntext == '\n' || *ntext == '\r') {
            if (is_at) {
                if (value.size() == 0) value = L"true";
                return ntext;
            }
            else {
                m_errorInfo = ERROR_KAG_TAG_ENDED;
                m_errorLine = m_parseLine;
                return NULL;
            }
        }
        else if ((*ntext == ']' && !is_at) || *ntext < 0x21) {
            if (value.size() == 0) value = L"true";
            return ntext;
        }
        else {
            value.push_back(*ntext);
            ++ntext;
        }
    }
}

wchar_t* KAGParser::parseEmpty(wchar_t* text)
{
    while (true)
    {
        if (*text == '\0' || *text == '\n' || *text == '\r')
        {
            return text;
        }
        else if (*text < 0x21)
        {
            ++text;
            continue;
        }
        else
        {
            return text;
        }
    }
}

wchar_t* KAGParser::parseString(wchar_t* text,String& str,bool& entity)
{
    unsigned char start_ch = *text;
    str.push_back(*text);
    ++text;
    while (true)
    {
        if (*text == '\0' || *text == '\n' || *text == '\r')
        {
            m_errorInfo = ERROR_KAG_VALUE_STRING_ENDED;
            m_errorLine = m_parseLine;
            return NULL;
        }
        if (*text == '\\') {
            str.push_back(*text);
            ++text;
            str.push_back(*text);
            ++text;
            continue;
        }
        if (*text == '\'' || *text == '\"') {
            if (*text == start_ch) {
                str.push_back(*text);
                ++text;
                return text;
            }
            else {
                str.push_back(*text);
                ++text;
            }
        }
        else {
            str.push_back(*text);
            ++text;
        }
    }
}

wchar_t* KAGParser::parseCh(wchar_t* text)
{
    wchar_t* ntext = text;
    while (true)
    {
        if (*ntext >= 0x20)
        {
            if (*ntext == L'[') {
                if (*(ntext+1) != L'[') {
                    return ntext;
                }
                ntext++;
            }
            createTag(L"ch");
            String value;
            value.push_back(*ntext);
            m_tag->addParam(L"text", value);
        }
        else {
            return ntext;
        }
        ++ntext;
    }
}

wchar_t* KAGParser::containText(wchar_t* text, const wchar_t* data,bool is_end)
{
    size_t l = wcslen(data);
    for (size_t i=0; i<l; ++i) {
        if(*(text+i) != *(data+i))
            return text;
    }
    if (is_end)
    {
        if (*(text + l) < 0x21) {
            return text + l;
        }
        else
        {
            return text;
        }
    }
    return text + l;
}

void KAGParser::createStorage(const String& file,const String& fullpath)
{
    SAFF_DELETE(m_storage);
    m_storage = new KAGStorage();
    m_storage->fileName=file;
    m_storage->fullPath=fullpath;
    m_label=NULL;
    m_tag=NULL;
}

void KAGParser::createLabel(const String& key,const String& name)
{
    KAGLabel* lastLabel = m_label;
    m_label=new KAGLabel();
    m_label->key=key;
    m_storage->addLabel(m_label);
    m_label->name=name;
    m_label->storage = m_storage;
    if (lastLabel)
    {
        lastLabel->nextLabel = m_label;
    }
    m_tag = NULL;
}

void KAGParser::createTag(const String& name)
{
    m_tag = new KAGTag();
    m_tag->name=name;
    m_tag->line = m_parseLine;
    m_label->addTag(m_tag);
    m_tag->storage = m_storage;
    m_tag->label = m_label;
}

DE_END
