//
//  ViewController.m
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import "ViewController.h"
#import <OpenGL/OpenGL.h>
#include "Device.h"
#include "GLCanvas.h"

@implementation ViewController

static ViewController* s_instance;
+(ViewController*)GetInstance
{
    return s_instance;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    s_instance = self;
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
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
    
    DE::Device::GetInstance()->setDeviceSize(frameSize.width, frameSize.height - menuBarHeight);
    DE::GLCanvas::GetInstance()->resizeGL();
    
    return frameSize;
}

-(BOOL)windowShouldClose:(id)sender
{
    [_glView onClose];
    [[NSApplication sharedApplication]terminate:sender];
    return YES;
}

@end

@implementation DEOpenGLView
{
    NSTimer* m_timer;
}

- (void)redraw:(NSTimer *)pTimer
{
    
    [self drawRect:[self bounds]];
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
    DE::Device::GetInstance()->mainLoop();
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
    //    if(COMManager::GetInstance()->touchBegan(local_point.x, self.frame.size.height - local_point.y))
    //    {
    //        _touchValid = YES;
    //    }
}

-(void)mouseMoved:(NSEvent *)theEvent
{
    NSPoint event_location = [theEvent locationInWindow];
    NSPoint local_point = [self convertPoint:event_location fromView:nil];
    //    COMManager::GetInstance()->touchMoved(local_point.x, self.frame.size.height -local_point.y);
}

-(void)mouseUp:(NSEvent *)theEvent
{
    NSPoint event_location = [theEvent locationInWindow];
    NSPoint local_point = [self convertPoint:event_location fromView:nil];
    //    COMManager::GetInstance()->touchEnded(local_point.x, self.frame.size.height -local_point.y);
}


@end
