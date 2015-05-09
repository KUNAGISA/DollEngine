//
//  Device.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Device__
#define __DollEngine__Device__

#include "Units.h"
#include "Canvas.h"

DE_BEGIN

class Device
{
public:
    Device();
    static Device* GetInstance()
    {
        static Device* _instance=NULL;
        if(!_instance) {
            _instance = new Device();
        }
        return  _instance;
    }
    virtual ~Device();
    
    void initialize();
    void initEnginePaths();
    
public:
    void mainLoop();
    
    void startup();
    void setDeviceSize(float w,float h);
    
    PROPERTY_CONST(string,AppPath,m_appPath){m_appPath=v;}
    PROPERTY_CONST(string,DataPath,m_dataPath){m_dataPath=v;}
    PROPERTY_CONST(string,SaveDataPath,m_saveDataPath){m_saveDataPath=v;}
    PROPERTY_CONST(string,PatchPath,m_patchPath){m_patchPath=v;}
    
    PROPERTY(Canvas*,CurrentCanvas,m_currentCanvas);
    PROPERTY(float,FrameInterval,m_frameInterval){m_frameInterval=v;}
    PROPERTY(std::function<void()>, GLInitCallback, m_glInitCallback){m_glInitCallback=v;}
    
    PROPERTY(bool,NeedRedraw,m_needRedraw){m_needRedraw=v;}
    PROPERTY(bool,NeedRetouch,m_needRetouch){m_needRetouch=v;}
    PROPERTY_RO(float,DeviceWidth,m_deviceWidth)
    PROPERTY_RO(float,DeviceHeight,m_deviceHeight) //设备大小
//    PROPERTY_RO(float,LayerWidth,m_layerWidth)
//    PROPERTY_RO(float,LayerHeight,m_layerHeight)
//    PROPERTY_RO(float,LayerLeft,m_layerLeft)
//    PROPERTY_RO(float,LayerTop,m_layerTop)
//    PROPERTY_RO(float,LayerZoom,m_layerZoom)
//    PROPERTY_RO(float,WinWidth,m_winWidth)
//    PROPERTY_RO(float,WinHeight,m_winHeight)
protected:
//    void timerEvent(QTimerEvent*event );
    
protected:
    int m_mainLoopTimerId;
};

DE_END

#endif /* defined(__DollEngine__Device__) */
