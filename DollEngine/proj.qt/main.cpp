#include "System.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    DE::System::GetInstance()->startup();
    int v = a.exec();
    if(v == 0x88ff){
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
    return 0;
}
