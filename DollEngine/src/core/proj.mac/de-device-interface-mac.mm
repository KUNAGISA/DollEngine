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
#import "WindowDelegate.h"
#include "de.h"

NAMESPACE_DE_DEVICE

float get_window_edge_width()
{
    return 0;
}

float get_window_edge_height()
{
    return [[[NSApplication sharedApplication] menu] menuBarHeight];
}

static NSWindow* s_window=null;
void init_window()
{
    if (device::window()->getInnerWidth() < 128) {
        device::window()->setInnerWidth(128);
    }
    if (device::window()->getInnerHeight() < 128) {
        device::window()->setInnerHeight(128);
    }
    NSRect rect = NSMakeRect(0, 0,
                             device::window()->getInnerWidth(),
                             device::window()->getInnerHeight());
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
    
    GLView* glView = [[GLView alloc] initWithFrame:rect];
    [WindowDelegate getInstance].glView = glView;
    s_window.contentView = glView;
    [s_window center];
    [s_window becomeFirstResponder];
    [s_window makeKeyAndOrderFront:[WindowDelegate getInstance]];
    [s_window setAcceptsMouseMovedEvents:NO];
    [s_window orderFront:nil];
    s_window.styleMask |= NSResizableWindowMask;
    device::window()->setID((__bridge void*)s_window);
    painter::reset_viewport();
}

NAMESPACE_DE_END2