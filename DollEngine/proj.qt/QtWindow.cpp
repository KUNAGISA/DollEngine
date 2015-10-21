#include "QtWindow.h"
#include "PaintEngine.h"

QtWindow::QtWindow()
{
    
}

void QtWindow::setTitle(const DE::String& v)
{
    m_title = v;
    setWindowTitle(v.c_nstr());
}

void QtWindow::initializeGL()
{
    QOpenGLWidget::initializeGL();
    DE::PaintEngine::GetInstance();
}

void QtWindow::resizeGL(int w,int h)
{
    QOpenGLWidget::resizeGL(w,h);
}

void QtWindow::paintGL()
{
    QOpenGLWidget::paintGL();
}