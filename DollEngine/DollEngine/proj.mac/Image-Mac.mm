//
//  Image-Mac.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#import "ViewController.h"
#include "GLImage.h"
#include "Storages.h"
#include "Debug.h"

DE_BEGIN

bool GLImage::loadImages(const string &fullPath)
{
    IOData* pBuffer = Storages::GetFileData(fullPath);
    if (pBuffer)
    {
        CGImageRef CGImage;
        NSData *temp_data = [NSData dataWithBytes:pBuffer->getBuffer() length:pBuffer->getSize()];
        CGImageSourceRef source = CGImageSourceCreateWithData((CFDataRef)temp_data, NULL);
        SAFF_DELETE(pBuffer)
        CGImage = CGImageSourceCreateImageAtIndex(source, 0, NULL);
        if (CGImage == NULL) {
            if (CGImage) CFRelease(CGImage);
            if (source) CFRelease(source);
            return false;
        }
        
        NSUInteger POTWide, POTHigh;
        POTWide = CGImageGetWidth(CGImage);
        POTHigh = CGImageGetHeight(CGImage);
        
        CGContextRef        context = nil;
        CGColorSpaceRef        colorSpace;
        bool                hasAlpha;
        CGImageAlphaInfo    info;
        CGSize                imageSize;
        
        CGImageRef image = CGImage;
        info = CGImageGetAlphaInfo(image);
        hasAlpha = ((info == kCGImageAlphaPremultipliedLast) || (info == kCGImageAlphaPremultipliedFirst) || (info == kCGImageAlphaLast) || (info == kCGImageAlphaFirst) ? YES : NO);
        colorSpace = CGImageGetColorSpace(image);
        imageSize.width = CGImageGetWidth(image);
        imageSize.height = CGImageGetHeight(image);
        
        colorSpace = CGColorSpaceCreateDeviceRGB();
        IOData* data = new IOData();
        data->initWithSize(POTHigh * POTWide * 4);
        info = hasAlpha ? kCGImageAlphaPremultipliedLast : kCGImageAlphaNoneSkipLast;
        context = CGBitmapContextCreate(data->getBuffer(), POTWide, POTHigh, 8, 4 * POTWide, colorSpace, info | kCGBitmapByteOrder32Big);
        CGColorSpaceRelease(colorSpace);
        
        CGRect rect;
        rect.size.width = POTWide;
        rect.size.height = POTHigh;
        rect.origin.x = 0;
        rect.origin.y = 0;
        
        CGContextClearRect(context, rect);
        CGContextTranslateCTM(context, 0, 0);
        CGContextDrawImage(context, rect, image);
        
        setWidth((int)POTWide);
        setHeight((int)POTHigh);
        setData(data);
        CGContextRelease(context);
        
        if (CGImage) CFRelease(CGImage);
        if (source) CFRelease(source);
        return true;
    }
    return false;
}

DE_END
