//
//  GLCache.cpp
//  DollEngine
//
//  Created by DollStudio on 15/5/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GLCache.h"
#include "Transform.h"
#include "TextFrame.h"
#include "GLProgram.h"
#include "NormalProgram.h"
#include "FileInfo.h"
#include "Debug.h"
#include "GLImage.h"

DE_BEGIN

string GLCache::GetKeyByFont(const string& str,const string& fontName,int fontSize,int outlineSize)
{
    return StringWithFormat("%s_%s_%d_%d"
                            ,str.c_str()
                            ,fontName.c_str()
                            ,fontSize
                            ,outlineSize);
}


GLCache::GLCache()
{
    FT_Init_FreeType(&m_fontLibrary);
}

TextFrame* GLCache::addText(const string& text,const string& fontName,int fontSize)
{
    string _fontName;
    if (fontName.empty() || text == "") {
        _fontName = DEFFONT;
    }
    else {
        _fontName = fontName;
    }
    
    if (fontSize == 0 || text == "") {
        fontSize = DEFFONTSIZE;
    }
    
    string key = GetKeyByFont(text,fontName,fontSize,0);
    
    auto iter = m_allSpriteFrames.find(key);
    if (iter != m_allSpriteFrames.end()) {
        return dynamic_cast<TextFrame*>(iter->second);
    }
    
    TextFrame* frame = new TextFrame();
    GLTexture* tex= null;
    auto iter2 = m_allTextures.find(key);
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {
        FT_Face face = getFont(fontName);
        if (!face) {
            face = getFont(DEFFONT);
        }
        wstring str;
        Utf8ToUnicode((char*)text.c_str(),str);
        unsigned short charcode = str[0];
        FT_UInt graphIdx = FT_Get_Char_Index(face, (FT_ULong)charcode);
        if (graphIdx == 0)
        {
            face = getFont(DEFFONT);
            graphIdx = FT_Get_Char_Index(face, charcode);
        }
        FT_Error ft_err = FT_Set_Char_Size(face,
                                           fontSize*64,
                                           fontSize*64,
                                           72,72);
        if(ft_err) {
            return null;
        }
        ft_err = FT_Load_Glyph(face, graphIdx, FT_LOAD_DEFAULT);
        if(ft_err) {
            return null;
        }
        if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
        {
            ft_err = FT_Render_Glyph(face->glyph,FT_RENDER_MODE_NORMAL);
            if(ft_err) {
                return null;
            }
        }
        
        int width = face->glyph->bitmap.width;
        int height = face->glyph->bitmap.rows;
        
        Rect rect;
        rect.width = width;
        rect.height = height;
        
        IOData* iodata = new IOData();
        iodata->initWithSize(width*height*4);
        for (int x=0; x<width; ++x) {
            for (int y=0; y<height; ++y) {
                int idx = y*width*4 + x*4;
                unsigned char* color = face->glyph->bitmap.buffer + y*width + x;
                memset(iodata->getBuffer() + idx, *color, 4);
            }
        }
        
        GLImage* image = new GLImage();
        image->setData(iodata);
        image->setWidth(width);
        image->setHeight(height);
        
        tex = new GLTexture();
        if(tex->initWithImage(image)) {
            delete image;
        }
        else {
            delete image;
            delete tex;
            delete frame;
            return null;
        }
        frame->setAdvance((int)(face->glyph->metrics.horiAdvance/64));
        frame->setBearingX((int)(face->glyph->metrics.horiBearingX/64));
        frame->setBearingY((int)(face->glyph->metrics.horiBearingY/64));
        frame->setYMin((int)(face->bbox.yMin));
    }

    frame->setTexture(tex);
    
    m_allSpriteFrames[key] = frame;
    frame->setCacheKey(key);
    frame->retain();
    return frame;
}

GLTexture* GLCache::addTexture(const string& picKey)
{
    FileInfo file(picKey);
    if (!file.exist()) {
        throw Debug::throwMsg(ERROR_FILE_EXIST_FAILD,picKey);
    }
    auto iter2 = m_allTextures.find(file.absolutePath());
    GLTexture* tex=null;
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {
        GLImage image;
        if(image.loadImages(file.absolutePath()))
        {
            tex = new GLTexture();
            tex->initWithImage(&image);
        }
        else {
            throw Debug::throwMsg(ERROR_IMAGE_LOAD_FAILD,picKey);
            return null;
        }
        m_allTextures[file.absolutePath()] = tex;
        tex->setCacheKey(file.absolutePath());
        tex->retain();
    }
    return tex;
}

SpriteFrame* GLCache::addFrame(const string& picKey,const string& plist)
{
    if (plist == "") {
        FileInfo file(picKey);
        if (!file.exist()) {
            throw Debug::throwMsg(ERROR_FILE_EXIST_FAILD,picKey);
        }
        auto iter = m_allSpriteFrames.find(file.absolutePath());
        if (iter != m_allSpriteFrames.end()) {
            return iter->second;
        }
        auto iter2 = m_allTextures.find(file.absolutePath());
        GLTexture* tex=null;
        if(iter2 != m_allTextures.end()) {
            tex = iter2->second;
        }
        else {
            tex = addTexture(picKey);
        }
        SpriteFrame* frame = new SpriteFrame();
        frame->setTexture(tex);
        
        m_allSpriteFrames[file.absolutePath()] = frame;
        frame->setCacheKey(file.absolutePath());
        frame->retain();
        return frame;
    }
    else {
        throw Debug::throwMsg("暂时不支持Plist格式");
        return null;
    }
}

void GLCache::removeSpriteFrameCache(SpriteFrame* frame)
{
    m_allSpriteFrames.erase(frame->getCacheKey());
}

void GLCache::removeTextureCache(GLTexture* frame)
{
    m_allTextures.erase(frame->getCacheKey());
}

FT_Face GLCache::getFont(const string& fontName)
{
    auto iter = m_allFonts.find(fontName);
    if (iter != m_allFonts.end()) {
        return iter->second;
    }
    else {
        if (fontName == DEFFONT) {
            addFont("WenQuanYiMicroHei.ttc");
        }
        return null;
    }
}

string GLCache::addFont(const string& path)
{
    FileInfo file(path);
    if (!file.exist()) {
        throw Debug::throwMsg(ERROR_FILE_EXIST_FAILD,path);
    }
    auto iter = m_allFontPaths.find(file.absolutePath());
    if (iter == m_allFontPaths.end())
    {
        FT_Face face;
        FT_Error ft_err = FT_New_Face(m_fontLibrary, file.absolutePath().c_str(), 0, &face);
        if (ft_err) {
            throw Debug::throwMsg(ERROR_ADDFONT_FAILD);
        }
        ft_err = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
        if (ft_err) {
            FT_Done_Face(face);
            throw Debug::throwMsg(ERROR_ADDFONT_FAILD);
        }
        m_allFontPaths[file.absolutePath()] = face->family_name;
        auto iter2 = m_allFonts.find(face->family_name);
        if (iter2 == m_allFonts.end())
        {
            m_allFonts[face->family_name] = face;
            DM("新增自定义字体:%s",face->family_name);
            return face->family_name;
        }
        FT_Done_Face(face);
        return iter2->first;
    }
    return iter->second;
}

void GLCache::removeFont(const string& fontName)
{
    auto iter = m_allFonts.find(fontName);
    if (iter != m_allFonts.end()) {
        for (auto pair : m_allFontPaths) {
            if (pair.second == fontName) {
                m_allFontPaths.erase(pair.first);
                break;
            }
        }
        
        FT_Done_Face(iter->second);
        m_allFonts.erase(fontName);
    }
}

DE_END