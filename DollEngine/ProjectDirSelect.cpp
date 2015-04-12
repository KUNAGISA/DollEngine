#include "ProjectDirSelect.h"
#include "ui_ProjectDirSelect.h"
#include <QFileDialog>
#include <QSettings>
#include "Device.h"
#include "BaseCanvas.h"

ProjectDirSelect::ProjectDirSelect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectDirSelect)
{
    ui->setupUi(this);
    QSettings set("default.config",QSettings::IniFormat);
    QString v = set.value("project_dir").toString();
    ui->lineEdit->setText(v);
}

ProjectDirSelect::~ProjectDirSelect()
{
    delete ui;
}

void ProjectDirSelect::on_pushButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(NULL,"设置工程目录",ui->lineEdit->text());
    if(path != "")
    {
        ui->lineEdit->setText(path);
    }
}

void ProjectDirSelect::on_buttonBox_accepted()
{
    if (ui->lineEdit->text() == "") {
        return;
    }
    QSettings set("default.config",QSettings::IniFormat);
    set.setValue("project_dir",ui->lineEdit->text());
    DE::Device::GetInstance()->setDataPath(ui->lineEdit->text());
    DE::Device::GetInstance()->setCurrentCanvas(DE::BaseCanvas::GetInstance());
    DE::Device::GetInstance()->startup();
}
