//
//  Window.h
//  DollEngine
//
//  Created by DollStudio on 15/7/15.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Window__
#define __DollEngine__Window__

#include "CoreUnits.h"

DE_BEGIN

class GameObject;
class RTT;
class Painter;

class Window
{
public:
    Window();
    ~Window();
    static Window* GetInstance();
    void initialize(float w,float h,float s);
    void onInitFinished();
    void visit();
    void beginTransition(bool isblack);
    void transWithCrossFade(float dt);
    void transFinished();
    GameObject* getTransNode(){return m_transNode;}
    PROPERTY(bool, Visible, m_visible){m_visible=v;}
    
    PROPERTY(GameObject*,World,m_world);
protected:
    void* m_deviceWindow;
    GameObject* m_transNode;
    Painter* m_transBlack;
    RTT* m_transRTT;
};

DE_END

#endif /* defined(__DollEngine__Window__) */
