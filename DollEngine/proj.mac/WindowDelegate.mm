//
//  WindowDelegate.m
//  DollEngine
//
//  Created by DollStudio on 14/12/7.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#import "WindowDelegate.h"
#include "de.h"

//#import "System.h"
//#include "Window.h"

@implementation WindowDelegate

static WindowDelegate* s_instance=nil;
+(WindowDelegate*)getInstance
{
    if (s_instance == nil)
    {
        s_instance = [[WindowDelegate alloc]init];
    }
    return s_instance;
}

- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize
{
    if (frameSize.width <=128) {
        frameSize.width=128;
    }
    if (frameSize.height <=128) {
        frameSize.height=128;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    auto window = de::device::window();
    if (window)
    {
        window->setSize(frameSize.width, frameSize.height);
        de::gl::reset_viewport();
    }
    return frameSize;
}

-(BOOL)windowShouldClose:(id)sender
{
    [self.glView close];
    [[NSApplication sharedApplication]terminate:sender];
    return YES;
}

-(void)showConsole
{
    if (!m_control) {
        m_control = [[ConsoleController alloc]initWithWindowNibName:@"ConsoleController"];
    }
    [m_control.window orderFrontRegardless];
}

-(void)pushLog:(const char*)text
{
    if (m_control)
    {
        [m_control pushLog:text];
    }
}

@end
