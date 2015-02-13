//
//  de-transform.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_transform__
#define __DollEngine__de_transform__

#include "de-functions.h"

NAMESPACE_DE_BEGIN

class transform
{
public:
    transform();
    
    virtual ~transform();
    
    void set(transform* a,transform* b);
    void set(transform* a);
public:
    void init();
    void refresh();
    bool isPointInside(float x,float y);
public:
    const kmMat4& getMatrix(){return m_matrix;}
    void setRotation(float v){m_rotationX=m_rotationY=m_rotationZ=v;m_need_refresh=true;}
    float getRotation(){return m_rotationX;}
    void setScale(float v){m_scaleX=m_scaleY=v;m_need_refresh=true;}
    float getScale(){return m_scaleX;}
public:
    PROPERTY(float , X, m_x){m_x=v;m_need_refresh=true;}
    PROPERTY(float , Y, m_y){m_y=v;m_need_refresh=true;}
    PROPERTY(float , Width, m_width){m_width=fmaxf(0.0f,v);m_need_refresh=true;}
    PROPERTY(float , Height, m_height){m_height=fmaxf(0.0f,v);m_need_refresh=true;}
    PROPERTY(float , AnchorX,m_anchorX){m_anchorX=v;m_need_refresh=true;}
    PROPERTY(float , AnchorY,m_anchorY){m_anchorY=v;m_need_refresh=true;}
    PROPERTY(float , ScaleX,m_scaleX){m_scaleX=v;m_need_refresh=true;}
    PROPERTY(float , ScaleY,m_scaleY){m_scaleY=v;m_need_refresh=true;}
    PROPERTY(float , RotationX,m_rotationX){m_rotationX=v;m_need_refresh=true;}
    PROPERTY(float , RotationY,m_rotationY){m_rotationY=v;m_need_refresh=true;}
    PROPERTY(float , RotationZ,m_rotationZ){m_rotationZ=v;m_need_refresh=true;}
    PROPERTY(bool, IgnoreAnchorPoint, m_ignoreAnchorPoint){m_ignoreAnchorPoint=v;m_need_refresh=true;}
protected:
    kmMat4 m_matrix;
    bool m_need_refresh;
};

NAMESPACE_DE_END

#endif /* defined(__DollEngine__de_transform__) */
