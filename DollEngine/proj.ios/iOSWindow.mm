//
//  iOSWindow.mm
//  DollEngineIOS
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "iOSWindow.h"

@interface OpenGLView : UIOpenGLView<UIWindowDelegate>

+(OpenGLView*)GetInstance;

@end

@implementation OpenGLView

static OpenGLView* s_instance=nil;

+(OpenGLView*)GetInstance
{
    if (!s_instance) {
        s_instance = [[OpenGLView alloc]init];
    }
    return s_instance;
}

@end

iOSWindow::iOSWindow()
{
	UIWindow* window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

	OpenGLView* glView = [OpenGLView GetInstance];
	glView.frame = [window bounds];
	glView.pixelFormat = kEAGLColorFormatRGBA8;
	glView.depthFormat = GL_DEPTH24_STENCIL8_OES;
	glView.preserveBackbuffer = NO;
	glView.sharegroup = nil;
	glView.multiSampling = NO;
	glView.numberOfSamples = 0;

	glView.multipleTouchEnabled = YES;

    UIViewController* viewController = [[UIViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = glView;
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


	window.delegate = glView;
	m_deviceWindow = (__bridge void*)win;
}

iOSWindow::~iOSWindow()
{

}

void iOSWindow::setVisible(bool v)
{
	m_visible = v;
	DM("iOS中Window的visible属性无效");

}