//
//  de-painter-interface.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/22.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-painter-interface.h"
#include "de.h"

NAMESPACE_DE_PAINTER

void reset_viewport()
{
    Transform* device = device::main_trans();
    device->refresh();
    
    device::Window* window = device::window();
    
    float p = window->getLayerWidth()
    /window->getLayerHeight();
    float sc_p = window->getInnerWidth()
    /window->getInnerHeight();
    float layZoom=1,layX=0,layY=0;
    if (p > sc_p)
    {
        //上下留边
        layZoom = window->getInnerWidth()/window->getLayerWidth();
        layX = 0;
        layY = (window->getInnerHeight() - window->getLayerHeight() * layZoom)/2;
    }
    else
    {
        //左右留边
        layZoom = window->getInnerHeight()
        /window->getLayerHeight();
        layX = (window->getInnerWidth() - window->getLayerWidth() * layZoom)/2;
        layY = 0;
    }
    window->setLayerZoom(layZoom);
    window->setLayerLeft(layX);
    window->setLayerTop(layY);
    
    device->setX(layX*2/window->getInnerWidth()-1);
    device->setY(-layY*2/window->getInnerHeight()+1);
    device->setScaleX(2/window->getInnerWidth() * layZoom);
    device->setScaleY(-2/window->getInnerHeight() * layZoom);
    
#ifdef OS_MAC
    glViewport(0,0,window->getInnerWidth(),window->getInnerHeight());
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#endif
}

NAMESPACE_DE_END2
