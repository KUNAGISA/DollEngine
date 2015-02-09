//
//  Window_MAC.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14/12/7.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "WindowDelegate.h"
#import "GLView.h"
#include "Window.h"

static  NSWindow* s_window = nil;
void Window::initGLView()
{
    if(m_width < 128) setInnerWidth(128);
    if(m_height < 128) setInnerHeight(128);
    NSRect rect = NSMakeRect(0, 0, m_innerWidth, m_innerHeight);
    NSInteger mask = NSClosableWindowMask
    | NSTitledWindowMask
    | NSMiniaturizableWindowMask
//    | NSResizableWindowMask
    ;
    s_window = [[NSWindow alloc] initWithContentRect:rect
                                                styleMask:mask
                                                  backing:NSBackingStoreBuffered
                                                    defer:YES];
    s_window.delegate = [WindowDelegate getInstance];
    
    GLView* glView = [[GLView alloc] initWithFrame:NSMakeRect(0, 0, m_innerWidth, m_innerHeight)];
    [WindowDelegate getInstance].glView = glView;
    s_window.contentView = glView;
    [s_window center];
    [s_window becomeFirstResponder];
    [s_window makeKeyAndOrderFront:[WindowDelegate getInstance]];
    [s_window setAcceptsMouseMovedEvents:NO];
    [s_window orderFront:nil];
    s_window.styleMask |= NSResizableWindowMask;
    reViewport();
}
