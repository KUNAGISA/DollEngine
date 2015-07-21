//
//  KAGData.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/11/16.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "KAGData.h"
#include "KAGParser.h"

DE_BEGIN

int KAGTag::exec(KAGParser* parser)
{
    parser->m_currentLine = this->line;
    if (name == L"macro")
    {
        if (parser->getIsMakeMacro())
        {
            Debug::throwMsg(ERROR_KAG_MACRO_NESTING);
        }
        wstring macroname = getValue(L"name");
        if (macroname.size() == 0)
        {
            Debug::throwMsg(ERROR_KAG_MACRONAME_EMPTY);
        }
        KAGLabel* label = new KAGLabel();
        label->key = macroname;
        label->isMacro = true;
        parser->m_macros->addLabel(label);
        parser->m_label = label;
        parser->setIsMakeMacro(true);
        this->print();
        return 0;
    }
    else if (parser->getIsMakeMacro())
    {
        this->print();
        parser->m_label->addTag(this);
        if (name == L"endmacro")
        {
            parser->setIsMakeMacro(false);
        }
        return 0;
    }
    else
    {
        return parser->execute(this);
    }
}


int KAGLabel::exec(KAGParser* parser, int tag_index)
{
    for (int i = tag_index; i < allTags.size(); ++i)
    {
        parser->m_currentTagIndex=i;
        int ret = allTags[i]->exec(parser);
        if (ret != 0) {
            return ret;
        }
    }
    return 0;
}

int KAGStorage::exec(KAGParser* parser,const wstring& label_key, int tag_index)
{
    auto iter = allLabels.find(label_key);
    if (iter == allLabels.end())
    {
        Debug::throwMsg(ERROR_KAG_LABEL_FIND_FAIL,parser->m_currentLine,label_key);
        return -2;
    }
    parser->m_currentStorage = this;
    parser->setIsProcessed(true);
    KAGLabel* label = iter->second;
    bool isjump = false;
    while (label)
    {
        parser->m_currentLabelKey = label->key;
        int ret = label->exec(parser, tag_index);
        tag_index = 0;
        if(ret == 0)
        {
            label = label->nextLabel;
        }
        else if (ret == -1)
        {
            //即将jump
            isjump = true;
            break;
        }
        else if (ret > 0)
        {
            parser->m_nextKAG.storage = parser->m_currentStorage;
            parser->m_nextKAG.labelKey = parser->m_currentLabelKey;
            parser->m_nextKAG.tagIndex = parser->m_currentTagIndex+1;
            parser->wait(ret/1000.0f);
            parser->setIsProcessed(false);
            return 0;
        }
        else if (ret < -1)
        {
            //完全停止
            parser->m_nextKAG.storage = null;
            parser->setIsProcessed(false);
            return 0;
        }
    }
    parser->setIsProcessed(false);
    if (isjump) {
        if (parser->m_nextKAG.storage)
        {
            return parser->m_nextKAG.storage->exec(parser, parser->m_nextKAG.labelKey, parser->m_nextKAG.tagIndex);
        }
        else
        {
            return -2;
        }
    }
    else {
        parser->onScenarioEnded();
        return 0;
    }
}

DE_END