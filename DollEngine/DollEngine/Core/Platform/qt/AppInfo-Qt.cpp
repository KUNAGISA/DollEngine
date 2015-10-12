#include "AppInfo.h"
#include <QCoreApplication>

DE_BEGIN

AppInfo::AppInfo()
:m_debugMode(0)
{
    AppInfo::NeedRedraw = true;
    AppInfo::NeedSortTouches = true;
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

float AppInfo::getDesktopWidth()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = desktopWidget->availableGeometry();
    return deskRect.width();
}
float AppInfo::getDesktopHeight()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = desktopWidget->availableGeometry();
    return deskRect.height();
}

DE_END
