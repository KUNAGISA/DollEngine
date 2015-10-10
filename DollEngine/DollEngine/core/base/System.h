//
//  System.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__System__
#define __DollEngine__System__

#include "CoreUnits.h"

DE_BEGIN

class System
{
public:
    System();
    Shared(System)
    virtual ~System();
    
public:
    void mainLoop();
    void startup(); //脚本入口
    void setDeviceSize(float w,float h);
    
    PROPERTY_CONST(String,AppPath,m_appPath){m_appPath=v;}
    PROPERTY_CONST(String,DataPath,m_dataPath){m_dataPath=v;}
    PROPERTY_CONST(String,SaveDataPath,m_saveDataPath){m_saveDataPath=v;}
    PROPERTY_CONST(String,PatchPath,m_patchPath){m_patchPath=v;}
    
    PROPERTY_RO(float,DeviceWidth,m_deviceWidth)
    PROPERTY_RO(float,DeviceHeight,m_deviceHeight) //设备大小
    
    PROPERTY(bool,NeedRedraw,m_needRedraw){m_needRedraw=v;}
    PROPERTY(bool,IsError,m_isError){m_isError=v;}
    
    //debug mode:0不显示console 1显示但不打印tag 2打印tag但不打印macro 3所有都打印
    PROPERTY(int,DebugMode,m_debugMode);
protected:
    void initEnginePaths();
//    void timerEvent(QTimerEvent*event );
    
};

DE_END

#endif /* defined(__DollEngine__Device__) */
