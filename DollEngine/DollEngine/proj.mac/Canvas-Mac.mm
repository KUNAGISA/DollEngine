//
//  Canvas-Mac.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import "ViewController.h"
#include "Canvas.h"
#include "Device.h"

DE_BEGIN

void Canvas::setVisible(bool v)
{
    if (m_visible != v)
    {
        if (v && !m_window) {
            ViewController* ctlr = [ViewController GetInstance];
            NSWindow* curWindow = ctlr.view.window;
            curWindow.delegate = ctlr;
            [curWindow setReleasedWhenClosed:YES];
//            [curWindow setContentSize:CGSizeMake(m_winWidth, m_winHeight)];
            [curWindow center];
            m_window = (__bridge void*)curWindow;
            
            
            initializeGL();
        }
    }
}

DE_END
