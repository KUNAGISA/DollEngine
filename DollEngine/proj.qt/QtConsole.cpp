#include "QtConsole.h"
#include "ui_QtConsole.h"
#include "System.h"

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

void QtConsole::Print(const tjs_char *msg)
{
    if(DE::System::GetInstance()->getDebugMode() > 0){
        show();
    }
    else {
        return;
    }
    const char* t = DE::String(msg).c_nstr();
    ui->textEdit->append(t);
}

void QtConsole::keyReleaseEvent(QKeyEvent * event)
{
    if(event->matches(QKeySequence::Refresh)) {
        qApp->exit( 0x88ff );
    }
}
