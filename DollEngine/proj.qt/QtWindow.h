#ifndef QTWINDOW_H
#define QTWINDOW_H

#include <QMainWindow>
#include "Window.h"
#include "CoreTypes.h"

namespace Ui {
class QtWindow;
}

class GLWidget;
DE_BEGIN

class QtWindow : public QMainWindow,public DE::Window
{
    Q_OBJECT
    
public:
    explicit QtWindow(QWidget *parent = 0);
    ~QtWindow();
    
    virtual void setTitle(const DE::String& v);
    void setSize(int w, int h);
    void setVisible(bool visible);
    
public:
    void keyReleaseEvent(QKeyEvent * event);
    void closeEvent(QCloseEvent *);
    void timerEvent(QTimerEvent *);
private:
    Ui::QtWindow *ui;
    GLWidget* glWidget;
};

DE_END

#endif // QTWINDOW_H
