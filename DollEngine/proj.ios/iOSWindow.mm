//
//  iOSWindow.mm
//  DollEngineIOS
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#include "iOSWindow.h"
#include "PaintEngine.h"
#include "System.h"
#include "SystemDelegate.h"

static bool g_loopEnabled = true;

@interface OpenGLController : GLKViewController {
    GLuint defaultFramebuffer_;
    GLuint colorRenderbuffer_;
    BOOL isClick_;
    BOOL mouseEnabled_;
}

+(OpenGLController*)GetInstance;

@property (strong, nonatomic) EAGLContext *context;

@end

@implementation OpenGLController

static OpenGLController* s_instance=nil;

+(OpenGLController*)GetInstance
{
    if (!s_instance) {
        s_instance = [[OpenGLController alloc]initWithNibName:nil bundle:nil];
    }
    return s_instance;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    
    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormatNone;
    
    CHECK_GL_ERROR;
    
    [EAGLContext setCurrentContext:self.context];
    DE::PaintEngine::GetInstance()->initialize();
    
    glGenFramebuffers(1, &defaultFramebuffer_);
    NSAssert( defaultFramebuffer_, @"Can't create default frame buffer");
    
    glGenRenderbuffers(1, &colorRenderbuffer_);
    NSAssert( colorRenderbuffer_, @"Can't create default render buffer");
    
    glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer_);
    glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer_);
    glBindVertexArrayOES(0);
    CHECK_GL_ERROR;
    
    self.preferredFramesPerSecond = 30;//设置刷新率
}

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
    
    glDeleteBuffers(1, &defaultFramebuffer_);
    glDeleteBuffers(1, &colorRenderbuffer_);
    glDeleteVertexArraysOES(1,0);
    DE::System::GetInstance()->doCompact();
}

- (void)dealloc
{
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    DE::System::GetInstance()->doCompact();
//    if ([self isViewLoaded] && ([[self view] window] == nil)) {
//        self.view = nil;
//        
//        [self tearDownGL];
//
//        if ([EAGLContext currentContext] == self.context) {
//            [EAGLContext setCurrentContext:nil];
//        }
//        self.context = nil;
//    }
    
    // Dispose of any resources that can be recreated.
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    mouseEnabled_ = YES;
    isClick_ = YES;
    NSEnumerator * enumerator = [touches objectEnumerator];
    UITouch *touch;
    
    while (touch = [enumerator nextObject]) {
        break;
    }
    CGPoint pos = [touch locationInView:self.view];
    float s = [UIScreen mainScreen].scale;
    pos.x *= s;
    pos.y *= s;
    float x = pos.x - DE::PaintEngine::GetInstance()->getLayerX();
    float y = pos.y - DE::PaintEngine::GetInstance()->getLayerY();
    x /= DE::PaintEngine::GetInstance()->getLayerZoom();
    y /= DE::PaintEngine::GetInstance()->getLayerZoom();
    if(x < 0 ||
       y < 0 ||
       x > DE::PaintEngine::GetInstance()->getLayerWidth()||
       y > DE::PaintEngine::GetInstance()->getLayerHeight()){
        mouseEnabled_ = NO;
        return;
    }
    y = DE::PaintEngine::GetInstance()->getLayerHeight() - y;
    DE::System::GetInstance()->getDelegate()->onMouseDown(x,y);
    return;
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    if(mouseEnabled_) {
        NSEnumerator * enumerator = [touches objectEnumerator];
        UITouch *touch;
        while (touch = [enumerator nextObject]) {
            break;
        }
        CGPoint pos = [touch locationInView:self.view];
        float s = [UIScreen mainScreen].scale;
        pos.x *= s;
        pos.y *= s;
        float x = pos.x - DE::PaintEngine::GetInstance()->getLayerX();
        float y = pos.y - DE::PaintEngine::GetInstance()->getLayerY();
        x /= DE::PaintEngine::GetInstance()->getLayerZoom();
        y /= DE::PaintEngine::GetInstance()->getLayerZoom();
        isClick_ = NO;
        y = DE::PaintEngine::GetInstance()->getLayerHeight() - y;
        DE::System::GetInstance()->getDelegate()->onMouseMove(x,y);
    }
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    if(mouseEnabled_) {
        NSEnumerator * enumerator = [touches objectEnumerator];
        UITouch *touch;
        while (touch = [enumerator nextObject]) {
            break;
        }
        CGPoint pos = [touch locationInView:self.view];
        float s = [UIScreen mainScreen].scale;
        pos.x *= s;
        pos.y *= s;
        float x = pos.x - DE::PaintEngine::GetInstance()->getLayerX();
        float y = pos.y - DE::PaintEngine::GetInstance()->getLayerY();
        x /= DE::PaintEngine::GetInstance()->getLayerZoom();
        y /= DE::PaintEngine::GetInstance()->getLayerZoom();
        y = DE::PaintEngine::GetInstance()->getLayerHeight() - y;
        DE::System::GetInstance()->getDelegate()->onMouseUp(x,y);
        if (isClick_) {
            DE::System::GetInstance()->getDelegate()->onClick(x,y);
        }
    }
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    if(mouseEnabled_) {
        NSEnumerator * enumerator = [touches objectEnumerator];
        UITouch *touch;
        while (touch = [enumerator nextObject]) {
            break;
        }
        CGPoint pos = [touch locationInView:self.view];
        float s = [UIScreen mainScreen].scale;
        pos.x *= s;
        pos.y *= s;
        float x = pos.x - DE::PaintEngine::GetInstance()->getLayerX();
        float y = pos.y - DE::PaintEngine::GetInstance()->getLayerY();
        x /= DE::PaintEngine::GetInstance()->getLayerZoom();
        y /= DE::PaintEngine::GetInstance()->getLayerZoom();
        isClick_ = NO;
        y = DE::PaintEngine::GetInstance()->getLayerHeight() - y;
        DE::System::GetInstance()->getDelegate()->onMouseUp(x,y);
    }
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    if(g_loopEnabled){
        DE::SystemDelegate* delegate = DE::System::GetInstance()->getDelegate();
        if(delegate) {
            delegate->onMainLoop();
        }
    }
}


@end

DE_BEGIN

static iOSWindow* g_window = NULL;

iOSWindow* iOSWindow::GetInstance()
{
    return g_window;
}

iOSWindow::iOSWindow()
{
    g_window = this;
	UIWindow* window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    setWidth(window.frame.size.width);
    setHeight(window.frame.size.height);
	OpenGLController* viewController = [OpenGLController GetInstance];
    
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden: YES];

    m_iosWindow = (__bridge void*)window;
    m_iosViewCtl = (__bridge void*)viewController;
}

iOSWindow::~iOSWindow()
{
    UIWindow* window = (__bridge UIWindow*)m_iosWindow;
    [window release];
    GLKViewController* ctl = (__bridge GLKViewController*)m_iosViewCtl;
    [window release];
    [ctl release];
}

void iOSWindow::mainLoopEnabled(bool v)
{
    g_loopEnabled = v;
}

void iOSWindow::setVisible(bool v)
{
	m_visible = true;
}

void iOSWindow::setSize(int w,int h)
{
    w = System::GetInstance()->getDesktopWidth();
    h = System::GetInstance()->getDesktopHeight();
    Window::setSize(w, h);
    PaintEngine::GetInstance()->resize(w,h);
}

DE_END
