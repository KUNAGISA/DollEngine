//
//  de-painter-image.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/23.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-painter-image.h"
#include "de.h"

NAMESPACE_DE_PAINTER

Image::Image()
:m_data(null)
,m_width(0)
,m_height(0)
,m_bufferPitch(IMAGE_BUFFER_PITCH_DEFAULT)
{
    
}

Image::~Image()
{
    DELETE_OBJ(m_data);
}

Image* Image::createRoundRect(int r)
{
    int width = r*3;
    int height = width;
    if (r == 0)
    {
        width = 2;
        height = 2;
    }
    de::Data* data = de::Data::DataWithSize(width*height*4);
    memset(data->getBytes(), 0xff, width*height*4);
    unsigned int* buffer = (unsigned int*)data->getBytes();
    //左上角
    for (int i = 0; i < r; ++i)
    {
        for (int k = 0; k < r; ++k)
        {
            if ((r-i)*(r-i)+(r-k)*(r-k) >= r*r)
            {
                unsigned int* buf = buffer + width*i+k;
                *buf = 0x00000000;
            }
        }
    }
    //右上角
    for (int i = 0; i < r; ++i)
    {
        for (int k = width-r; k < width; ++k)
        {
            if ((r-i)*(r-i)+(width-1-r-k)*(width-1-r-k) >= r*r)
            {
                unsigned int* buf = buffer + width*i+k;
                *buf = 0x00000000;
            }
        }
    }
    //左下角
    for (int i = height-r; i < height; ++i)
    {
        for (int k = 0; k < r; ++k)
        {
            if ((height-1-r-i)*(height-1-r-i)+(r-k)*(r-k) >= r*r)
            {
                unsigned int* buf = buffer + width*i+k;
                *buf = 0x00000000;
            }
        }
    }
    //右下角
    for (int i = height-r; i < height; ++i)
    {
        for (int k = width-r; k < width; ++k)
        {
            if ((height-1-r-i)*(height-1-r-i)+(width-1-r-k)*(width-1-r-k) >= r*r)
            {
                unsigned int* buf = buffer + width*i+k;
                *buf = 0x00000000;
            }
        }
    }
    data->setBytes((unsigned char*)buffer);
    data->setSize((sizeof(unsigned int)/sizeof(unsigned char))*width*height);
    Image* image = new Image();
    image->setData(data);
    image->setWidth(width);
    image->setHeight(height);
    return image;
}

NAMESPACE_DE_END2
