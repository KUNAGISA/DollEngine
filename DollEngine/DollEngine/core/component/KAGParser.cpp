//
//  KAGParser.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/11/14.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "KAGParser.h"
#include "Storages.h"

DE_BEGIN

KAGParser::KAGParser()
:m_errorLine(-1)
,m_storage(null)
,m_label(null)
,m_tag(null)
,m_isScripts(false)
,m_errorInfo(NO_ERROR)
,m_currentStorage(null)
,m_waitTime(0)
,m_isProcssed(false)
,m_currentLine(0)
,m_currentTagIndex(0)
,m_parseLine(0)
,m_isMakeMacro(false)
{
    setCompName("KAGParser");
    m_type = COMP_UPDATE;
    m_macros = new KAGStorage();
    m_macros->fileName = L"MACRO";
    m_macros->fullPath = L"MACRO";
    m_allStorage[L"MACRO"] = m_macros;
}

KAGParser::~KAGParser()
{
    for (auto iter: m_allStorage)
    {
        delete iter.second;
    }
    m_allStorage.clear();
//    delete m_macros;
}

void KAGParser::jumpTo(const wstring& filepath,const wstring& key)
{
    setEnabled(false);
    DM("\n========%ls(%ls)========",filepath.c_str(),key.c_str());
    if (getIsProcessed())
    {
        m_nextKAG.storage = loadScenario(filepath);
        m_nextKAG.labelKey = key;
        m_nextKAG.tagIndex = 0;
    }
    else
    {
        auto storage = loadScenario(filepath);
        if (storage) {
            storage->exec(this, key, 0);
        }
    }
}

void KAGParser::wait(float time)
{
    setWaitTime(time);
    setTime(0);
    setEnabled(true);
}

void KAGParser::doNext()
{
    setWaitTime(0);
}//立刻执行下一个

KAGStorage* KAGParser::loadScenario(const wstring& filepath)
{
    string fpath;
    string path;
    UnicodeToUtf8(filepath.c_str(), path);
    if (path != "MACRO")
    {
        fpath = Storages::GetInstance()->getFullPath(path);
        if (fpath == "")
        {
            Debug::throwMsg(ERROR_FILE_EXIST_FAILD,path.c_str());
            return null;
        }
    }
    else
    {
        fpath = "MACRO";
    }
    wstring fullpath;
    Utf8ToUnicode(fpath.c_str(), fullpath);
    auto storage_iter = m_allStorage.find(fullpath);
    if (storage_iter != m_allStorage.end())
    {
        return storage_iter->second;
    }
    IOData* data = Storages::GetFileString(fpath);
    if (!data)
    {
        m_errorLine = -1;
        return null;
    }
    wstring kagcode;
    kagchar* ntext;
    if (data->getBuffer()[0] != 0xfe) {
        data->convertToUnicode(kagcode);
        ntext = (kagchar*)kagcode.c_str();
    }
    else {
        ntext = (kagchar*)data->getBuffer();
    }
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
            m_label = null;
            m_tag = null;
            Debug::throwMsg(m_errorInfo,m_errorLine);
            break;
        }
    }
    SAFF_DELETE(data);
    auto ret = m_storage;
    m_storage = null;
    m_label = null;
    m_tag = null;
    if (m_errorLine == 0)
    {
        m_allStorage[fullpath] = ret;
        return ret;
    }
    else
    {
        return null;
    }
}

void KAGParser::callLabel(const wstring& filepath, const wstring& key)
{
    KAGStack stack;
    stack.storage = m_currentStorage;
    stack.labelKey = m_currentLabelKey;
    stack.tagIndex = m_currentTagIndex;
    m_callStack.push_back(stack);
    jumpTo(filepath,key);
}

void KAGParser::clearCallStack()
{

}

void KAGParser::returnCall()
{
    if (m_callStack.size() == 0)
    {
        Debug::throwMsg(ERROR_KAG_LABEL_FIND_FAIL,m_currentLine);
    }
    KAGStack stack = m_callStack.back();
    m_callStack.pop_back();
    
    m_nextKAG.storage = stack.storage;
    m_nextKAG.labelKey = stack.labelKey;
    m_nextKAG.tagIndex = stack.tagIndex+1;
    DM("\n========%ls(%ls)========",
       m_nextKAG.storage->fileName.c_str(),
       m_nextKAG.labelKey.c_str());
}

bool KAGParser::callMacro(const wstring& name)
{
    auto label = m_macros->getLabel(name);
    if (label)
    {
        callLabel(L"MACRO", name);
        return true;
    }
    return false;
}

