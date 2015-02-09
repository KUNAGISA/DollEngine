//
//  CharFrame.cpp
//  DollEngine
//
//  Created by DollStudio on 14/12/19.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "CharFrame.h"
#include "System.h"
#include "StringUtils.h"
#include "PaintEngine.h"

#define FTLIB System::GetInstance()->getFontLibrary()

CharFrame::CharFrame()
:m_outlineSize(0)
,m_advance(0)
,m_bearingX(0)
,m_bearingY(0)
,m_xMax(0)
,m_yMin(0)
,m_yMax(0)
,m_xMin(0)
{
}

CharFrame::~CharFrame()
{
}

bool CharFrame::initWithConfig(const wstring& str,const wstring& fontName,float fontSize,float outlineSize)
{
    wstring _fontName;
    if (fontName.size() == 0)
    {
        _fontName = DEFFONT;
    }
    else
    {
        _fontName = fontName;
    }
    wstring key = CharFrame::CreateKey(str,_fontName,fontSize,outlineSize);
    if (PaintEngine::GetInstance()->getSpriteFrameByKey(key)) {
        DM("重复创建CharFrame");
        return false;
    }
    FT_Face face = System::GetInstance()->getFont(_fontName);
    if (face == null)
    {
        EM(ERROR_FT_NO_TTF,_fontName.c_str());
        face = System::GetInstance()->getFont(DEFFONT);
        if (!face) {
            EM(ERROR_FT_NO_TTF,DEFFONT);
            ASSERT(null);
        }
    }
    unsigned short charcode = str[0];
    FT_UInt graphIdx = FT_Get_Char_Index(face, (FT_ULong)charcode);
    if (graphIdx == 0)
    {
        face = System::GetInstance()->getFont(DEFFONT);
        graphIdx = FT_Get_Char_Index(face, charcode);
    }
    FT_Error ft_err = FT_Set_Char_Size(face,
                              fontSize*64,
                              fontSize*64,
                              72,72);
    if (ft_err) {
        return false;
    }
    ft_err = FT_Load_Glyph(face, graphIdx, FT_LOAD_DEFAULT);
    if (ft_err) {
        return false;
    }
    if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
    {
        ft_err = FT_Render_Glyph(face->glyph,FT_RENDER_MODE_NORMAL);
    }
    
    int width = face->glyph->bitmap.width;
    int height = face->glyph->bitmap.rows;
    
    kRect frame;
    frame.width = width;
    frame.height = height;
    
    IOData* iodata = new IOData();
    iodata->initWithSize(width*height*4);
    for (int x=0; x<width; ++x)
    {
        for (int y=0; y<height; ++y)
        {
            int idx = y*width*4 + x*4;
            unsigned char* color = face->glyph->bitmap.buffer + y*width + x;
            memset(iodata->getBuffer() + idx, *color, 4);
        }
    }
    
    Image* image = new Image();
    image->setData(iodata);
    image->setWidth(width);
    image->setHeight(height);
    
    Texture2D* tex = new Texture2D();
    if(tex->initWithImage(image))
    {
        if(!initWithTexture(tex))
        {
            delete image;
            delete tex;
            return false;
        }
    }
    delete image;
    PaintEngine::GetInstance()->insertObject(key, this, tex);
    
    //设置基础属性
    setAdvance(face->glyph->metrics.horiAdvance/64);
    setBearingX(face->glyph->metrics.horiBearingX/64);
    setBearingY(face->glyph->metrics.horiBearingY/64);
    setYMin(face->bbox.yMin);
    return true;
}

wstring CharFrame::CreateKey(const wstring& str,const wstring& fontName,float fontSize,float outlineSize)
{
    return StringUtils::StringFromFormat(L"%ls_%ls_%d_%d"
                                  ,str.c_str()
                                  ,fontName.c_str()
                                  ,(int)fontSize
                                  ,(int)outlineSize);
}
