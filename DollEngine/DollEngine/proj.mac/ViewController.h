//
//  ViewController.h
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface DEOpenGLView : NSOpenGLView

-(void)onClose;

@end

@interface ViewController : NSViewController<NSWindowDelegate>
{
    DEOpenGLView* _glView;
}

+(ViewController*)GetInstance;

-(void)setWindowSize:(float)w height:(float)h;

@end

