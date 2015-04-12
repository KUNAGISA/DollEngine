#include "BaseCanvas.h"
#include "Layer.h"
#include "DrawEngine.h"
#include "MouseEventManager.h"
#include <QPainter>

DE_BEGIN

static BaseCanvas* s_instance=null;
static QMenuBar* bar;
BaseCanvas::BaseCanvas()
    :m_primaryLayer(null)
{
    s_instance = this;
    QSettings set("default.config",QSettings::IniFormat);
    QString v = set.value("project_dir").toString();
    if(QSysInfo::productType() == "ios") {
        v = QCoreApplication::applicationDirPath();
        v += "/data";
    }
    if(v != "") {
        QDir dir(v);
        if(!dir.exists()) {
            qDebug()<<"工程目录未找到";
            return;
        }
        Device::GetInstance()->setDataPath(v);
        Device::GetInstance()->setCurrentCanvas(this);
        qDebug() << "BaseCanvas Size:" <<geometry();
        return;
    }
    qDebug()<<"工程目录为空";
}

BaseCanvas* BaseCanvas::GetInstance()
{
    return s_instance;
}

BaseCanvas::~BaseCanvas()
{
}

void BaseCanvas::initializeGL()
{
    QOpenGLWindow::initializeGL();
    DrawEngine::GetInstance()->initializeGL();
    
    if (Device::GetInstance()->getGLInitHandler()) {
        Device::GetInstance()->getGLInitHandler()();
        Device::GetInstance()->startup();
    }
}

void BaseCanvas::paintGL()
{
    makeCurrent();
    DrawEngine::GetInstance()->clearGL();
    if(m_primaryLayer) {
        m_primaryLayer->draw();
    }
    QOpenGLWindow::paintGL();
}

void BaseCanvas::resizeGL(int width, int height)
{
    QOpenGLWindow::resizeGL(width, height);
    Device::GetInstance()->setWinSize(width,height);
//    qDebug()<<"[BaseCanvas ResizeGL]\n{\n"
//    <<"\twidth:"<<width<<"\n"
//    <<"\theight:"<<height<<"\n"
//    <<"\tlayerLeft:"<<Device::GetInstance()->getLayerLeft()<<"\n"
//    <<"\tlayerTop:"<<Device::GetInstance()->getLayerTop()<<"\n"
//    <<"\tlayerWidth:"<<Device::GetInstance()->getLayerWidth()<<"\n"
//    <<"\tlayerHeight:"<<Device::GetInstance()->getLayerHeight()<<"\n"
//    <<"\tlayerZoom:"<<Device::GetInstance()->getLayerZoom()<<"\n"
//    <<"}";
    DrawEngine::GetInstance()->resizeGL(width,height);
    NEED_REDRAW;
}

void BaseCanvas::refreshMouseEvent()
{
    MouseEventManager::GetInstance()->clear();
    if(m_primaryLayer) {
        m_primaryLayer->refreshMouseEvent();
    }
}

void BaseCanvas::setPrimaryLayer(Layer* lay)
{
    if(m_primaryLayer) {
        delete m_primaryLayer;
        m_primaryLayer = null;
    }
    if(lay->getParent()) {
        lay->removeFromParent(false);
    }
    m_primaryLayer = lay;
}

void BaseCanvas::mousePressEvent(QMouseEvent * event)
{
    MouseEventManager::GetInstance()->onMouseBegan(event->x(),event->y());
}

void BaseCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    MouseEventManager::GetInstance()->onMouseEnd(event->x(),event->y());
}

void BaseCanvas::mouseMoveEvent(QMouseEvent *event)
{
    MouseEventManager::GetInstance()->onMouseMove(event->x(),event->y());
}

void BaseCanvas::mouseDoubleClickEvent(QMouseEvent *event)
{
    MouseEventManager::GetInstance()->onDoubleClick(event->x(),event->y());
}

DE_END
