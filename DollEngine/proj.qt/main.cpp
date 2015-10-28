#include "System.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    DE::System::GetInstance()->startup();
    return a.exec();
}
