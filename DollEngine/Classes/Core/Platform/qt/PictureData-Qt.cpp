//
//  PictureData-iOS.mm
//  DollEngine
//
//  Created by DollStudio on 15/10/9.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include <QImage>
#include <QFontDatabase>
#include <QPainter>
#include <QPen>
#include <QApplication>
#include "PictureData.h"
#include "IOData.h"
#include "Storages.h"
#include "System.h"

DE_BEGIN

bool PictureData::loadFromFile(const DE::String &fullPath)
{
    QImage image(fullPath.c_nstr());
    if(image.isNull()){
        return false;
    }
    setWidth(image.width());
    setHeight(image.height());
    IOData* imgData = new IOData();
    imgData->initWithSize(getWidth() * getHeight() * 4);
    QImage imagegl = image.convertToFormat(QImage::Format_RGBA8888);
    memcpy(imgData->getBuffer(),imagegl.bits(),imgData->getSize());
    setData(imgData);
    return true;
}

PictureData* PictureData::addText(const String& text,const String& fontName,int fontSize,FontData* fd)
{
    if(text.empty()) {
        return NULL;
    }
    //在之前调用的地方判断过defname是否存在了
    int nindex = (int)System::GetInstance()->getFont(fontName);
    
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
        qDebug()<<txt<<metric.charWidth(txt,0)<<fd->advance << l;
        fd->advance += metric.charWidth(txt,0);
        if(i == 0) {
            fd->bearingX = -l;//图片应该的orgin偏移量
        }
    }
    fd->bearingY = metric.ascent()-1;
    
    QImage img(w,rect.height(),QImage::Format_RGBA8888);
    img.fill(0);
    
    QPainter painter(&img);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    
    QPen pen = painter.pen();
    pen.setColor(Qt::white);
    painter.setFont(font);
    painter.setPen(pen);
    
    painter.drawText(img.rect(),Qt::AlignLeft|Qt::AlignTop,txt);
    
    PictureData* data = new PictureData();
    data->setWidth(img.width());
    data->setHeight(img.height());
    IOData* imgData = new IOData();
    imgData->initWithSize(data->getWidth() * data->getHeight() * 4);
    memcpy(imgData->getBuffer(),img.bits(),imgData->getSize());
    data->setData(imgData);
    return data;
}

DE_END

