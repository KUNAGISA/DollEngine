//
//  TJSWindow.cpp
//  DollEngine
//
//  Created by DollStudio on 14/12/7.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "TJSWindow.h"

NCB_REGISTER_CLASS_DIFFER(_NCB_WINDOW_, TJSWindow)
{
    iTJS_FACTORY
    NCB_METHOD(setInnerSize);
    NCB_METHOD(setSize);
    NCB_METHOD(setLayerSize);
    NCB_METHOD(initGLView);
    NCB_PROPERTY_RO(layerLeft, getLayerLeft);
    NCB_PROPERTY_RO(layerTop, getLayerTop);
    NCB_PROPERTY_RO(layerZoom, getLayerZoom);
    NCB_PROPERTY(primaryLayer, getPrimaryLayer, setPrimaryLayer);
    NCB_PROPERTY(layerWidth, getLayerWidth, setLayerWidth);
    NCB_PROPERTY(layerHeight, getLayerHeight, setLayerHeight);
    NCB_PROPERTY(innerWidth, getInnerWidth, setInnerWidth);
    NCB_PROPERTY(innerHeight, getInnerHeight, setInnerHeight);
};