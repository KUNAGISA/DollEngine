#include "System.h"
#include "FileInfo.h"
#include "IOData.h"
#include "Storages.h"
#include "PictureData.h"
#include <QCoreApplication>
#include <QFontDatabase>

DE_BEGIN

System::System()
:m_debugMode(1)
,m_isError(false)
,m_delegate(NULL)
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

System::~System()
{
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


PictureData* System::addText(const String& text,const String& fontName,int fontSize,FontData* fd)
{
    QFont font;
    font.setPointSize(fontSize);
    auto iter = m_allFonts.find(fontName);
    String fl = fontName;
    if (iter == m_allFonts.end()) {
        iter = m_allFonts.find(DEFFONT);
        fl = DEFFONT;
    }
    font.setFamily(fl.c_nstr());
    QFontMetrics metric(font);
    
    QImage img(metric.width(text.c_nstr()),metric.height(),QImage::Format_RGBA8888);
    QPainter painter(&img);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    
    QPen pen = painter.pen();
    pen.setColor(Qt::white);
    painter.setFont(font);
    painter.setPen(pen);
    
    painter.drawText(img.rect(),Qt::AlignCenter,text.c_nstr());
    
    
    
    PictureData* data = new PictureData();
    data->setWidth(img.width());
    data->setHeight(img.height());
    IOData* imgData = new IOData();
    imgData->initWithSize(data->getWidth() * data->getHeight() * 4);
    memcpy(imgData->getBuffer(),img.bits(),imgData->getSize());
    data->setData(imgData);
    return data;
}

String System::addFont(const String& path)
{
    FileInfo file(path);
    if (!file.exist()) {
        EM(ERROR_FILE_NOT_EXIST,path);
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
            DM("新增自定义字体:%s",fontName.c_nstr());
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
        QFontDatabase::removeApplicationFont((int)iter->second);
        m_allFonts.erase(fontName);
    }
}

DE_END
