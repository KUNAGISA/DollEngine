//
//  Functions.cpp
//  DollEngine
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "Functions.h"
#include "Storages.h"
#include "Image.h"

Image* get_image_data(const wstring& fullpath)
{
    long length;
    unsigned char* pBuffer = Storages::GetFileData(fullpath, &length);
    if (pBuffer)
    {
        CGImageRef cgImage;
        NSData *data;
        
        data = [NSData dataWithBytes:pBuffer length:length];
        cgImage = [[UIImage imageWithData:data] CGImage];
        delete [] pBuffer;
        Image* pImageinfo = new Image();
        pImageinfo->setWidth(CGImageGetWidth(cgImage));
        pImageinfo->setHeight(CGImageGetHeight(cgImage));
        CGImageAlphaInfo info = CGImageGetAlphaInfo(cgImage);
        CGColorSpaceRef colorSpace = CGImageGetColorSpace(cgImage);
        if (colorSpace)
        {
            info = kCGImageAlphaPremultipliedLast;
        }
        else
        {
            delete pImageinfo;
            return null;
        }
        pImageinfo->setBuffer(new unsigned char[pImageinfo->getWidth() * pImageinfo->getHeight() * 4]);
        colorSpace = CGColorSpaceCreateDeviceRGB();
        CGContextRef context = CGBitmapContextCreate(pImageinfo->getBuffer(),
                                                     pImageinfo->getWidth(),
                                                     pImageinfo->getHeight(),
                                                     pImageinfo->getBufferPitch(),
                                                     4 * pImageinfo->getWidth(),
                                                     colorSpace,
                                                     info | kCGBitmapByteOrder32Big);
        
        CGContextClearRect(context, CGRectMake(0, 0, pImageinfo->getWidth(), pImageinfo->getHeight()));
        CGContextDrawImage(context, CGRectMake(0, 0, pImageinfo->getWidth(), pImageinfo->getHeight()), cgImage);
        
        CGContextRelease(context);
        CFRelease(colorSpace);
        
        return pImageinfo;
    }
    return null;
}

float get_menubar_height()
{
    return 0;
}

const wstring& get_cache_path()
{
    static wstring s_cache_path;
    if (s_cache_path == "")
    {
        NSArray *cache = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
        NSString *cachePath = [cache objectAtIndex:0] ;
        s_cache_path = cachePath.UTF8String;
        s_cache_path.append("/");
    }
    return s_cache_path;
}