//
//  Image.cpp
//  DollEngine
//
//  Created by DollStudio on 14-9-17.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "Image.h"

Image::Image()
:m_data(null)
,m_width(0)
,m_height(0)
,m_bufferPitch(IMAGE_BUFFER_PITCH_DEFAULT)
{
    
}

Image::~Image()
{
    SAFF_DELETE_NULL(m_data);
}

Image* Image::createRoundRect(int r)
{
    if (r == 0)
    {
        IOData* data = new IOData();
        unsigned int* buffer = new unsigned int[4];
        memset(buffer, 0xff, sizeof(unsigned int)*4);
        data->setBuffer((unsigned char*)buffer);
        data->setSize((sizeof(unsigned int)/sizeof(unsigned char))*4);
        Image* image = new Image();
        image->setData(data);
        image->setWidth(2);
        image->setHeight(2);
        return image;
    }
    int width = r*3;
    int height = width;
    IOData* data = new IOData();
    unsigned int* buffer = new unsigned int[width*height];
    memset(buffer, 0xff, sizeof(unsigned int)*width*height);
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
    data->setBuffer((unsigned char*)buffer);
    data->setSize((sizeof(unsigned int)/sizeof(unsigned char))*width*height);
    Image* image = new Image();
    image->setData(data);
    image->setWidth(width);
    image->setHeight(height);
    return image;
}

