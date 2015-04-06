#ifndef BASECANVAS_H
#define BASECANVAS_H

#include "CoreTypes.h"

DE_BEGIN

class Layer;
class BaseCanvas : public QOpenGLWidget
{
public:
    BaseCanvas(QWidget *parent = 0);
    virtual ~BaseCanvas();
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void touchUpdate();
    
//    void resizeEvent(QResizeEvent* e);
    
    PROPERTY(Layer*,PrimaryLayer,m_primaryLayer);
};

DE_END

#endif // BASECANVAS_H
