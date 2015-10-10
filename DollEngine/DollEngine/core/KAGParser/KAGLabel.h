//
//  KAGLabel.h
//  DollEngine
//
//  Created by DollStudio on 15/8/8.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__KAGLabel__
#define __DollEngine__KAGLabel__


#include "KAGTag.h"

DE_BEGIN


class KAGLabel
{
public:
    KAGLabel():isMacro(false),storage(null),nextLabel(null){}
    ~KAGLabel(){
        for(KAGTag* tag : allTags)
        {
            delete tag;
        }
        allTags.clear();
    }
    
    void addTag(KAGTag* tag){
        allTags.push_back(tag);
    }
    void print(int idx);
    KAGStorage* storage;
    String key;
    String name;
    vector<KAGTag*> allTags;
    bool isMacro;
    KAGLabel* nextLabel;
};


DE_END

#endif /* defined(__DollEngine__KAGLabel__) */
