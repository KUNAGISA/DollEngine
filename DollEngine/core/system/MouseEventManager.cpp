#include "MouseEventManager.h"

DE_BEGIN

MouseEventManager::MouseEventManager()
{
    
}

MouseEventManager::~MouseEventManager()
{
    
}

void MouseEventManager::clear()
{
    m_allLayers.clear();
    m_activedLayers.clear();
}

void MouseEventManager::addLayer(Layer* lay)
{
    m_allLayers.push_back(lay);
}

void MouseEventManager::removeLayer(Layer* lay)
{
    m_allLayers.removeOne(lay);
    m_activedLayers.removeOne(lay);
}

void MouseEventManager::onMouseBegan(float x,float y)
{
    m_isMoved = false;
    m_activedLayers.clear();
    QList<Layer*> temp = m_allLayers;
    Q_FOREACH(Layer* lay , temp) {
        double ox=0,oy=0;
        if(lay->m_transInWorld->isPointInside(x,y,ox,oy)) {
            lay->onMouseBegan(ox,oy);
            if(lay->getEnabled()) {
                m_activedLayers.push_back(lay);
            }
            if(lay->getSwallow()) {
                break;
            }
        }
    }
}

void MouseEventManager::onMouseMove(float x,float y)
{
    m_isMoved = true;
    Q_FOREACH(Layer* lay, m_activedLayers) {
        double ox=0,oy=0;
        lay->m_transInWorld->isPointInside(x,y,ox,oy);
        lay->onMouseMove(ox,oy);
    }
}

void MouseEventManager::onMouseEnd(float x,float y)
{
    Q_FOREACH(Layer* lay, m_activedLayers) {
        double ox=0,oy=0;
        lay->m_transInWorld->isPointInside(x,y,ox,oy);
        lay->onMouseEnd(ox,oy);
        if(!m_isMoved) {
            lay->onClick(ox,oy);
        }
    }
    m_activedLayers.clear();
}

void MouseEventManager::onDoubleClick(float x,float y)
{
    QList<Layer*> temp = m_allLayers;
    Q_FOREACH(Layer* lay , temp) {
        double ox=0,oy=0;
        if(lay->m_transInWorld->isPointInside(x,y,ox,oy)) {
            lay->onDoubleClick(ox,oy);
            if(lay->getSwallow()) {
                break;
            }
        }
    }
}

DE_END