void KAGParser::trigger()
{
    if (m_waitTime <= getTime()) {
        setEnabled(false);
        m_nextKAG.storage->exec(this, m_nextKAG.labelKey, m_nextKAG.tagIndex);
    }
}

int KAGParser::execute(KAGTag* tag)
{
    tag->print();
    return 0;
}

kagchar* KAGParser::parseLine(kagchar* text,bool is_scripts)
{
    bool _is_note = false;
    while (text && *text)//*text != '\0' && *text != '\n' && *text != '\r')
    {
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
            kagchar* ntext = containText(text, L"[endscript]",false);
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
            m_tag = null;
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
                return null;
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
    return null;
}

kagchar* KAGParser::parseLabel(kagchar* text)
{
    kagchar* ntext=text;
    ++ntext;
    ntext = parseEmpty(ntext);
    wstring key=L"*";
    wstring name;
    while (true)
    {
        if (*ntext < 0x21||
            *ntext == '|')
        {
            if (key == L"*")
            {
                m_errorInfo = ERROR_KAG_LABELKEY_NULL;
                m_errorLine = m_parseLine;
                return null;
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

kagchar* KAGParser::parseTagAt(kagchar* text)
{
    return parseTag(text,true);
}

kagchar* KAGParser::parseTag(kagchar* text,bool is_at)
{
    text = parseEmpty(text);
    kagchar* ttext = parseTagName(text,is_at);
    if (!ttext) {
        return null;
    }
    wstring name;
    name.assign(text, ttext-text);
    createTag(name);
    text = ttext;
    wstring key,value;
    while (true)
    {
        key = L"",value=L"";
        text = parseEmpty(text);
        kagchar* ntext = parseTagParamKey(text,is_at);
        if (ntext != text)
        {
            key.assign(text, ntext-text);
            text = ntext;
            text = parseEmpty(text);
            bool entity=false;
            bool macroarg = false;
            ntext = parseTagParamValue(text, is_at,value,entity,macroarg);
            if (ntext == null) {
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

kagchar* KAGParser::parseTagName(kagchar* text,bool is_at)
{
    kagchar* ntext = text;
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

kagchar* KAGParser::parseTagParamKey(kagchar* text,bool is_at)
{
    kagchar* ntext = text;
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

kagchar* KAGParser::parseTagParamValue(kagchar* text,bool is_at,wstring& value,bool& entity,bool& macroarg)
{
    kagchar* ntext = text;
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
    while (true)
    {
        if (*ntext == '\\') {
            value.push_back(*ntext);
            ++ntext;
            value.push_back(*ntext);
            ++ntext;
            continue;
        }
        if (*ntext == '&' && *(ntext+1) != '&') {
            entity = true;
        }
        if (*ntext == '\'' || *ntext == '"')
        {
            wstring str;
            ntext = parseString(ntext,str,entity);
            if (!ntext) {
                return null;
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
                return null;
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

kagchar* KAGParser::parseEmpty(kagchar* text)
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

kagchar* KAGParser::parseString(kagchar* text,wstring& str,bool& entity)
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
            return null;
        }
        if (*text == '\\') {
            str.push_back(*text);
            ++text;
            str.push_back(*text);
            ++text;
            continue;
        }
        if (*text == '&' && *(text+1) != '&') {
            entity = true;
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

kagchar* KAGParser::parseCh(kagchar* text)
{
    kagchar* ntext = text;
    while (true)
    {
        if (*ntext < 0x20 ||
            *ntext == '[')
        {
            if (!m_tag || m_tag->name != L"ch")
            {
                createTag(L"ch");
                m_tag->addParam(L"text", L"");
            }
            m_tag->params[0].value.append(text, ntext-text);
            return ntext;
        }
        ++ntext;
    }
}

kagchar* KAGParser::containText(kagchar* text, const wchar_t* data,bool is_end)
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

void KAGParser::createStorage(const wstring& file,const wstring& fullpath)
{
    SAFF_DELETE(m_storage);
    m_storage = new KAGStorage();
    m_storage->fileName=file;
    m_storage->fullPath=fullpath;
    m_label=null;
    m_tag=null;
}

void KAGParser::createLabel(const wstring& key,const wstring& name)
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
    m_tag = null;
}

void KAGParser::createTag(const wstring& name)
{
    m_tag = new KAGTag();
    m_tag->name=name;
    m_tag->line = m_parseLine;
    m_label->addTag(m_tag);
    m_tag->storage = m_storage;
    m_tag->label = m_label;
}

DE_END
