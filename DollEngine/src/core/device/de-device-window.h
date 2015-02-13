//
//  de-device-window.h
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_device_window__
#define __DollEngine__de_device_window__

#include "de-functions.h"


NAMESPACE_DE_DEVICE
class device_window
{
public:
    void hideMouseCursor();//隐藏鼠标（ios中为隐藏点击时出现的小动画）
    void setInnerSize(float width, float height);//设置逻辑宽高
    void setLayerSize(float x,float h);
    void setSize(float width, float height);//设置窗口大小（ios和setInnerSize相同用途
    PROPERTY(float, InnerWidth, m_innerWidth);//逻辑宽度
    PROPERTY(float, InnerHeight, m_innerHeight);//逻辑高度
    PROPERTY(float, Width, m_width);//窗口宽度
    PROPERTY(float, Height, m_height);//高度
    PROPERTY(float, LayerWidth, m_layerWidth);//根节点坐标
    PROPERTY(float, LayerHeight, m_layerHeight);//根节点坐标
    PROPERTY_RO(float, LayerLeft, m_layerLeft);//根节点坐标
    PROPERTY_RO(float, LayerTop, m_layerTop);//根节点坐标
    PROPERTY_RO(float, LayerZoom, m_layerZoom);//根节点缩放率
    PROPERTY_CONST(wstring, Caption, m_caption){m_caption=v;}//窗口标题
    
    void visit();
protected:
    bool m_needReViewPort;
};
NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_device_window__) */
