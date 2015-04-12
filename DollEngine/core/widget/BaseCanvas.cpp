#include "BaseCanvas.h"
#include "Layer.h"
#include "DrawEngine.h"
#include "MouseEventManager.h"

DE_BEGIN

BaseCanvas::BaseCanvas(QWidget* parent)
    :QOpenGLWidget(parent)
    ,m_primaryLayer(null)
{
    
}

BaseCanvas::~BaseCanvas()
{
    
}

void BaseCanvas::initializeGL()
{
    DrawEngine::GetInstance()->initializeGL();
}

void BaseCanvas::resizeGL(int width, int height)
{
    Device::GetInstance()->setWinSize(width,height);
    Device::GetInstance()->onResize();
    DrawEngine::GetInstance()->resizeGL(width,height);
    NEED_REDRAW;
}

void BaseCanvas::paintGL()
{
    DrawEngine::GetInstance()->clearGL();
    if(m_primaryLayer) {
        m_primaryLayer->draw();
    }
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
