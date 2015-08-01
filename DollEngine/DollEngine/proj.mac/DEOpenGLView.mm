//
//  ViewController.m
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import "DEOpenGLView.h"
#import <OpenGL/OpenGL.h>
#include "Application.h"
#include "GLCanvas.h"
#include "CompManager.h"

@implementation DEOpenGLView
{
    NSTimer* m_timer;
}

- (void)redraw:(NSTimer *)pTimer
{
    [self setNeedsDisplay:YES];
}


-(void)prepareOpenGL
{
    NSOpenGLPixelFormatAttribute attributes[] = {
        NSOpenGLPFADepthSize, 24,
        NSOpenGLPFAStencilSize, 8,
        NSOpenGLPFADoubleBuffer,
        0
    };
    
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
    if (pixelFormat == nil) {
        NSLog(@"Faild create pixel format");
        return;
    }
    
    [self setPixelFormat:pixelFormat];
    [super prepareOpenGL];
    
    [self.openGLContext makeCurrentContext];
    
    m_timer = [NSTimer timerWithTimeInterval:(1.0/60.0) target:self
                                    selector:@selector(redraw:) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop]addTimer:m_timer forMode:
     NSDefaultRunLoopMode];
}

- (void)viewDidMoveToWindow
{
    int options=NSTrackingMouseEnteredAndExited|NSTrackingActiveAlways|NSTrackingInVisibleRect|NSTrackingEnabledDuringMouseDrag;//
    
    NSTrackingArea *ta;
    ta=[[NSTrackingArea alloc] initWithRect:NSZeroRect options:options owner:self userInfo:nil];
    [self addTrackingArea:ta];
    //NSLog(@"viewDidMoveToWindow");
}

-(void) lockOpenGLContext
{
    NSOpenGLContext *glContext = [self openGLContext];
    NSAssert( glContext, @"FATAL: could not get openGL context");
    [glContext makeCurrentContext];
    CGLLockContext((CGLContextObj)[glContext CGLContextObj]);
}

-(void) unlockOpenGLContext
{
    NSOpenGLContext *glContext = [self openGLContext];
    NSAssert( glContext, @"FATAL: could not get openGL context");
    CGLUnlockContext((CGLContextObj)[glContext CGLContextObj]);
}

- (void) drawRect:(NSRect)dirtyRect
{
    [self lockOpenGLContext];
    DEApplication->mainLoop();
    glFlush();
    //    [[self openGLContext] flushBuffer];
    [self unlockOpenGLContext];
}

-(void)onClose
{
    [m_timer invalidate];
    [self clearGLContext];
}

-(void)mouseDown:(NSEvent *)theEvent
{
    NSPoint event_location = [theEvent locationInWindow];
    NSPoint local_point = [self convertPoint:event_location fromView:nil];
    DE::CompManager::GetInstance()->onMouseDown(local_point.x,local_point.y);
}

-(void)mouseDragged:(NSEvent *)theEvent
{
    NSPoint event_location = [theEvent locationInWindow];
    NSPoint local_point = [self convertPoint:event_location fromView:nil];
    DE::CompManager::GetInstance()->onMouseMove(local_point.x, self.frame.size.height - local_point.y);
}

-(void)mouseUp:(NSEvent *)theEvent
{
    NSPoint event_location = [theEvent locationInWindow];
    NSPoint local_point = [self convertPoint:event_location fromView:nil];
    DE::CompManager::GetInstance()->onMouseUp(local_point.x, local_point.y);
}


@end
