//
//  Transform.h
//  Krkr_GL
//
//  Created by DollStudio on 14/11/5.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__Transform__
#define __Krkr_GL__Transform__

#include "Macros.h"
#include "Types.h"
#include "COM.h"

class Transform
{
public:
    Transform();
    
    virtual ~Transform();
    
    void set(Transform* a,Transform* b);
    void set(Transform* a);
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

#endif /* defined(__Krkr_GL__Transform__) */
