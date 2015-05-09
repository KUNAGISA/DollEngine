//
//  GameObject.h
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__GameObject__
#define __DollEngine__GameObject__

#include "Units.h"
#include "Transform.h"
#include "Device.h"

DE_BEGIN

class BaseComp;
class Painter;
class GameObject
{
public:
    GameObject();
    virtual ~GameObject();
    
    void addComponent(BaseComp* comp);
    void visit();
    void transform();
    
    void addChild(GameObject* lay);
    void removeChild(GameObject* lay,bool isRelease);
    void removeFromParent(bool isRelease=true);
    void sortChildren();
    
    PROPERTY(int, Z, m_z){m_z=v;}
    PROPERTY(GameObject*,Parent,m_parent){m_parent=v;}
    
    PROPERTY_RO(Transform*, TransInWorld, m_transInWorld);
    PROPERTY_RO(Transform*, Transform, m_transform);
    
protected:
    vector<BaseComp*> m_unknowComp;
    vector<BaseComp*> m_updateComp;
    vector<BaseComp*> m_paintComp;
    vector<BaseComp*> m_touchComp;
    
    list<GameObject*> m_children;
    list<GameObject*>::iterator m_iterInParent;
    
    TRANSFORM_PROPERTY_FUNC(Left,X)
    TRANSFORM_PROPERTY_FUNC(Top,Y)
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
};

DE_END

#endif /* defined(__DollEngine__GameObject__) */
