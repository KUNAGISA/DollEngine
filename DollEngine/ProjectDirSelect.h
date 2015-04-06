#ifndef PROJECTDIRSELECT_H
#define PROJECTDIRSELECT_H

#include <QDialog>

namespace Ui {
class ProjectDirSelect;
}

class ProjectDirSelect : public QDialog
{
    Q_OBJECT
    
public:
    explicit ProjectDirSelect(QWidget *parent = 0);
    ~ProjectDirSelect();
    
private slots:
    void on_pushButton_clicked();
    
    void on_buttonBox_accepted();
    
private:
    Ui::ProjectDirSelect *ui;
};

#endif // PROJECTDIRSELECT_H
