//
//  de-storage-fonts.h
//  DollEngine
//
//  Created by DollStudio on 15/2/21.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_storage_fonts__
#define __DollEngine__de_storage_fonts__

#include "de-functions.h"

NAMESPACE_DE_FONTS

class Fonts
{
public:
    Shared(Fonts);
    Fonts();
    bool addFont(const de_string& path);
    void initDefautFont();
private:
    map<de_string, FT_Face> m_fontFaceByName;
    map<de_string, de_string> m_fontNameByPath;
    FT_Library m_fontLibrary;
};


NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_storage_fonts__) */
