#include "System.h"
#include "FileInfo.h"
#include "IOData.h"
#include "Storages.h"
#include "PictureData.h"
#include <QCoreApplication>
#include <QFontDatabase>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QPen>

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
<<<<<<< HEAD
    auto iter = m_allFonts.find(fontName);
    if (iter == m_allFonts.end()) {
        iter = m_allFonts.find(DEFFONT);
        if(iter == m_allFonts.end()){
            return NULL;
        }
    }
    int findex = (int)iter->second;
    QStringList strList = QFontDatabase::applicationFontFamilies(findex);
    if(strList.size() == 0) {
        return NULL;
    }
    QString fl = strList.at(0);
    QFont font;
    font.setPointSize(fontSize);
    font.setFamily(fl);
    QFontMetrics metric(font);
    int w = metric.width(text.c_nstr());
    QImage img(w,metric.height(),QImage::Format_RGBA8888);
=======
    if(text.empty()) {
        return NULL;
    } 
    auto iter = m_allFonts.find(fontName);
    if (iter == m_allFonts.end()) {
        iter = m_allFonts.find(DEFFONT);
    }
    int nindex = (int)iter->second;
    QStringList fls = QFontDatabase::applicationFontFamilies(nindex);
    if(fls.size() == 0){
        return NULL;
    }
    QString fl = fls.at(0);
    QFont font;
    font.setPointSize(fontSize);
    font.setFamily(fl);
    QString txt = text.c_nstr();
    QFontMetrics metric(font);
    QRect rect = metric.boundingRect(txt);
    int w = rect.width();
    if(w == 0){
        return NULL;
    }
    for(int i=0;i<txt.size();++i) {
        QChar ch = txt.at(i);
        int r = metric.rightBearing(ch);
        int l = metric.leftBearing(ch);
        fd->advance += (r-l);
        if(i == 0) {
            fd->bearingX = metric.leftBearing(ch);//图片应该的orgin偏移量
        }
//        fd->bearingY = metric.descent();
    }
//    fd->advance = metric.averageCharWidth();
//    fd->bearingX = metric.minLeftBearing();//图片应该的orgin偏移量
    fd->bearingY = metric.descent();  
    
    QImage img(w,rect.height(),QImage::Format_RGBA8888_Premultiplied);
    img.fill(0);
>>>>>>> e245759b40580155d7b31cec664e0b25eb932be1
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
