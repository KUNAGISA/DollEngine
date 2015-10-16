#include "QtWindow.h"
#include "GLCanvas.h"

QtWindow::QtWindow()
{
    
}


void QtWindow::initializeGL()
{
    QOpenGLWidget::initializeGL();
    DE::GLCanvas::GetInstance();
}

void QtWindow::resizeGL(int w,int h)
{
    QOpenGLWidget::resizeGL(w,h);
}

void QtWindow::paintGL()
{
    QOpenGLWidget::paintGL();
}
