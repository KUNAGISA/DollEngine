#include "ConsoleFind.h"
#include "ui_ConsoleFind.h"

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
