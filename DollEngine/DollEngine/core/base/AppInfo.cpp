//
//  System.cpp
//  DollEngine
//
//  Created by DollStudio on 15/10/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "System.h"
#include "Console.h"

DE_BEGIN

bool System::NeedRedraw=true;
bool System::NeedSortTouches=true;

void System::setDebugMode(int v)
{
    m_debugMode = v;
}


DE_END
