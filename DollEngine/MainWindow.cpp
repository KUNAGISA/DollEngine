#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ProjectDirSelect.h"
#include "Device.h"

using namespace DE;
static ProjectDirSelect* s_pds=NULL;
static MainWindow* s_instance=NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s_instance = this;
    QSettings set("default.config",QSettings::IniFormat);
    QString v = set.value("project_dir").toString();
    if(v != "") {
        Device::GetInstance()->setDataPath(v);
        Device::GetInstance()->setCurrentCanvas(MainWindow::getCanvas());
        Device::GetInstance()->startup();
    }
}

MainWindow* MainWindow::GetInstance()
{
    return s_instance;
}

MainWindow::~MainWindow()
{
    delete ui;
}

DE::BaseCanvas* MainWindow::getCanvas()
{
    return ui->openGLWidget;
}

void MainWindow::on_actionGongchengmulu_triggered()
{
    if (!s_pds) {
        s_pds = new ProjectDirSelect(this);
    }
    s_pds->show();
}
