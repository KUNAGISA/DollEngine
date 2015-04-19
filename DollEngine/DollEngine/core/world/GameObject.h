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
#include "BaseComp.h"
#include "Transform.h"

DE_BEGIN

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();
    
    void addComponent(BaseComp* comp);
    void visit();
    void onPaint();
    void transform();
    
    void addChild(GameObject* lay);
    void removeChild(GameObject* lay,bool isRelease);
    void removeFromParent(bool isRelease=true);
    void sortChildren();
    
    PROPERTY(int, Z, m_z){m_z=v;}
    PROPERTY(GameObject*,Parent,m_parent){m_parent=v;}
    
protected:
    vector<BaseComp*> m_unknowComp;
    vector<BaseComp*> m_updateComp;
    vector<BaseComp*> m_paintComp;
    vector<BaseComp*> m_touchComp;
    
    list<GameObject*> m_children;
    list<GameObject*>::iterator m_iterInParent;
//
//    bool loadImages(const QString& path,const QString& plist="");
//    void draw();
//    void refreshMouseEvent();
//    void addChild(GameObject* lay);
//    void removeChild(GameObject* lay,bool isRelease);
//    void removeFromParent(bool isRelease);
//    void sortChildren();
//    PROPERTY_CONST(GradientColor,Color,m_color){m_color=v;NEED_REDRAW;}
//    PROPERTY(int, ZOrder,m_zOrder);
//    PROPERTY(bool,Enabled,m_enabled){if(v!=m_enabled) {m_enabled=v;NEED_RETOUCH;}}
//    PROPERTY(bool,AllChildEnabled,m_allChildEnabled){if(v!=m_allChildEnabled) {m_allChildEnabled=v;NEED_RETOUCH;}}
//    PROPERTY(bool,Swallow,m_swallow){m_swallow=v;}
//    
//    GameObject_PROPERTY_FUNC(Left,X)
//    GameObject_PROPERTY_FUNC(Top,Y)
//    GameObject_PROPERTY_FUNC(Width,Width)
//    GameObject_PROPERTY_FUNC(Height,Height)
//    GameObject_PROPERTY_FUNC(AnchorX,AnchorX)
//    GameObject_PROPERTY_FUNC(AnchorY,AnchorY)
//    GameObject_PROPERTY_FUNC(ScaleX,ScaleX)
//    GameObject_PROPERTY_FUNC(ScaleY,ScaleY)
//    GameObject_PROPERTY_FUNC(Scale,Scale)
//    GameObject_PROPERTY_FUNC(RotationX,RotationX)
//    GameObject_PROPERTY_FUNC(RotationY,RotationY)
//    GameObject_PROPERTY_FUNC(RotationZ,RotationZ)
//    GameObject_PROPERTY_FUNC(Rotation,Rotation)
//    GameObject_PROPERTY_FUNC(IgnoreAnchorPoint,IgnoreAnchorPoint)
//    
//    
//public:
//    bool onMouseBegan(float x,float y){qDebug()<<"began"<<x<<y<<this;return true;}
//    void onMouseMove(float x,float y){qDebug()<<"move"<<x<<y<<this;}
//    void onMouseEnd(float x,float y){qDebug()<<"end"<<x<<y<<this;}
//    void onClick(float x,float y){qDebug()<<"click"<<x<<y<<this;}
//    void onDoubleClick(float x,float y){qDebug()<<"doubleclick"<<x<<y<<this;}
protected:
//    QList<GameObject*> m_children;
    Transform* m_transform;
    Transform* m_transInWorld;
//    SpriteFrame* m_displayFrame;
//    Effect* m_effect;
    bool m_needSortChildren;
//
//    friend class MouseEventManager;
};

DE_END

#endif /* defined(__DollEngine__GameObject__) */
