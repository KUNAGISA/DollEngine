//
//  PictureData-iOS.mm
//  DollEngine
//
//  Created by DollStudio on 15/10/9.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include <QImage>
#include "PictureData.h"
#include "IOData.h"
#include "Storages.h"

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

DE_END

