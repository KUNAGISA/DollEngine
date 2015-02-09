//
//  Object.h
//  Krkr_GL
//
//  Created by ios开发－b on 14/12/25.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__Object__
#define __Krkr_GL__Object__

#include "Functions.h"
#include "COM.h"
#include "System.h"
#include "Transform.h"

class Transform;
class ActionBase;
class Object
{
    
public:
    Object();
    ~Object();
    
    //当遍历时
    virtual void onPaint(){}
    //从源Object复制
    virtual void assign(Object* src);
    virtual void visit();
    virtual void transform();
    void priority(bool v=true);
    
    // TODO: 新增“寄存”机制，可以将这个Object寄存到另外一个Object下
    //   这样在当前Object执行visit时不会触发onPaint及遍历子层visit
    //   当寄存的Object执行visit时才会触发，直到Object“回收”
    //   这个功能是为了提供诸如：英雄放技能，需要除了英雄之外的其他内容都黑屏——这样的功能
    
    PROPERTY_RO(Transform*, WorldTrans, m_worldTrans);
    PROPERTY_RO(Transform*, Transform, m_transform);
    PROPERTY(bool, Visible, m_visible);
    PROPERTY(Object*, Parent, m_parent);
    PROPERTY(int, Z, m_z);
    PROPERTY(bool, Enabled, m_enabled);
    PROPERTY(int, Priority, m_priority){m_priority=v;}
    PROPERTY(int, PriorityMax, m_priorityMax){m_priorityMax=v;}
    PROPERTY(float, Opacity, m_opacity);
    PROPERTY(float, RealyOpacity, m_realyOpacity){m_realyOpacity=v;}
    
#define _OBJECT_PROPERTY_FUNC(NAME,VALUE) \
void set##NAME(float v) \
{\
if (m_transform) { \
m_transform->set##VALUE(v);\
System::GetInstance()->setTransChanged(true);\
}\
}\
float get##NAME()\
{\
if (m_transform) {\
return m_transform->get##VALUE();\
}\
return 0;\
}
    
    _OBJECT_PROPERTY_FUNC(Left,X)
    _OBJECT_PROPERTY_FUNC(Top,Y)
    _OBJECT_PROPERTY_FUNC(Width,Width)
    _OBJECT_PROPERTY_FUNC(Height,Height)
    _OBJECT_PROPERTY_FUNC(AnchorX,AnchorX)
    _OBJECT_PROPERTY_FUNC(AnchorY,AnchorY)
    _OBJECT_PROPERTY_FUNC(ScaleX,ScaleX)
    _OBJECT_PROPERTY_FUNC(ScaleY,ScaleY)
    _OBJECT_PROPERTY_FUNC(Scale,Scale)
    _OBJECT_PROPERTY_FUNC(RotationX,RotationX)
    _OBJECT_PROPERTY_FUNC(RotationY,RotationY)
    _OBJECT_PROPERTY_FUNC(RotationZ,RotationZ)
    _OBJECT_PROPERTY_FUNC(Rotation,Rotation)
    _OBJECT_PROPERTY_FUNC(IgnoreAnchorPoint,IgnoreAnchorPoint)
    
    
public:
    void addAction(ActionBase* act);
    void removeAction(ActionBase* act);
    virtual void addChild(Object* src);
    virtual void removeChild(Object* src);
protected:
    list<Object*> m_children;
    list<Object*>::iterator m_iterInParent;
    bool m_needSortChild;
    set<ActionBase*> m_actions;
};

#endif /* defined(__Krkr_GL__Object__) */
