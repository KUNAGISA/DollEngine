#include "QtWindow.h"
#include "ui_QtWindow.h"
#include "PaintEngine.h"
#include <QOpenGLContext>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

GLWidget::~GLWidget()
{
}


void GLWidget::initializeGL()
{
    DE::PaintEngine::GetInstance()->initialize();
}

void GLWidget::paintGL()
{
    NEED_REDRAW;
}

void GLWidget::resizeGL(int width, int height)
{
    DE::PaintEngine::GetInstance()->resize(width,height);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
}

void GLWidget::mouseReleaseEvent(QMouseEvent * /* event */)
{
}

DE_BEGIN

QtWindow::QtWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtWindow)
{
    ui->setupUi(this);
    GLWidget* w = new GLWidget(NULL);
    ui->gridLayout->addWidget(w);
}

QtWindow::~QtWindow()
{
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

DE_END
