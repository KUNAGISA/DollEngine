//
//  de-tjs-window.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-tjs-window.h"

deTJSWindow::deTJSWindow()
{
    de::device::window(this);
}

void deTJSWindow::initWidget()
{
    de::device::init_window();
}

NCB_REGISTER_CLASS_DIFFER(Window, deTJSWindow)
{
    TJS_FACTORY
    NCB_METHOD(setInnerSize);
    NCB_METHOD(setSize);
    NCB_METHOD(setLayerSize);
    NCB_METHOD(initWidget);
    NCB_PROPERTY_RO(layerLeft, getLayerLeft);
    NCB_PROPERTY_RO(layerTop, getLayerTop);
    NCB_PROPERTY_RO(layerZoom, getLayerZoom);
    NCB_PROPERTY(layerWidth, getLayerWidth, setLayerWidth);
    NCB_PROPERTY(layerHeight, getLayerHeight, setLayerHeight);
    NCB_PROPERTY(innerWidth, getInnerWidth, setInnerWidth);
    NCB_PROPERTY(innerHeight, getInnerHeight, setInnerHeight);
};
