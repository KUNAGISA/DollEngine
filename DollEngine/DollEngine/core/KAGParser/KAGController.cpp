//
//  KAGController.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/8.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "KAGController.h"
#include "KAGParser.h"
#include "ScriptEngine.h"

DE_BEGIN

KAGController::KAGController()
:m_storage(null)
,m_label(null)
,m_tagIndex(0)
{
    
}

KAGController::~KAGController()
{
    
}

bool KAGController::stepInLabel(const wstring& file, const wstring& label, bool iscall)
{
    KAGStorage* storage;
    if (file == L"") {
        storage = m_storage;
    }
    else {
        storage = KAGParser::GetInstance()->loadScenario(file);
    }
    if (!storage) {
        return false;
    }
    KAGLabel* lb;
    if (label == L"") {
        lb = storage->getLabel(L"_def_");;
    }
    else {
        lb = storage->getLabel(label);
    }
    if (!lb) {
        return false;
    }
    if (iscall) {
        if (m_storage) {
            KAGStack stack={m_storage,m_label,m_tagIndex};
            m_stack.push(stack);
        }
    }
    m_storage = storage;
    m_label = lb;
    m_tagIndex = 0;
    wstring dm = L"\n========";
    dm += m_storage->fileName;
    dm += L"(";
    dm += m_label->key;
    dm += L")========";
    ScriptEngine::GetInstance()->print(dm);
    return true;
}
bool KAGController::stepOutLabel()
{
    if (m_stack.size() == 0) {
        return false;
    }
    KAGStack stack = m_stack.top();
    m_storage = stack.storage;
    m_label = stack.label;
    m_tagIndex = stack.tagIndex;
    m_stack.pop();
    wstring dm = L"\n========";
    dm += m_storage->fileName;
    dm += L"(";
    dm += m_label->key;
    dm += L")========";
    ScriptEngine::GetInstance()->print(dm);
    return true;
}

bool KAGController::stepNext()
{
    m_tagIndex++;
    while (true) {
        if (m_tagIndex >= m_label->allTags.size()) {
            if (!m_label->nextLabel) {
                return false;
            }
            m_label = m_label->nextLabel;
            m_tagIndex = 0;
            wstring dm = L"\n========";
            dm += m_storage->fileName;
            dm += L"(";
            dm += m_label->key;
            dm += L")========";
            ScriptEngine::GetInstance()->print(dm);
        }
        else{
            break;
        }
    }
    return true;
}

DE_END