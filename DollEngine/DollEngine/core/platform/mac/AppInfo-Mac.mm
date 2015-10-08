//
//  AppInfo-Mac.mm
//  DollEngine
//
//  Created by DollStudio on 15/10/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "AppInfo.h"

DE_BEGIN

float AppInfo::getDesktopWidth()
{
    return [[NSScreen mainScreen] frame].size.width;
}

float AppInfo::getDesktopHeight()
{
    return [[NSScreen mainScreen] frame].size.height;
}

DE_END

