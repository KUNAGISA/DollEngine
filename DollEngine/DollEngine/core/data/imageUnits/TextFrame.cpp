//
//  TextFrame.cpp
//  DollEngine
//
//  Created by DollStudio on 15/5/16.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "TextFrame.h"


DE_BEGIN

TextFrame::TextFrame()
{
    m_font = new FontData();
}

TextFrame::~TextFrame()
{
    SAFF_DELETE(m_font);
}


DE_END