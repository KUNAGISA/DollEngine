#include "Console.h"
#include "ui_Console.h"

Console::Console(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);
}

Console::~Console()
{
    delete ui;
}
