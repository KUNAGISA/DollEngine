#include "Device.h"
#include "BaseCanvas.h"

DE_BEGIN

Device::Device()
    :m_currentCanvas(null)
    ,m_frameInterval(60)
    ,m_deviceTrans(null)
    ,m_layerWidth(1024)
    ,m_layerHeight(768)
    ,m_mainLoopTimerId(0)
{
    setAppPath(QCoreApplication::applicationDirPath());
}

Device::~Device()
{
    if(m_mainLoopTimerId != 0) {
        killTimer(m_mainLoopTimerId);
    }
}

void Device::mainLoop()
{
    if(m_currentCanvas)
    {
        if(getNeedRetouch()) {
            setNeedRetouch(false);
            m_currentCanvas->refreshMouseEvent();
        }
        if(getNeedRedraw()) {
            setNeedRedraw(false);
            m_currentCanvas->update();
        }
    }
}

void Device::startup()
{
    m_mainLoopTimerId = startTimer(1000.0f/m_frameInterval);
}

void Device::setCanvasSize(float w, float h)
{
    if(!m_deviceTrans) {
        m_deviceTrans = new Transform();
    }
    m_layerWidth = w;
    m_layerHeight = h;
    onResize();
}

void Device::setWinSize(float w, float h)
{
    m_winWidth = w;
    m_winHeight = h;
    onResize();
}

void Device::onResize()
{
    if(m_layerHeight == 0 || m_layerWidth == 0) {
        return;
    }
    if(!m_deviceTrans) {
        m_deviceTrans = new Transform();
    }
    float p = m_layerWidth/m_layerHeight;
    float sc_p = m_winWidth/m_winHeight;
    float layZoom=1,layX=0,layY=0;
    if (p > sc_p)
    {
        //上下留边
        layZoom = m_winWidth/m_layerWidth;
        layX = 0;
        layY = (m_winHeight - m_layerHeight * layZoom)/2;
    }
    else
    {
        //左右留边
        layZoom = m_winHeight/m_layerHeight;
        layX = (m_winWidth - m_layerWidth * layZoom)/2;
        layY = 0;
    }
    m_layerZoom = layZoom;
    m_layerLeft = layX;
    m_layerTop = layY;
    
    m_deviceTrans->setX(layX*2/m_winWidth-1);
    m_deviceTrans->setY(-layY*2/m_winHeight+1);
    m_deviceTrans->setScaleX(2/m_winWidth * layZoom);
    m_deviceTrans->setScaleY(-2/m_winHeight * layZoom);
    m_deviceTrans->flush();
}

void Device::setFrameInterval(int v)
{
    if(m_frameInterval == v ) {
        return;
    }
    if(m_mainLoopTimerId != 0) {
        killTimer(m_mainLoopTimerId);
    }
    m_frameInterval = v;
    m_mainLoopTimerId = startTimer(1000.0f/m_frameInterval);
}

void Device::timerEvent(QTimerEvent* )
{
    mainLoop();
}

DE_END
