#include "System.h"
#include <QApplication>
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
    delete DE::System::GetInstance();
    if(DE::Console::GetInstance()) {
        QSettings set("def.dcfg",QSettings::IniFormat);
        QRect rect = ((QtConsole*)DE::Console::GetInstance())->geometry();
        set.setValue("consoleRect",rect);
    }
    if(v == 0x88ff){
#ifdef Q_OS_WIN
        QProcess::execute("E:/GitHub/DollEngine/DollEngine/build.bat");
#elif defined(Q_OS_MAC)
        QProcess::execute("/Users/Dollstudio/DollStudio/gitProject/krGL/DollEngine/DollEngine/build.sh");
#endif
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
    return 0;
}
