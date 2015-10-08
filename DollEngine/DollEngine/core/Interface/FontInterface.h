#ifndef FONTINTERFACE_H
#define FONTINTERFACE_H

#include "CoreUnits.h"
#include "ImageData.h"

DE_BEGIN

class FontInterface
{
public:
    FontInterface();
    ~FontInterface();
    Shared(FontInterface)
    
    ImageData* addText(const String& text,const String& fontName,int fontSize,FontData* fd);
    String addFont(const String& filePath);
    void* getFont(const String& font);
    void removeFont(const String& filePath);
    
    static String GetKeyByFont(const String& str,const String& fontName,int fontSize,int outlineSize) {
        return String::fromFormat("%s_%s_%d_%d",str.c_str(),fontName.c_str(),fontSize,outlineSize);
    }
    
private:
    map<String,void*> m_allFonts;
    map<String,String> m_allFontPaths;
};

DE_END

#endif // FONTINTERFACE_H
