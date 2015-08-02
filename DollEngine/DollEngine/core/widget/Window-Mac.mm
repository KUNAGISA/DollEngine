//
//  Window-MAC.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "DEOpenGLView.h"
#include "Window.h"
#include "Application.h"
#include "GLCanvas.h"

static NSWindow* s_window=nil;

@interface WindowDelegate : NSObject<NSWindowDelegate>

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

- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize
{
    float menuBarHeight = [[[NSApplication sharedApplication] menu] menuBarHeight];
    if (frameSize.width <=128) {
        frameSize.width=128;
    }
    if (frameSize.height <=128+menuBarHeight) {
        frameSize.height=128+menuBarHeight;
    }
    
    DEApplication->setDeviceSize(frameSize.width, frameSize.height - menuBarHeight);
    DE::GLCanvas::GetInstance()->resizeGL();
    
    return frameSize;
}

-(BOOL)windowShouldClose:(id)sender
{
    [[NSApplication sharedApplication]terminate:sender];
    return YES;
}

@end

DE_BEGIN

void Window::initialize(float w, float h,float s)
{
    if (!m_deviceWindow) {
        if (w*s < 120) {
            w = 120;
        }
        if (h*s < 120) {
            h = 120;
        }
        NSRect rc = NSMakeRect(0, 0, w*s, h*s);
        NSUInteger uiStyle = NSTitledWindowMask | NSResizableWindowMask | NSClosableWindowMask;
        NSBackingStoreType storeStyle = NSBackingStoreBuffered;
        s_window = [[NSWindow alloc]initWithContentRect:rc
                                              styleMask:uiStyle
                                                backing:storeStyle
                                                  defer:NO
                                                 screen:[NSScreen mainScreen]];

        m_deviceWindow = (__bridge void*)s_window;
        
        DEOpenGLView* glView = [[DEOpenGLView alloc]initWithFrame:rc];
        s_window.contentView = glView;
        s_window.releasedWhenClosed = YES;
        [s_window center];
        [s_window becomeFirstResponder];
        [s_window makeKeyAndOrderFront:[WindowDelegate GetInstance]];
        [s_window setAcceptsMouseMovedEvents:NO];
        [s_window makeMainWindow];
        
        s_window.delegate = [WindowDelegate GetInstance];
        DEApplication->setDeviceSize(w*s,h*s);
        GLCanvas::GetInstance()->setLayerWidth(w);
        GLCanvas::GetInstance()->setLayerHeight(h);
        GLCanvas::GetInstance()->initializeGL();
        DEApplication->initDebugInfo();
        onInitFinished();
    }
}

void Window::setTitle(const string &v)
{
    m_title = v;
    s_window.title = [NSString stringWithUTF8String:v.c_str()];
}

DE_END