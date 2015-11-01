//
//  CharacterInfo.h
//  DollEngine
//
//  Created by DollStudio on 15/5/16.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__CharacterInfo__
#define __DollEngine__CharacterInfo__

#include "ImageInfo.h"

DE_BEGIN

class CharacterInfo : public ImageInfo
{
public:
    CharacterInfo();
    ~CharacterInfo();
    PROPERTY(FontData*, Font, m_font){m_font=v;}
};

DE_END

#endif /* defined(__DollEngine__CharacterInfo__) */
