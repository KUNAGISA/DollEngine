//
//  de-device-interface.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include "de-device-interface.h"

NAMESPACE_DE_DEVICE

float get_window_edge_width()
{
    return 0;
}

float get_window_edge_height()
{
    return [[[NSApplication sharedApplication] menu] menuBarHeight];
}


NAMESPACE_DE_END2