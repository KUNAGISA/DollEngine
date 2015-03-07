//
//  de-painter-paint.cpp
//  DollEngine
//
//  Created by DollStudio on 15/2/23.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#include "de-painter-paint.h"
#include "de.h"

NAMESPACE_DE_PAINTER

Paint::Paint()
:m_program(null)
,m_spriteFrame(null)
//,m_scale9(false)
,m_imageHeight(0)
,m_imageWidth(0)
,m_leftInside(0)
,m_topInside(0)
,m_rightInside(0)
,m_bottomInside(0)
,m_opacity(1)
{
//    m_program = Engine::GetInstance()->getDefaultProgram();
    for (int i=0; i<9; ++i)
    {
        m_scale9Frame[i] = new SpriteFrame();
        m_scale9Trans[i] = new de::Transform();
    }
}

Paint::~Paint()
{
    for (int i=0; i<9; ++i) {
        delete m_scale9Frame[i];
        delete m_scale9Trans[i];
    }
}

NAMESPACE_DE_END2
