#ifndef QTCONSOLE_H
#define QTCONSOLE_H

#include <QWidget>
#include "Console.h"

namespace Ui {
class QtConsole;
}

class QtConsole : public QWidget, DE::Console
{
    Q_OBJECT
    
public:
    explicit QtConsole(QWidget *parent = 0);
    ~QtConsole();
    
    void setVisible(bool visible);
    bool getVisible();
private:
    Ui::QtConsole *ui;
};

#endif // QTCONSOLE_H
