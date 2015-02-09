//
//  ViewController.m
//  Krkr_GL
//
//  Created by DollStudio on 14-7-29.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#import "ViewController.h"
#include "Window.h"
#include "CanvasManager.h"
#include "System.h"
#include "MouseManager.h"

@interface ViewController ()

@property (strong, nonatomic) EAGLContext *context;
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    CGRect frame = [[UIScreen mainScreen]bounds];
    CGFloat factor = [[UIScreen mainScreen]scale];
    System::GetInstance()->setDesktopWidth(frame.size.width);
    System::GetInstance()->setDesktopHeight(frame.size.height);
    System::GetInstance()->setScreenWidth(frame.size.width*factor);
    System::GetInstance()->setScreenHeight(frame.size.height*factor);
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormatNone;
    
    if ([UIApplication sharedApplication].statusBarOrientation == UIInterfaceOrientationLandscapeLeft ||
        [UIApplication sharedApplication].statusBarOrientation == UIInterfaceOrientationLandscapeRight)
    {
        //横屏
    }
    else
    {
        //纵屏
    }
    [EAGLContext setCurrentContext:self.context];
    CanvasManager::GetInstance()->initGL();
//    self.preferredFramesPerSecond = 30;
    self.preferredFramesPerSecond = 60;
//    self.view.multipleTouchEnabled = true;
//    CanvasManager::GetInstance()->setTransChanged(false);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    if(Window::GetInstance())
    {
        [EAGLContext setCurrentContext:self.context];
        Window::GetInstance()->visit();
    }
}

#define __TOUCH_POS_CONVERT__(v,k) v*[[UIScreen mainScreen]scale]/Window::GetInstance()->getZoomNumer()-k

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    for(UITouch* touch in event.allTouches)
    {
        CGPoint pos = [touch locationInView:self.view];
        MouseManager::GetInstance()
        ->sendMouseEvent(MOUSE_STATE::MOUSE_DOWN,
                         __TOUCH_POS_CONVERT__(pos.x,Window::GetInstance()->getLeft()),
                         __TOUCH_POS_CONVERT__(pos.y,Window::GetInstance()->getTop()));
    }
}

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    for(UITouch* touch in event.allTouches)
    {
        CGPoint pos = [touch locationInView:self.view];
        MouseManager::GetInstance()
        ->sendMouseEvent(MOUSE_STATE::MOUSE_MOVE,
                         __TOUCH_POS_CONVERT__(pos.x,Window::GetInstance()->getLeft()),
                         __TOUCH_POS_CONVERT__(pos.y,Window::GetInstance()->getTop()));
    }
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    for(UITouch* touch in event.allTouches)
    {
        CGPoint pos = [touch locationInView:self.view];
        MouseManager::GetInstance()
        ->sendMouseEvent(MOUSE_STATE::MOUSE_UP,
                         __TOUCH_POS_CONVERT__(pos.x,Window::GetInstance()->getLeft()),
                         __TOUCH_POS_CONVERT__(pos.y,Window::GetInstance()->getTop()));
    }
}

-(void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    for(UITouch* touch in event.allTouches)
    {
        CGPoint pos = [touch locationInView:self.view];
        MouseManager::GetInstance()
        ->sendMouseEvent(MOUSE_STATE::MOUSE_CANCEL,
                         __TOUCH_POS_CONVERT__(pos.x,Window::GetInstance()->getLeft()),
                         __TOUCH_POS_CONVERT__(pos.y,Window::GetInstance()->getTop()));
    }
}

@end
