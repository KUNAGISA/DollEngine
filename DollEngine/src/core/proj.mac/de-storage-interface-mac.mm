//
//  de-storage-interface.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/13.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include "de-storage-interface.h"

NAMESPACE_DE_STORAGE

de_string get_app_path()
{
    static wstring s_app_path;
    if (s_app_path.size() == 0)
    {
        NSString *defaultDBPath = [[NSBundle mainBundle] resourcePath];
        de::convert_utf8_to_wstring(defaultDBPath.UTF8String, s_app_path);
        s_app_path.append(L"/");
    }
    return s_app_path;
}

de_string get_data_path()
{
    static wstring s_document_path;
    if (s_document_path.size() == 0)
    {
        NSArray *path = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
                                                            NSUserDomainMask,
                                                            YES);
        NSString *documentDirectory = [path objectAtIndex:0];
        de::convert_utf8_to_wstring(documentDirectory.UTF8String, s_document_path);
        s_document_path.append(L"/");
    }
    return s_document_path;
}

de_string get_cache_path()
{
    static de_string s_cache_path=L"";
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
            de::convert_utf8_to_wstring(path.UTF8String, s_cache_path);
            [panel close];
        }
        else
        {
            exit(0);
        }
    }
    else
    {
        de::convert_utf8_to_wstring(rootPath.UTF8String, s_cache_path);
    }
    s_cache_path += L"/";
    return s_cache_path;
}

NAMESPACE_DE_END2