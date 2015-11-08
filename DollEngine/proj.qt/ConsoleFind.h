#ifndef CONSOLEFIND_H
#define CONSOLEFIND_H

#include <QWidget>

namespace Ui {
class ConsoleFind;
}

class ConsoleFind : public QWidget
{
    Q_OBJECT
    
public:
    explicit ConsoleFind(QWidget *parent = 0);
    ~ConsoleFind();
    
private:
    Ui::ConsoleFind *ui;
};

#endif // CONSOLEFIND_H
