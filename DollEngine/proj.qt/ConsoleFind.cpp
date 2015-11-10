#include "ConsoleFind.h"
#include "ui_ConsoleFind.h"
#include "QtConsole.h"

ConsoleFind::ConsoleFind(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleFind)
{
    ui->setupUi(this);
}

ConsoleFind::~ConsoleFind()
{
    delete ui;
}

void ConsoleFind::on_findup_clicked()
{
    if(ui->caseSensitively->isChecked()){
        console->find(ui->findText->toPlainText(),QTextDocument::FindBackward | QTextDocument::FindCaseSensitively);
    }
    else {
        console->find(ui->findText->toPlainText(),QTextDocument::FindBackward);
    }
}

void ConsoleFind::on_finddown_clicked()
{
    if(ui->caseSensitively->isChecked()){
        console->find(ui->findText->toPlainText(), QTextDocument::FindCaseSensitively);
    }
    else {
        console->find(ui->findText->toPlainText(),0);
    }
}
