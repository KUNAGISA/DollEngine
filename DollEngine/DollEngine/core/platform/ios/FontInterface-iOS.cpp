#include "FontInterface.h"
#include "FileInfo.h"
#include <ft2build.h>
#include FT_FREETYPE_H


DE_BEGIN

FontInterface::FontInterface()
{
    FT_Init_FreeType(&m_fontLibrary);
}

FontInterface::~FontInterface()
{
    FT_Done_FreeType(m_fontLibrary);
}

FT_Face FontInterface::getFont(const string& fontName)
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

ImageData* FontInterface::addText(const string& text,const string& fontName,int fontSize,FontData* fd)
{
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

string FontInterface::addFont(const string& path)
{
    FileInfo file(path);
    if (!file.exist()) {
        Debug::throwMsg(ERROR_FILE_EXIST_FAILD,path);
    }
    auto iter = m_allFontPaths.find(file.absolutePath());
    if (iter == m_allFontPaths.end())
    {
        FT_Face face;
        FT_Error ft_err = FT_New_Face(m_fontLibrary, file.absolutePath().c_str(), 0, &face);
        if (ft_err) {
            Debug::throwMsg(ERROR_ADDFONT_FAILD);
        }
        ft_err = FT_Select_Charmap(face, FT_ENCODING_UNICODE);
        if (ft_err) {
            FT_Done_Face(face);
            Debug::throwMsg(ERROR_ADDFONT_FAILD);
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

void FontInterface::removeFont(const string& fontName)
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
