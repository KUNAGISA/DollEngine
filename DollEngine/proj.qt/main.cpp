#include "System.h"
#include <QApplication>
#include <QDebug>
#include <QSettings>
#include <QProcess>
#include "QtConsole.h"
#include "Console.h"
#include "PaintEngine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    DE::System::GetInstance()->startup();
    int v = a.exec();
    if(DE::Console::GetInstance()) {
        QSettings set("def.dcfg",QSettings::IniFormat);
        QRect rect = ((QtConsole*)DE::Console::GetInstance())->geometry();
        set.setValue("consoleRect",rect);
    }
    if(v == 0x88ff){
        QProcess::execute("E:/GitHub/DollEngine/DollEngine/build.bat");
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
    return 0;
}
