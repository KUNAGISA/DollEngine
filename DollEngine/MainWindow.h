#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace DE {
class BaseCanvas;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    static MainWindow* GetInstance();
    ~MainWindow();
    
    DE::BaseCanvas* getCanvas();
private slots:
    void on_actionGongchengmulu_triggered();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
