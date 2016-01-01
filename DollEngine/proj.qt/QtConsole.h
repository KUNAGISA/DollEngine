#ifndef QTCONSOLE_H
#define QTCONSOLE_H

#include <QMainWindow>
#include <QWidget>
#include <QTextEdit>
#include "Console.h"
#include "CoreString.h"


namespace Ui {
class QtConsole;
}

class QtConsole : public QMainWindow, DE::Console
{
    Q_OBJECT
    
public:
    explicit QtConsole(QWidget *parent = 0);
    ~QtConsole();
    
    virtual void Print(const tjs_char *msg);
    virtual void setVisible(bool visible){
        QWidget::setVisible(visible);
    }
    virtual bool getVisible(){return isVisible();}
    
    void find(const QString& f,QTextDocument::FindFlags flag);
private slots:
    void on_lineEdit_returnPressed();
    
    void on_pushButton_clicked();
    
    void on_pushButton_2_clicked();
    
    void on_actionFind_triggered();
    
    void on_actionRefresh_triggered();
    
private:
    Ui::QtConsole *ui;
};

#endif // QTCONSOLE_H
