#ifndef MOUSEEVENTMANAGER_H
#define MOUSEEVENTMANAGER_H

#include "CoreTypes.h"
#include "Layer.h"

DE_BEGIN

class MouseEventManager
{
public:
    MouseEventManager();
    Shared(MouseEventManager)
    ~MouseEventManager();
    
    void clear();
    void addLayer(Layer* lay);
    void removeLayer(Layer* lay);
    
    void onMouseBegan(float x,float y);
    void onMouseMove(float x,float y);
    void onMouseEnd(float x,float y);
    void onDoubleClick(float x,float y);
private:
    QList<Layer*> m_allLayers;
    QList<Layer*> m_activedLayers;
    bool m_isMoved;
};

DE_END

#endif // MOUSEEVENTMANAGER_H
