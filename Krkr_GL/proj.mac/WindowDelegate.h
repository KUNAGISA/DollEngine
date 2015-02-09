//
//  WindowDelegate.h
//  Krkr_GL
//
//  Created by DollStudio on 14/12/7.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import "GLView.h"
#import "ConsoleController.h"

@interface WindowDelegate : NSObject<NSWindowDelegate>
{
    ConsoleController* m_control;
}

@property (nonatomic, assign) GLView* glView;

+(WindowDelegate*)getInstance;
-(void)showConsole;
-(void)pushLog:(const char*)text;
@end
