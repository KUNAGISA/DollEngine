//
//  Window.cpp
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Window.h"
#include "RTT.h"
#include "PaintEngine.h"

DE_BEGIN

static Window* s_instance=NULL;

Window* Window::GetInstance()
{
    return s_instance;
}

Window::Window()
:m_visible(false)
,m_fullScreen(false)
{
    s_instance = this;
}

Window::~Window()
{
}

DE_END


#include "TjsBind.h"


