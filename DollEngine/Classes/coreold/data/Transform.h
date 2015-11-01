//
//  Transform.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Transform__
#define __DollEngine__Transform__

#include "CoreUnits.h"

DE_BEGIN


class Transform
{
public:
    Transform();
    virtual ~Transform();
    
    void copy(Transform* src);
    void transform(Transform* v);
public:
    void init();
    void flush();
    void transTo(float inx, float iny, GLV2F* outValue);
    bool pointInside(float x,float y,float& ox,float& oy);
public:
    const kmMat4& getMatrix(){return m_matrix;}
    void setRotation(float v){m_rotationX=m_rotationY=m_rotationZ=v;m_needFlush=true;}
    float getRotation(){return m_rotationX;}
    void setScale(float v){m_scaleX=m_scaleY=v;m_needFlush=true;}
    float getScale(){return m_scaleX;}
public:
    PROPERTY(float , X, m_x){m_x=v;m_needFlush=true;}
    PROPERTY(float , Y, m_y){m_y=v;m_needFlush=true;}
    PROPERTY(float , Width, m_width){m_width=fmaxf(0.0f,v);m_needFlush=true;}
    PROPERTY(float , Height, m_height){m_height=fmaxf(0.0f,v);m_needFlush=true;}
    PROPERTY(float , AnchorX,m_anchorX){m_anchorX=v;m_needFlush=true;}
    PROPERTY(float , AnchorY,m_anchorY){m_anchorY=v;m_needFlush=true;}
    PROPERTY(float , ScaleX,m_scaleX){m_scaleX=v;m_needFlush=true;}
    PROPERTY(float , ScaleY,m_scaleY){m_scaleY=v;m_needFlush=true;}
    PROPERTY(float , RotationX,m_rotationX){m_rotationX=v;m_needFlush=true;}
    PROPERTY(float , RotationY,m_rotationY){m_rotationY=v;m_needFlush=true;}
    PROPERTY(float , RotationZ,m_rotationZ){m_rotationZ=v;m_needFlush=true;}
    PROPERTY(bool, IgnoreAnchorPoint, m_ignoreAnchorPoint){m_ignoreAnchorPoint=v;m_needFlush=true;}
protected:
    kmMat4 m_matrix;
    bool m_needFlush;
};


DE_END

#endif /* defined(__DollEngine__Transform__) */
