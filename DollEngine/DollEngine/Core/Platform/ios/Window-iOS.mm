//
//  Window-MAC.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "Window.h"
#include "System.h"
#include "GLCanvas.h"

static UIWindow* s_window=nil;

@interface WindowDelegate : NSObject

+(WindowDelegate*)GetInstance;

@end

@implementation WindowDelegate

static WindowDelegate* s_instance=nil;

+(WindowDelegate*)GetInstance
{
    if (!s_instance) {
        s_instance = [[WindowDelegate alloc]init];
    }
    return s_instance;
}

@end

DE_BEGIN

void Window::initialize(float w, float h,float s)
{
    if (!m_deviceWindow) {
        if (w < 120) {
            w = 120;
        }
        if (h < 120) {
            h = 120;
        }
        s_window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

        m_deviceWindow = (__bridge void*)s_window;
//        
//        DEOpenGLView* glView = [[DEOpenGLView alloc]initWithFrame:rc];
//        s_window.contentView = glView;
//        s_window.releasedWhenClosed = YES;
        [s_window center];
        [s_window becomeFirstResponder];
        
        //        [s_window makeKeyAndOrderFront:[WindowDelegate GetInstance]];
//        [s_window setAcceptsMouseMovedEvents:NO];
//        [s_window makeMainWindow];
//        
//        s_window.delegate = [WindowDelegate GetInstance];

    }
}


DE_END