#ifndef LAYER_H
#define LAYER_H

#include "CoreTypes.h"
#include "Device.h"
#include "Transform.h"
#include "SpriteFrame.h"
#include "Effect.h"

DE_BEGIN
class Layer
{
public:
    Layer();
    virtual ~Layer();
    
    bool loadImages(const QString& path,const QString& plist="");
    void draw();
    void onPaint();
    void transform();
    void refreshMouseEvent();
    void addChild(Layer* lay);
    void removeChild(Layer* lay,bool isRelease);
    void removeFromParent(bool isRelease);
    void sortChildren();
    PROPERTY_CONST(GradientColor,Color,m_color){m_color=v;NEED_REDRAW;}
    PROPERTY(Layer*,Parent,m_parent);
    PROPERTY(int, ZOrder,m_zOrder);
    PROPERTY(bool,Enabled,m_enabled){if(v!=m_enabled) {m_enabled=v;NEED_RETOUCH;}}
    PROPERTY(bool,AllChildEnabled,m_allChildEnabled){if(v!=m_allChildEnabled) {m_allChildEnabled=v;NEED_RETOUCH;}}
    PROPERTY(bool,Swallow,m_swallow){m_swallow=v;}
    
    LAYER_PROPERTY_FUNC(Left,X)
    LAYER_PROPERTY_FUNC(Top,Y)
    LAYER_PROPERTY_FUNC(Width,Width)
    LAYER_PROPERTY_FUNC(Height,Height)
    LAYER_PROPERTY_FUNC(AnchorX,AnchorX)
    LAYER_PROPERTY_FUNC(AnchorY,AnchorY)
    LAYER_PROPERTY_FUNC(ScaleX,ScaleX)
    LAYER_PROPERTY_FUNC(ScaleY,ScaleY)
    LAYER_PROPERTY_FUNC(Scale,Scale)
    LAYER_PROPERTY_FUNC(RotationX,RotationX)
    LAYER_PROPERTY_FUNC(RotationY,RotationY)
    LAYER_PROPERTY_FUNC(RotationZ,RotationZ)
    LAYER_PROPERTY_FUNC(Rotation,Rotation)
    LAYER_PROPERTY_FUNC(IgnoreAnchorPoint,IgnoreAnchorPoint)
    
    
public:
    bool onMouseBegan(float x,float y){qDebug()<<"began"<<x<<y<<this;return true;}
    void onMouseMove(float x,float y){qDebug()<<"move"<<x<<y<<this;}
    void onMouseEnd(float x,float y){qDebug()<<"end"<<x<<y<<this;}
    void onClick(float x,float y){qDebug()<<"click"<<x<<y<<this;}
    void onDoubleClick(float x,float y){qDebug()<<"doubleclick"<<x<<y<<this;}
protected:
    QList<Layer*> m_children;
    Transform* m_transform;
    Transform* m_transInWorld;
    SpriteFrame* m_displayFrame;
    Effect* m_effect;
    bool m_needSortChildren;
    
    friend class MouseEventManager;
};

DE_END

#endif // LAYER_H
