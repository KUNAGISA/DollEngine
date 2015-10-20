//
//  PictureData.h
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Image__
#define __DollEngine__Image__

#include "CoreTypes.h"
#include "IOData.h"

DE_BEGIN

class IOData;
class PictureData
{
public:
    enum IMAGE_BUFFER_PITCH
    {
        IMAGE_BUFFER_PITCH_DEFAULT = 8,
        IMAGE_BUFFER_PITCH_8 = IMAGE_BUFFER_PITCH_DEFAULT,
        IMAGE_BUFFER_PITCH_7 = 7,//0xrrggbba
        IMAGE_BUFFER_PITCH_6 = 6,//0xrrggbb
        IMAGE_BUFFER_PITCH_4 = 4,//0xrgba
        IMAGE_BUFFER_PITCH_3 = 3,//0xrgb
        IMAGE_BUFFER_PITCH_2 = 2,//0xaa
    };
public:
    PictureData();
    virtual ~PictureData();
    bool loadFromFile(const String& fullPath);
    static PictureData* createRoundRect(int r);//创建一个圆角矩形的数据
public:
    PROPERTY(IOData*, Data, m_data){m_data=v;}
    PROPERTY(int, Width, m_width){m_width=v;}
    PROPERTY(int, Height, m_height){m_height=v;}
    PROPERTY(IMAGE_BUFFER_PITCH, BufferPitch, m_bufferPitch){m_bufferPitch=v;}
};

DE_END

#endif /* defined(__DollEngine__Image__) */
