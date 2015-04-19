//
//  Console-Mac.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import "ConsoleController.h"
#include "Console.h"

DE_BEGIN

void Console::setVisible(bool v)
{
    if (m_visible != v) {
        m_visible = v;
        if (!v) {
            [[ConsoleController GetInstance].window close];
        }
        else {
            [[ConsoleController GetInstance].window makeKeyAndOrderFront:nil];
        }
    }
}

DE_END
