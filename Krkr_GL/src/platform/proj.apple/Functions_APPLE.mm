//
//  Functions.cpp
//  Krkr_GL
//
//  Created by DollStudio on 14-9-1.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "Functions.h"
#include "StringUtils.h"

const wstring& get_app_path()
{
    static wstring s_app_path;
    if (s_app_path.size() == 0)
    {
        NSString *defaultDBPath = [[NSBundle mainBundle] resourcePath];
        StringUtils::ConvertUtf8ToUnicode(defaultDBPath.UTF8String, s_app_path);
        s_app_path.append(L"/");
    }
    return s_app_path;
}

const wstring& get_document_path()
{
    static wstring s_document_path;
    if (s_document_path.size() == 0)
    {
        NSArray *path = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
                                                            NSUserDomainMask,
                                                            YES);
        NSString *documentDirectory = [path objectAtIndex:0];
        StringUtils::ConvertUtf8ToUnicode(documentDirectory.UTF8String, s_document_path);
        s_document_path.append(L"/");
    }
    return s_document_path;
}


