//
//  Functions.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <CoreText/CoreText.h>
#import "WindowDelegate.h"
#include "Functions.h"
#include "Storages.h"
#include "Image.h"
#include "StringUtils.h"

Image* get_image_data(const wstring& fullpath)
{
    bool ret = false;
    IOData* pBuffer = Storages::GetFileData(fullpath);
    if (pBuffer)
    {
        CGImageRef CGImage;
        NSData *temp_data = [NSData dataWithBytes:pBuffer->getBuffer() length:pBuffer->getSize()];
//        cgImage = [[UIImage imageWithData:data] CGImage];
        CGImageSourceRef source = CGImageSourceCreateWithData((CFDataRef)temp_data, NULL);
        SAFF_DELETE_NULL(pBuffer)
        CGImage = CGImageSourceCreateImageAtIndex(source, 0, NULL);
        if (CGImage == NULL) {
            if (CGImage) CFRelease(CGImage);
            if (source) CFRelease(source);
            return null;
        }
        
        NSUInteger POTWide, POTHigh;
        POTWide = CGImageGetWidth(CGImage);
        POTHigh = CGImageGetHeight(CGImage);
        
        Image* pImageinfo = new Image();
        NSUInteger            i;
        CGContextRef        context = nil;
        CGColorSpaceRef        colorSpace;
        unsigned char*        tempData;
        unsigned int*        inPixel32;
        unsigned short*        outPixel16;
        bool                hasAlpha;
        CGImageAlphaInfo    info;
        CGSize                imageSize;
        
        CGImageRef image = CGImage;
        info = CGImageGetAlphaInfo(image);
        hasAlpha = ((info == kCGImageAlphaPremultipliedLast) || (info == kCGImageAlphaPremultipliedFirst) || (info == kCGImageAlphaLast) || (info == kCGImageAlphaFirst) ? YES : NO);
        size_t bpp = CGImageGetBitsPerComponent(image);
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

float get_winframe_height()
{
    return [[[NSApplication sharedApplication] menu] menuBarHeight];
}

float get_winframe_width()
{
    return 0;
}

const wstring& get_cache_path()
{
    static wstring s_cache_path=L"";
    if(s_cache_path != L"") return s_cache_path;
    NSString* rootPath = [[NSUserDefaults standardUserDefaults] stringForKey:@"ROOT_PATH"];
    if (rootPath == nil || [rootPath compare:@""] == NSOrderedSame)
    {
        NSOpenPanel* panel = [NSOpenPanel openPanel];
        [panel setTitle:@"Select engine root path"];
        panel.allowsMultipleSelection = NO;
        panel.canChooseDirectories = YES;
        panel.canChooseFiles = NO;
        if ([panel runModal] == NSFileHandlingPanelOKButton)
        {
            NSString* path = [[panel.URLs objectAtIndex:0] path];
            [[NSUserDefaults standardUserDefaults]setValue:path forKey:@"ROOT_PATH"];
            [[NSUserDefaults standardUserDefaults]synchronize];
            StringUtils::ConvertUtf8ToUnicode(path.UTF8String, s_cache_path);
            [panel close];
        }
        else
        {
            exit(0);
        }
    }
    else
    {
        StringUtils::ConvertUtf8ToUnicode(rootPath.UTF8String, s_cache_path);
    }
    s_cache_path += L"/";
    return s_cache_path;
}

void push_msg(const char* text)
{
    [[WindowDelegate getInstance]pushLog:text];
}
