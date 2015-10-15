#include "QtWindow.h"

QtWindow::QtWindow()
{
    
}


void QtWindow::initializeGL()
{
    QOpenGLWidget::initializeGL();
    DI->initialize();
}

void QtWindow::resizeGL(int w,int h)
{
    QOpenGLWidget::resizeGL(w,h);
}

void QtWindow::paintGL()
{
    QOpenGLWidget::paintGL();
}
