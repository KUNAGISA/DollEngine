#include "System.h"
#include "FileInfo.h"
#include "IOData.h"
#include "Storages.h"
#include "PictureData.h"
#include <QCoreApplication>
#include <QApplication>
#include <QFontDatabase>
#include <QDesktopWidget>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QThread>
#include "QtWindow.h"

class OpenUrlThread : public QThread
{
protected:
    void run() Q_DECL_OVERRIDE {
        QDesktopServices::openUrl(_url);
    }
public:
    void setUrl(const DE::String& url){
        _url = QUrl(QString::fromStdWString(url));
    }
    QUrl _url;
};

DE_BEGIN

System::System()
:m_debugMode(1)
,m_isError(false)
,m_delegate(NULL)
{
    System::NeedRedraw = true;
    System::NeedSortTouches = true;
    
#ifdef Q_OS_WIN32
    m_platformName = L"Win32";
#endif
    
#ifdef Q_OS_MAC
    m_platformName = L"MacOS";
#endif
    
    //Data path
    m_dataPath = QCoreApplication::applicationDirPath().toStdString();
    m_dataPath += L"/data/";
    //printf("Data path:%s\n",m_dataPath.c_nstr());
    
    //App path
    m_appPath = QCoreApplication::applicationDirPath().toStdString();
    m_appPath += L"/";
    //printf("App path:%s\n",m_appPath.c_nstr());
    
    //SaveData path
    m_saveDataPath = QCoreApplication::applicationDirPath().toStdString();
    m_saveDataPath += L"/savedata/";
    QDir dir(m_saveDataPath.c_nstr());
    if(!dir.exists()) {
        dir.mkdir(m_saveDataPath.c_nstr());
    }
    //printf("SaveData path:%s\n",m_saveDataPath.c_nstr());
    
    //Patch path
    m_patchPath = QCoreApplication::applicationDirPath().toStdString();
    m_patchPath += L"/patch/";
    QDir dir2(m_patchPath.c_nstr());
    if(!dir2.exists()) {
        dir2.mkdir(m_patchPath.c_nstr());
    }
    //printf("Patch path:%s\n",m_patchPath.c_nstr());
}

System::~System()
{
    stopMainLoop();
    SAFF_DELETE(m_delegate);
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

String System::addFont(const String& path)
{
    FileInfo file(path);
    if (!file.exist()) {
        EM(ERROR_FILE_NOT_EXIST,path);
        return L"";
    }
    auto iter = m_allFontPaths.find(file.absolutePath());
    if (iter == m_allFontPaths.end())
    {
        IOData* data = Storages::GetInstance()->GetFileData(file.absolutePath());
        int _font = QFontDatabase::addApplicationFontFromData(QByteArray((const char*)data->getBuffer(),data->getSize()));
        QStringList familys = QFontDatabase::applicationFontFamilies(_font);
        QString family = familys.at(0);
        String fontName = family.toStdString();
        m_allFontPaths[file.absolutePath()] = fontName;
        auto iter2 = m_allFonts.find(fontName);
        if (iter2 == m_allFonts.end())
        {
            m_allFonts[fontName] = (void*)_font;
            if(m_defFontName.empty()) {
                DM("新增自定义字体:%s(默认字体)",fontName.c_nstr());
                m_defFontName = fontName;
            }
            else {
                DM("新增自定义字体:%s",fontName.c_nstr());
            }
            return fontName;
        }
        return fontName;
    }
    return iter->second;
}

void System::removeFont(const String& fontName)
{
    auto iter = m_allFonts.find(fontName);
    if (iter != m_allFonts.end()) {
        for (auto pair : m_allFontPaths) {
            if (pair.second == fontName) {
                m_allFontPaths.erase(pair.first);
                break;
            }
        }
        QFontDatabase::removeApplicationFont((uintptr_t)iter->second);
        m_allFonts.erase(fontName);
    }
}

void System::openUrl(const String& url)
{
    OpenUrlThread *workerThread = new OpenUrlThread();
    workerThread->connect(workerThread, &OpenUrlThread::finished, workerThread, &QObject::deleteLater);
    workerThread->setUrl(url);
    workerThread->start();
    qDebug()<<url.c_nstr();
//    
}

void System::stopMainLoop()
{
    QtWindow::GetInstance()->stopTimer();
}

void System::startMainLoop()
{
    QtWindow::GetInstance()->startTimer();
}

DE_END
