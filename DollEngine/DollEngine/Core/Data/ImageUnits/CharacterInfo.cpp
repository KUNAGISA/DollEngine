//
//  CharacterInfo.cpp
//  DollEngine
//
//  Created by DollStudio on 15/5/16.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "CharacterInfo.h"


DE_BEGIN

CharacterInfo::CharacterInfo()
{
    m_font = new FontData();
}

CharacterInfo::~CharacterInfo()
{
    SAFF_DELETE(m_font);
}


DE_END