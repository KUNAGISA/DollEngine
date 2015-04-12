#ifndef BASECANVAS_H
#define BASECANVAS_H

#include "CoreTypes.h"

DE_BEGIN

class Layer;
class BaseCanvas : public QOpenGLWindow
{
public:
    BaseCanvas();
    static BaseCanvas* GetInstance();
    virtual ~BaseCanvas();
    
    virtual void	initializeGL();
    virtual void	paintGL();
    virtual void	resizeGL(int w, int h);
    
public:
    void refreshMouseEvent();
    
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
//    void resizeEvent(QResizeEvent* e);
    
    PROPERTY(Layer*,PrimaryLayer,m_primaryLayer);
};

DE_END

#endif // BASECANVAS_H
