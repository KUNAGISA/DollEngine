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
                                                     this->getWidth(),
                                                     this->getHeight(),
                                                     this->getBufferPitch(),
                                                     4 * this->getWidth(),
                                                     colorSpace,
                                                     info | kCGBitmapByteOrder32Big);
        
        CGContextClearRect(context, CGRectMake(0, 0, this->getWidth(), this->getHeight()));
        CGContextDrawImage(context, CGRectMake(0, 0, this->getWidth(), this->getHeight()), cgImage);
        
        CGContextRelease(context);
        CFRelease(colorSpace);
        return true;
    }
    return false;
}

DE_END

