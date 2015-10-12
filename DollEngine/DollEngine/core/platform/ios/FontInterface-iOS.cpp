#include "FontInterface.h"
#include "FileInfo.h"
#include <ft2build.h>
#include FT_FREETYPE_H


DE_BEGIN

static FT_Library g_fontLibrary=NULL;

FontInterface::FontInterface()
{
    FT_Init_FreeType(&g_fontLibrary);
}

FontInterface::~FontInterface()
{
    FT_Done_FreeType(g_fontLibrary);
}

void* FontInterface::getFont(const String& fontName)
{
    auto iter = m_allFonts.find(fontName);
    if (iter != m_allFonts.end()) {
        return iter->second;
    }
    else {
        if (fontName == DEFFONT) {
            addFont("WenQuanYiMicroHei.ttc");
        }
        return NULL;
    }
}

ImageData* FontInterface::addText(const String& text,const String& fontName,int fontSize,FontData* fd)
{
    FT_Face face = (FT_Face)getFont(fontName);
    if (!face) {
        face = (FT_Face)getFont(DEFFONT);
    }
    unsigned short charcode = text[0];
    FT_UInt graphIdx = FT_Get_Char_Index(face, (FT_ULong)charcode);
    if (graphIdx == 0)
    {
        face = (FT_Face)getFont(DEFFONT);
        graphIdx = FT_Get_Char_Index(face, charcode);
    }
    FT_Error ft_err = FT_Set_Char_Size(face,
                                       fontSize*64,
                                       fontSize*64,
                                       72,72);
    if(ft_err) {
        return NULL;
    }
    ft_err = FT_Load_Glyph(face, graphIdx, FT_LOAD_DEFAULT);
    if(ft_err) {
        return NULL;
    }
    if (face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
    {
        ft_err = FT_Render_Glyph(face->glyph,FT_RENDER_MODE_NORMAL);
        if(ft_err) {
            return NULL;
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
    
    ImageData* image = new ImageData();
    image->setData(iodata);
    image->setWidth(width);
    image->setHeight(height);
    
    fd->advance = (int)(face->glyph->metrics.horiAdvance/64);
    fd->bearingX = (int)(face->glyph->metrics.horiBearingX/64);
    fd->bearingY = (int)(face->glyph->metrics.horiBearingY/64);
    fd->yMin = (int)(face->bbox.yMin/64);
    fd->yMax = (int)(face->bbox.yMax/64);
    fd->xMin = (int)(face->bbox.xMin/64);
    fd->xMax = (int)(face->bbox.xMax/64);
    return image;
}

String FontInterface::addFont(const String& path)
{
    FileInfo file(path);
    if (!file.exist()) {
        EM(ERROR_FILE_NOT_EXIST,path);
    }
    auto iter = m_allFontPaths.find(file.absolutePath());
    if (iter == m_allFontPaths.end())
    {
        FT_Face face;
        FT_Error ft_err = FT_New_Face(g_fontLibrary, file.absolutePath().utf8Value().c_str(), 0, &face);
        if (ft_err) {
            EM(ERROR_ADDFONT_FAILD);
        }
        ft_err = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
        if (ft_err) {
            FT_Done_Face(face);
            EM(ERROR_ADDFONT_FAILD);
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

void FontInterface::removeFont(const String& fontName)
{
    auto iter = m_allFonts.find(fontName);
    if (iter != m_allFonts.end()) {
        for (auto pair : m_allFontPaths) {
            if (pair.second == fontName) {
                m_allFontPaths.erase(pair.first);
                break;
            }
        }
        
        FT_Done_Face((FT_Face)iter->second);
        m_allFonts.erase(fontName);
    }
}

DE_END
