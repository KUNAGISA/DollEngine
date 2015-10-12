#include "System.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    DE::System::GetInstance()->startup();
    
    return a.exec();
}
