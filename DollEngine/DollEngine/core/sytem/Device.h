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
    
    void startup(); //脚本入口
    void setDeviceSize(float w,float h);
    
    PROPERTY_CONST(string,AppPath,m_appPath){m_appPath=v;}
    PROPERTY_CONST(string,DataPath,m_dataPath){m_dataPath=v;}
    PROPERTY_CONST(string,SaveDataPath,m_saveDataPath){m_saveDataPath=v;}
    PROPERTY_CONST(string,PatchPath,m_patchPath){m_patchPath=v;}
    
    PROPERTY(Canvas*,CurrentCanvas,m_currentCanvas);
    
    PROPERTY_RO(float,DeviceWidth,m_deviceWidth)
    PROPERTY_RO(float,DeviceHeight,m_deviceHeight) //设备大小
    
    PROPERTY(bool,NeedRedraw,m_needRedraw){m_needRedraw=v;}
    PROPERTY(bool,NeedRetouch,m_needRetouch){m_needRetouch=v;}
protected:
//    void timerEvent(QTimerEvent*event );
    
protected:
};

DE_END

#endif /* defined(__DollEngine__Device__) */
