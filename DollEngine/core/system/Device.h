#ifndef DEVICE_H
#define DEVICE_H

#include "CoreTypes.h"
#include "Transform.h"

DE_BEGIN
class BaseCanvas;
class Device : public QObject
{
public:
    Device();
    Shared(Device)
    virtual ~Device();
    
    void mainLoop();
    
    void startup();
    void setCanvasSize(float w,float h);
    void setWinSize(float w,float h);
    void onResize();
    
    PROPERTY_CONST(QString,AppPath,m_appPath){m_appPath=v;}
    PROPERTY_CONST(QString,DataPath,m_dataPath){m_dataPath=v;}
    PROPERTY_CONST(QString,PatchPath,m_patchPath){m_patchPath=v;}
    PROPERTY(BaseCanvas*,CurrentCanvas,m_currentCanvas){m_currentCanvas=v;}
    PROPERTY(int,FrameInterval,m_frameInterval);
    PROPERTY(std::function<void()>, GLInitHandler, m_glInitHandler){m_glInitHandler=v;}
    
    PROPERTY(bool,NeedRedraw,m_needRedraw){m_needRedraw=v;}
    PROPERTY(bool,NeedRetouch,m_needRetouch){m_needRetouch=v;}
    PROPERTY_RO(Transform*,DeviceTrans,m_deviceTrans)
    PROPERTY_RO(float,LayerWidth,m_layerWidth)
    PROPERTY_RO(float,LayerHeight,m_layerHeight)
    PROPERTY_RO(float,LayerLeft,m_layerLeft)
    PROPERTY_RO(float,LayerTop,m_layerTop)
    PROPERTY_RO(float,LayerZoom,m_layerZoom)
    PROPERTY_RO(float,WinWidth,m_winWidth)
    PROPERTY_RO(float,WinHeight,m_winHeight)
protected:
    void timerEvent(QTimerEvent*event );
    
protected:
    int m_mainLoopTimerId;
};
DE_END
#endif // DEVICE_H
