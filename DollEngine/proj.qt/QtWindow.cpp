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
