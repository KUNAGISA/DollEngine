//
//  KAGController.h
//  DollEngine
//
//  Created by DollStudio on 15/8/8.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__KAGController__
#define __DollEngine__KAGController__

#include "KAGParser.h"
#include "CoreTypes.h"

DE_BEGIN


struct KAGStack
{
    KAGStorage* storage;
    KAGLabel* label;
    int tagIndex;
};


class KAGController
{
public:
    KAGController();
    virtual ~KAGController();
    
    bool stepInLabel(const String& storage, const String& label, bool iscall);
    bool stepOutLabel();
    bool stepNext();
    virtual int doTag(){return 0;}
    
    void printLabel();
    
    String getLastTarget(){return m_lastTarget;}
    
protected:
    KAGStorage* m_storage;
    KAGLabel* m_label;
    String m_lastTarget;
    int m_tagIndex;
    vector<KAGStack> m_stack;
};

DE_END

#endif /* defined(__DollEngine__KAGController__) */
