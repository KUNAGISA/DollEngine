#include "MainMenu.h"
#include "ui_MainMenu.h"
#include "ProjectDirSelect.h"

static ProjectDirSelect* s_pds=NULL;

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_actionSetProjectPath_triggered()
{
    if (!s_pds) {
        s_pds = new ProjectDirSelect(this);
    }
    s_pds->show();
}
