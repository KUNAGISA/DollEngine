//
//  ImageData-iOS.mm
//  DollEngine
//
//  Created by DollStudio on 15/10/9.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "PictureData.h"
#include "Storages.h"
#include "System.h"
#include <ft2build.h>
#include FT_FREETYPE_H

DE_BEGIN

bool PictureData::loadFromFile(const DE::String &fullPath)
{
    IOData* ioData = Storages::GetFileData(fullPath);
    if (ioData)
    {
        CGImageRef cgImage;
        NSData *data;
        
        data = [NSData dataWithBytes:ioData->getBuffer() length:ioData->getSize()];
        cgImage = [[UIImage imageWithData:data] CGImage];
        delete ioData;
        setWidth(CGImageGetWidth(cgImage));
        setHeight(CGImageGetHeight(cgImage));
        CGImageAlphaInfo info = CGImageGetAlphaInfo(cgImage);
        CGColorSpaceRef colorSpace = CGImageGetColorSpace(cgImage);
        if (colorSpace)
        {
            info = kCGImageAlphaPremultipliedLast;
        }
        else
        {
            return false;
        }
        IOData* imgData = new IOData();
        imgData->initWithSize(getWidth() * getHeight() * 4);
        colorSpace = CGColorSpaceCreateDeviceRGB();
        CGContextRef context = CGBitmapContextCreate(imgData->getBuffer(),
                                                     (size_t)this->getWidth(),
                                                     (size_t)this->getHeight(),
                                                     8,
                                                     (size_t)(4 * this->getWidth()),
                                                     colorSpace,
                                                     info|kCGBitmapByteOrder32Big);
        
        CGContextClearRect(context, CGRectMake(0, 0, this->getWidth(), this->getHeight()));
        CGContextDrawImage(context, CGRectMake(0, 0, this->getWidth(), this->getHeight()), cgImage);
        setData(imgData);
        CGContextRelease(context);
        CFRelease(colorSpace);
        return true;
    }
    return false;
}

PictureData* PictureData::addText(const String& text,const String& fontName,int fontSize,FontData* fd)
{
    if (text.empty()) {
        return NULL;
    }
    FT_Face face = (FT_Face)System::GetInstance()->getFont(fontName);
    
    unsigned short charcode = text[0];
    FT_UInt graphIdx = FT_Get_Char_Index(face, (FT_ULong)charcode);
    if (graphIdx == 0)
    {
        face = (FT_Face)System::GetInstance()->getFont(System::GetInstance()->getDefFontName());
        graphIdx = FT_Get_Char_Index(face, charcode);
    }
    FT_Error ft_err = FT_Set_Char_Size(face,
                                       fontSize*64,
                                       fontSize*64,
                                       72,72);
    if(ft_err) {
        return NULL;
    }
    ft_err = FT_Load_Glyph(face, graphIdx, FT_LOAD_DEFAULT);
    if(ft_err) {
        return NULL;
    }
    if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
    {
        ft_err = FT_Render_Glyph(face->glyph,FT_RENDER_MODE_NORMAL);
        if(ft_err) {
            return NULL;
        }
    }
    
    int width = face->glyph->bitmap.width;
    int height = face->glyph->bitmap.rows;
    
    Rect rect;
    rect.width = width;
    rect.height = height;
    
    IOData* iodata = new IOData();
    iodata->initWithSize(width*height*4);
    for (int x=0; x<width; ++x) {
        for (int y=0; y<height; ++y) {
            int idx = y*width*4 + x*4;
            unsigned char* color = face->glyph->bitmap.buffer + y*width + x;
            memset(iodata->getBuffer() + idx, *color, 4);
        }
    }
    
    PictureData* image = new PictureData();
    image->setData(iodata);
    image->setWidth(width);
    image->setHeight(height);
    
    fd->advance = (int)(face->glyph->metrics.horiAdvance/64);
    fd->bearingX = (int)(face->glyph->metrics.horiBearingX/64);
    fd->bearingY = (int)(face->glyph->metrics.horiBearingY/64);
    fd->yMin = (int)(face->bbox.yMin/64);
    fd->yMax = (int)(face->bbox.yMax/64);
    fd->xMin = (int)(face->bbox.xMin/64);
    fd->xMax = (int)(face->bbox.xMax/64);
    return image;
}

DE_END

