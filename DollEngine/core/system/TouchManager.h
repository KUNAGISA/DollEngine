#ifndef TOUCHMANAGER_H
#define TOUCHMANAGER_H

#include "CoreTypes.h"
#include "Layer.h"

DE_BEGIN

class TouchManager
{
public:
    TouchManager();
    Shared(TouchManager)
    ~TouchManager();
    
    void clear();
    void addTouchLayer(Layer* lay);
    void removeTouchLayer(Layer* lay);
private:
    QList<Layer*> m_allTouchLayers;
};

DE_END

#endif // TOUCHMANAGER_H
