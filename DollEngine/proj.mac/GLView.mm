//
//  GLView.m
//  Krkr_GL
//
//  Created by DollStudio on 14/12/6.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#import "GLView.h"
#include "de.h"
//#include "PaintEngine.h"
//#include "Canvas.h"
//#include "Window.h"
//#include "Object.h"
//#include "Storages.h"
//#include "COMManager.h"

@implementation GLView

- (void)idle:(NSTimer *)pTimer
{
    [self drawRect:[self bounds]];
}

- (void) prepareOpenGL
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
                                   selector:@selector(idle:) userInfo:nil repeats:YES];
    [[NSRunLoop currentRunLoop]addTimer:m_timer forMode:
     NSDefaultRunLoopMode];
    
    de::gl::initialize();
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
    if (de::device::window()) {
        de::device::window()->visit();
    }
    glFlush();
//    [[self openGLContext] flushBuffer];
    [self unlockOpenGLContext];
}

-(void)close
{
    [m_timer invalidate];
    [self clearGLContext];
}

-(void)mouseDown:(NSEvent *)theEvent
{
    _touchValid = NO;
    NSPoint event_location = [theEvent locationInWindow];
    NSPoint local_point = [self convertPoint:event_location fromView:nil];
//    if(COMManager::GetInstance()->touchBegan(local_point.x, self.frame.size.height - local_point.y))
//    {
//        _touchValid = YES;
//    }
}

-(void)mouseMoved:(NSEvent *)theEvent
{
    if (!_touchValid) {
        return;
    }
    NSPoint event_location = [theEvent locationInWindow];
    NSPoint local_point = [self convertPoint:event_location fromView:nil];
//    COMManager::GetInstance()->touchMoved(local_point.x, self.frame.size.height -local_point.y);
}

-(void)mouseUp:(NSEvent *)theEvent
{
    if (!_touchValid) {
        return;
    }
    NSPoint event_location = [theEvent locationInWindow];
    NSPoint local_point = [self convertPoint:event_location fromView:nil];
//    COMManager::GetInstance()->touchEnded(local_point.x, self.frame.size.height -local_point.y);
}

@end
