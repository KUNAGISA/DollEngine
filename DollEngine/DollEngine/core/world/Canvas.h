//
//  Canvas.h
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Canvas__
#define __DollEngine__Canvas__

#include "Units.h"
#include "GameObject.h"
#include "Transform.h"

DE_BEGIN

class Canvas {
    
    
public:
    Canvas();
    
    void initializeGL();
    void paintGL();
    void resizeGL(float width,float height);
    
    
    PROPERTY(bool, Visible, m_visible);
    PROPERTY(GameObject*,WorldObject,m_worldObject);
    
    PROPERTY_RO(float,LayerWidth,m_LayerWidth)
    PROPERTY_RO(float,LayerHeight,m_LayerHeight) //逻辑大小
    PROPERTY_RO(float,LayerLeft,m_LayerLeft)
    PROPERTY_RO(float,LayerTop,m_LayerTop)
    PROPERTY_RO(float,LayerZoom,m_LayerZoom)
protected:
    void* m_window;
};

DE_END

#endif /* defined(__DollEngine__Canvas__) */
