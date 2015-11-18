#include "QtWindow.h"
#include "ui_QtWindow.h"
#include "PaintEngine.h"
#include "System.h"
#include <QOpenGLContext>
#include "Image.h"
#include <QtOpenGL>
#include <QOpenGLFunctions>


class GLWidget : public QOpenGLWidget
{
    bool isClick;
    bool mouseEnabled;
public:
    GLWidget():QOpenGLWidget(NULL){
        
    }
    
    void initializeGL(){
        QOpenGLWidget::initializeGL();
        DE::PaintEngine::GetInstance()->initialize();
    }
    
    void resizeGL(int w,int h) {
        if(w == 0) w = 1;
        if(h == 0) h = 1;
        DE::Window::GetInstance()->Window::setSize(w,h);
        DE::PaintEngine::GetInstance()->resize(w,h);
    }
    
    void paintGL(){
        DE::SystemDelegate* delegate = DE::System::GetInstance()->getDelegate();
        if(delegate){
            delegate->onMainLoop();
        }
    }
    
    void mousePressEvent(QMouseEvent *event)
    {
        isClick = true;
        mouseEnabled = true;
        QPoint pos = event->pos();
        float x = pos.x() - DE::PaintEngine::GetInstance()->getLayerX();
        float y = pos.y() - DE::PaintEngine::GetInstance()->getLayerY();
        x /= DE::PaintEngine::GetInstance()->getLayerZoom();
        y /= DE::PaintEngine::GetInstance()->getLayerZoom();
        if(x < 0 || 
           y < 0 ||
           x > DE::PaintEngine::GetInstance()->getLayerWidth()||
           y > DE::PaintEngine::GetInstance()->getLayerHeight()){
            mouseEnabled = false;
            return;
        }
        y = DE::PaintEngine::GetInstance()->getLayerHeight() - y;
        DE::System::GetInstance()->getDelegate()->onMouseDown(x,y);
    }
    
    void mouseMoveEvent(QMouseEvent *event)
    {
        if(mouseEnabled){
            QPoint pos = event->pos();
            float x = pos.x() - DE::PaintEngine::GetInstance()->getLayerX();
            float y = pos.y() - DE::PaintEngine::GetInstance()->getLayerY();
            x /= DE::PaintEngine::GetInstance()->getLayerZoom();
            y /= DE::PaintEngine::GetInstance()->getLayerZoom();
            isClick = false;
            y = DE::PaintEngine::GetInstance()->getLayerHeight() - y;
            DE::System::GetInstance()->getDelegate()->onMouseMove(x,y);
        }
    }
    
    void mouseReleaseEvent(QMouseEvent *event)
    {
        if(mouseEnabled){
            QPoint pos = event->pos();
            float x = pos.x() - DE::PaintEngine::GetInstance()->getLayerX();
            float y = pos.y() - DE::PaintEngine::GetInstance()->getLayerY();
            x /= DE::PaintEngine::GetInstance()->getLayerZoom();
            y /= DE::PaintEngine::GetInstance()->getLayerZoom();
            
            y = DE::PaintEngine::GetInstance()->getLayerHeight() - y;
            DE::System::GetInstance()->getDelegate()->onMouseUp(x,y);
            if(isClick){
                DE::System::GetInstance()->getDelegate()->onClick(x,y);
            }
        }
    }
    
};


DE_BEGIN



QtWindow::QtWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtWindow)
{
    ui->setupUi(this);
    glWidget = new GLWidget();
    ui->gridLayout->addWidget(glWidget);
    startTimer(15);
    
}

QtWindow::~QtWindow()
{
    delete glWidget;
    delete ui;
}

void QtWindow::setTitle(const DE::String& v)
{
    m_title = v;
    setWindowTitle(v.c_nstr());
}

void QtWindow::setSize(int w, int h)
{
    Window::setSize(w,h);
    QRect r = geometry();
    r.setWidth(w);
    r.setHeight(h);
    setGeometry(r);
    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - r.width())/2, (desktop->height() - r.height())/2);
}

void QtWindow::setVisible(bool visible)
{
    QMainWindow::setVisible(visible);
    Window::setVisible(visible);
}

void QtWindow::keyReleaseEvent(QKeyEvent * event)
{
    if(event->matches(QKeySequence::Refresh)) {
        qApp->exit( 0x88ff );
    }
}

void QtWindow::closeEvent(QCloseEvent *)
{
    qApp->exit( 0 );
}

void QtWindow::timerEvent(QTimerEvent *)
{
    glWidget->update();
}

DE_END
