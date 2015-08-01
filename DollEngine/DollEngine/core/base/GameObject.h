//
//  GameObject.h
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GameObject__
#define __DollEngine__GameObject__

#include "CoreUnits.h"
#include "Transform.h"
#include "Application.h"

DE_BEGIN

class Component;
class Painter;
class GameObject
{
public:
    GameObject();
    virtual ~GameObject();
    
    void addComponent(Component* comp);
    virtual void visit(){}
    virtual void onPaint();
    virtual void onTouchUpdate();
    virtual void transform();
    
    PROPERTY(int, Z, m_z){m_z=v;}
    PROPERTY(bool, Enabled, m_enabled){m_enabled=v;NEED_REDRAW;}
    PROPERTY(bool, Visible, m_visible){m_visible=v;NEED_REDRAW;}
    PROPERTY(GameObject*,Parent,m_parent){m_parent=v;NEED_REDRAW;}
    
    PROPERTY_RO(Transform*, TransInWorld, m_transInWorld);
    PROPERTY_RO(Transform*, Transform, m_transform);
    
    PROPERTY(uint32_t, Color, m_color){m_color=v;}
    PROPERTY(int, Opacity, m_opacity){m_opacity=v;}
protected:
    vector<Component*> m_unknowComps;
    vector<Component*> m_updateComps;
    vector<Component*> m_paintComps;
    vector<Component*> m_touchComps;
    
public:
    TRANSFORM_PROPERTY_FUNC(X,X)
    TRANSFORM_PROPERTY_FUNC(Y,Y)
    TRANSFORM_PROPERTY_FUNC(Width,Width)
    TRANSFORM_PROPERTY_FUNC(Height,Height)
    TRANSFORM_PROPERTY_FUNC(AnchorX,AnchorX)
    TRANSFORM_PROPERTY_FUNC(AnchorY,AnchorY)
    TRANSFORM_PROPERTY_FUNC(ScaleX,ScaleX)
    TRANSFORM_PROPERTY_FUNC(ScaleY,ScaleY)
    TRANSFORM_PROPERTY_FUNC(Scale,Scale)
    TRANSFORM_PROPERTY_FUNC(RotationX,RotationX)
    TRANSFORM_PROPERTY_FUNC(RotationY,RotationY)
    TRANSFORM_PROPERTY_FUNC(RotationZ,RotationZ)
    TRANSFORM_PROPERTY_FUNC(Rotation,Rotation)
    TRANSFORM_PROPERTY_FUNC(IgnoreAnchorPoint,IgnoreAnchorPoint)
//
//    
//public:
//    bool onMouseBegan(float x,float y){qDebug()<<"began"<<x<<y<<this;return true;}
//    void onMouseMove(float x,float y){qDebug()<<"move"<<x<<y<<this;}
//    void onMouseEnd(float x,float y){qDebug()<<"end"<<x<<y<<this;}
//    void onClick(float x,float y){qDebug()<<"click"<<x<<y<<this;}
//    void onDoubleClick(float x,float y){qDebug()<<"doubleclick"<<x<<y<<this;}
protected:
    bool m_needSortChildren;
    Color m_realColor;
};

DE_END

#endif /* defined(__DollEngine__GameObject__) */
