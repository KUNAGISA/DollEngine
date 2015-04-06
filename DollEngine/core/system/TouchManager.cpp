#include "TouchManager.h"

DE_BEGIN

TouchManager::TouchManager()
{
    
}

TouchManager::~TouchManager()
{
    
}

void TouchManager::clear()
{
    m_allTouchLayers.clear();
}

void TouchManager::addTouchLayer(Layer* lay)
{
    m_allTouchLayers.push_back(lay);
}

void TouchManager::removeTouchLayer(Layer* lay)
{
    m_allTouchLayers.removeOne(lay);
}

DE_END
