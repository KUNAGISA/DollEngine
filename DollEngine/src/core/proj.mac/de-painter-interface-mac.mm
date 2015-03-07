//
//  de-painter-interface-mac.mm
//  DollEngine
//
//  Created by DollStudio on 15/3/7.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include "de-painter-interface.h"
#include "de.h"

NAMESPACE_DE_PAINTER

Image* get_image(const de_string& path)
{
    Image* pImageinfo = null;
    LOAD_FILE(pBuffer,path,pImageinfo)
    if (pBuffer)
    {
        CGImageRef CGImage;
        NSData *temp_data = [NSData dataWithBytes:pBuffer->getBytes() length:pBuffer->getSize()];
        pBuffer->clear();
        CGImageSourceRef source = CGImageSourceCreateWithData((CFDataRef)temp_data, NULL);
        CGImage = CGImageSourceCreateImageAtIndex(source, 0, NULL);
        if (CGImage == NULL) {
            if (CGImage) CFRelease(CGImage);
            if (source) CFRelease(source);
            return null;
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
        de::Data* data = de::Data::DataWithSize(POTHigh * POTWide * 4);
        info = hasAlpha ? kCGImageAlphaPremultipliedLast : kCGImageAlphaNoneSkipLast;
        context = CGBitmapContextCreate(data->getBytes(), POTWide, POTHigh, 8, 4 * POTWide, colorSpace, info | kCGBitmapByteOrder32Big);
        CGColorSpaceRelease(colorSpace);
        
        CGRect rect;
        rect.size.width = POTWide;
        rect.size.height = POTHigh;
        rect.origin.x = 0;
        rect.origin.y = 0;
        
        CGContextClearRect(context, rect);
        CGContextTranslateCTM(context, 0, 0);
        CGContextDrawImage(context, rect, image);
        
        pImageinfo->setWidth((int)POTWide);
        pImageinfo->setHeight((int)POTHigh);
        pImageinfo->setData(data);
        CGContextRelease(context);
        
        if (CGImage) CFRelease(CGImage);
        if (source) CFRelease(source);
        return pImageinfo;
    }
    return null;
}

NAMESPACE_DE_END2