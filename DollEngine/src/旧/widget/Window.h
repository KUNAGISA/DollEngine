//
//  Window.h
//  Krkr_GL
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __Krkr_GL__Window__
#define __Krkr_GL__Window__

#include "Functions.h"

class Object;

class Window
{
public:
//    void * _gl_view;
    
public:
    static Window* GetInstance();
    Window();
    virtual ~Window();
    void initGLView();
    void hideMouseCursor();//隐藏鼠标（ios中为隐藏点击时出现的小动画）
    void setInnerSize(float width, float height);//设置逻辑宽高
    void setLayerSize(float x,float h);
    void setSize(float width, float height);//设置窗口大小（ios和setInnerSize相同用途
    void reViewport();
    PROPERTY(Object*, PrimaryLayer, m_primaryLayer){m_primaryLayer = v;}
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
public:
    void visit();
    virtual void onTraversal(){}
protected:
    bool m_needReViewPort;
};

//    void add(Object* obj);//添加自动释放管理对象
//    void beginMove();//模拟窗口移动开始
//    void bringToFront();//将窗口置为最前
//    void close();//关闭窗口
//    void setZoom(float scale);//设置缩放倍率（ios无效
//    void showModal(bool mode);//设置显示模式
//    void update();//强制更新画面内容
//public:
//    PROPERTY(int, HWND, m_HWND){m_HWND=v;}//窗口句柄
//    PROPERTY(int, BorderStyle, m_borderStyle){m_borderStyle=v;}//窗口样式（ios无效
//    PROPERTY(float, Focusable, m_focusable){m_focusable=v;}//窗口焦距活的可能（ios无效
//    PROPERTY(float, FocusedLayer, m_focusedLayer){m_focusedLayer=v;}//焦点图层（刚刚接受点击事件的图层
//    PROPERTY(bool, FullScreen, m_fullScreen){m_fullScreen=v;}//全屏化（ios无效
//    PROPERTY(int, ImeMode, m_imeMode){m_imeMode=v;}//输入法模式（ios中为回车的样式
//    PROPERTY(int, InnerSunken, m_innerSunken){m_innerSunken=v;}//绘图区域样式（ios无效
//    PROPERTY(float, Left, m_left){m_left=v;}//窗口坐标（ios无效
//    PROPERTY(Window*, MainWindow, m_mainWindow){m_mainWindow=v;}//主窗口对象
//    PROPERTY(float, Menu, m_menu){m_menu=v;}//菜单对象
//    PROPERTY(int, MouseCursorState, m_mouseCursorState){m_mouseCursorState=v;}//鼠标状态（ios无效
//    PROPERTY(Object*, PrimaryLayer, m_primaryLayer){if(!m_primaryLayer) m_primaryLayer=v;}//根节点
//    PROPERTY(bool, ShowScrollBars, m_showScrollBars){m_showScrollBars=v;}//使画面可拖拽
//    PROPERTY(bool, StayOnTop, m_stayOnTop){m_stayOnTop=v;}//使保持在最上方
//    PROPERTY(float, Top,m_top){m_top=v;}//窗口坐标
//    PROPERTY(bool, TrapKey, m_trapKey){m_trapKey=v;}//是否捕获键盘输入事件
//    PROPERTY(bool, UseMouseKey, m_useMouseKey){m_useMouseKey=v;}//是否使用鼠标键
//    PROPERTY(bool, Visible, m_visible){m_visible=v;}//窗口是否显示
//public:
//    void onActivate(){}//当窗口激活到前台时
//    void onClick(){}//当窗口被点击时
//    void onCloseQuery(){}//窗口关闭前的询问（ios无效
//    void onDeactivate(){}//当窗口被放到后台时
//    void onDoubleClick(){}//当窗口被双击时
//    void onFileDrop(){}//当文件拖拽到窗口时（ios无效
//    void onKeyDown(){}//当按键按下时（ios无效
//    void onKeyPress(){}//当输入文字时
//    void onKeyUp(){}//当按键弹起时（ios无效
//    void onMouseDown(){}//当鼠标按下
//    void onMouseEnter(){}//当鼠标经过（ios为按下且经过时
//    void onMouseLeave(){}//当鼠标离开（ios为按下且离开时
//    void onMouseMove(){}//当鼠标移动（ios为按下且移动时
//    void onMouseUp(){}//当鼠标松开
//    void onMouseWheel(){}//当鼠标滚轮滚动
//    void onPopupHide(){}//当弹窗关闭
//    void onResize(){}//当窗口重新设置大小
//

#endif /* defined(__Krkr_GL__Window__) */
