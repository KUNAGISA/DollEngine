#include "QtConsole.h"
#include "ui_QtConsole.h"

DE::Console* DE::Console::Instance = NULL;

QtConsole::QtConsole(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtConsole)
{
    ui->setupUi(this);
    Console::Instance = this;
}

QtConsole::~QtConsole()
{
    delete ui;
}

void QtConsole::setVisible(bool visible)
{
    if(visible){
        show();
    }
    else {
        hide();
    }
}

bool QtConsole::getVisible()
{
    return !isHidden();
}
