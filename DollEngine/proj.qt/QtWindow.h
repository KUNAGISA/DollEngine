#ifndef QTWINDOW_H
#define QTWINDOW_H

#include <QMainWindow>
#include "Window.h"
#include "CoreTypes.h"

namespace Ui {
class QtWindow;
}

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
};

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
    void keyReleaseEvent(QKeyEvent * event);
    void closeEvent(QCloseEvent *);
private:
    Ui::QtWindow *ui;
};

DE_END

#endif // QTWINDOW_H
