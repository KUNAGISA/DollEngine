#ifndef QTWINDOW_H
#define QTWINDOW_H

#include "Window.h"

class QtWindow : public QOpenGLWidget, DE::Window
{
public:
    QtWindow();
    
protected:
    void initializeGL();
    void resizeGL(int w,int h);
    void paintGL();
};

#endif // QTWINDOW_H
