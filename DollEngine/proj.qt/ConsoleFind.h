#ifndef CONSOLEFIND_H
#define CONSOLEFIND_H

#include <QWidget>

namespace Ui {
class ConsoleFind;
}

class QtConsole;
class ConsoleFind : public QWidget
{
    Q_OBJECT
    
public:
    explicit ConsoleFind(QWidget *parent = 0);
    ~ConsoleFind();
    static ConsoleFind* GetInstance(QtConsole* console) {
        static ConsoleFind* g_instance = NULL;
        if(!g_instance) {
            g_instance  = new ConsoleFind();
        }
        g_instance->console = console;
        return g_instance;
    }
    QtConsole* console;
    void focusEdit();
private slots:
    void on_findup_clicked();
    
    void on_finddown_clicked();
    
private:
    Ui::ConsoleFind *ui;
};

#endif // CONSOLEFIND_H
