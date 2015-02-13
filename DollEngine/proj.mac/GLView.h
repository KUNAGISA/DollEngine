//
//  GLView.h
//  Krkr_GL
//
//  Created by DollStudio on 14/12/6.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl.h>

@interface GLView : NSOpenGLView
{
    NSTimer* m_timer;
    BOOL _touchValid;
}

-(void)close;

@end
