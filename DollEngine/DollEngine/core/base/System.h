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

class GameObject;
class Character;

class System
{
public:
    System();
    Shared(System)
    virtual ~System();
    
public:
    void mainLoop();
    void initDebugInfo();
    void startup(); //脚本入口
    void setDeviceSize(float w,float h);
    
    PROPERTY_CONST(string,AppPath,m_appPath){m_appPath=v;}
    PROPERTY_CONST(string,DataPath,m_dataPath){m_dataPath=v;}
    PROPERTY_CONST(string,SaveDataPath,m_saveDataPath){m_saveDataPath=v;}
    PROPERTY_CONST(string,PatchPath,m_patchPath){m_patchPath=v;}
    
    PROPERTY_RO(float,DeviceWidth,m_deviceWidth)
    PROPERTY_RO(float,DeviceHeight,m_deviceHeight) //设备大小
    
    PROPERTY(bool,NeedRedraw,m_needRedraw){m_needRedraw=v;}
    
    //debug mode:0不显示console 1显示但不打印tag 2打印tag但不打印macro 3所有都打印
    PROPERTY(int,DebugMode,m_debugMode);
protected:
    void initEnginePaths();
//    void timerEvent(QTimerEvent*event );
    
protected:
    GameObject* m_debugFPS;
    Character* m_debugFPSCOM;
    double m_debugTime;
    int m_debugPrintTime;
};

DE_END

#endif /* defined(__DollEngine__Device__) */
