#include "QtConsole.h"
#include "ui_QtConsole.h"
#include "System.h"
#include <QSettings>
#include <QKeyEvent>
#include <QDebug>
#include "ConsoleFind.h"

QtConsole::QtConsole(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtConsole)
{
    ui->setupUi(this);
    Console::Instance = this;
    QSettings set("def.dcfg",QSettings::IniFormat);
    QVariant v = set.value("consoleRect");
    if(!v.isNull()) {
        setGeometry(v.toRect());
    }
}

QtConsole::~QtConsole()
{
    delete ui;
}

void QtConsole::Print(const tjs_char *msg)
{
    if(DE::System::GetInstance()->getDebugMode() > 0){
        if(!isVisible())
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
    else if(event->matches(QKeySequence::Find)) {
        ConsoleFind::GetInstance(this)->show();
        ConsoleFind::GetInstance(this)->raise();
    }
}

void QtConsole::find(const QString& f,QTextDocument::FindFlags flag)
{
    bool ret = ui->textEdit->find(f,flag);
    if(ret == false){
        QTextCursor cur = ui->textEdit->textCursor();
        if(flag & QTextDocument::FindBackward) {
            cur.movePosition(QTextCursor::End);
            ui->textEdit->setTextCursor(cur);
            ui->textEdit->find(f,flag);
        }
        else {
            cur.movePosition(QTextCursor::Start);
            ui->textEdit->setTextCursor(cur);
            ui->textEdit->find(f,flag);
        }
    }
}

void QtConsole::on_lineEdit_returnPressed()
{
    evalScripts(ui->lineEdit->text().toStdWString());
    ui->lineEdit->setText("");
}

void QtConsole::on_pushButton_clicked()
{
    evalScripts(ui->lineEdit->text().toStdWString());
    ui->lineEdit->setText("");
}
