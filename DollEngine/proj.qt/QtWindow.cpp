#include "QtWindow.h"
#include "ui_QtWindow.h"

DE_BEGIN

QtWindow::QtWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtWindow)
{
    ui->setupUi(this);
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
