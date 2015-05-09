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
#include "Transform.h"

DE_BEGIN

class GameObject;
class Canvas {
    
    
public:
    Canvas();
    ~Canvas();
    
    void visit();
    
    
    PROPERTY(bool, Visible, m_visible);
    PROPERTY(GameObject*,WorldObject,m_worldObject);
    
    PROPERTY(float,LayerWidth,m_layerWidth){m_layerWidth=v;}
    PROPERTY(float,LayerHeight,m_layerHeight){m_layerHeight=v;} //逻辑大小
    PROPERTY(float,LayerLeft,m_layerLeft){m_layerLeft=v;}
    PROPERTY(float,LayerTop,m_layerTop){m_layerTop = v;}
    PROPERTY(float,LayerZoom,m_layerZoom){m_layerZoom=v;}
protected:
    void* m_window;
};

DE_END

#endif /* defined(__DollEngine__Canvas__) */
