//
//  KAGStorage.h
//  DollEngine
//
//  Created by DollStudio on 15/8/8.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__KAGStorage__
#define __DollEngine__KAGStorage__

#include "KAGLabel.h"

DE_BEGIN


class KAGStorage
{
public:
    KAGStorage(){}
    ~KAGStorage(){
        for(auto iter : allLabels)
        {
            delete iter.second;
        }
        allLabels.clear();
    }
    void addLabel(KAGLabel* title){
        allLabels[title->key] = title;
    }
    KAGLabel* getLabel(const wstring& key)
    {
        auto iter = allLabels.find(key);
        if (iter == allLabels.end()) {
            return NULL;
        }
        return iter->second;
    }
    wstring fullPath;
    wstring fileName;
    map<wstring,KAGLabel*> allLabels;
};

DE_END

#endif /* defined(__DollEngine__KAGStorage__) */
