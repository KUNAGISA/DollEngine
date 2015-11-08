//
//  ColorRect.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/26.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "ColorRect.h"
#include "System.h"
#include "PaintEngine.h"
#include "Storages.h"

DE_BEGIN

ColorRect::ColorRect()
    :m_r(0)
{
}

ColorRect::~ColorRect()
{
}

bool ColorRect::loadSize(int w,int h,int r)
{
    ImageInfo* info = new ImageInfo();
    if(info->loadWithSize(w,h,r)) {
        m_r = r;
        setInfo(info);
        NEED_REDRAW;
        return true;
    }
    else {
        delete info;
        DM("图片加载失败");
        return false;
    }
}

void ColorRect::setR(int v)
{
    if(v != m_r) {
        loadSize(getPaintWidth(),getPaintHeight(),v);
    }
}
DE_END
