#include "System.h"
#include <QCoreApplication>

DE_BEGIN

System::System()
:m_debugMode(1)
,m_isError(false)
{
    System::NeedRedraw = true;
    System::NeedSortTouches = true;
    //Data path
    m_dataPath = QCoreApplication::applicationDirPath().toStdString();
    m_dataPath += L"/data/";
    
    //App path
    m_appPath = QCoreApplication::applicationDirPath().toStdString();
    m_appPath += L"/";
    
    //SaveData path
    m_saveDataPath = QCoreApplication::applicationDirPath().toStdString();
    m_saveDataPath += L"/savedata/";
    
    //Patch path
    m_patchPath = QCoreApplication::applicationDirPath().toStdString();
    m_patchPath += L"/patch/";
}

float System::getDesktopWidth()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = desktopWidget->availableGeometry();
    return deskRect.width();
}
float System::getDesktopHeight()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = desktopWidget->availableGeometry();
    return deskRect.height();
}

DE_END
