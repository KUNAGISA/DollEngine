#ifndef FONTINTERFACE_H
#define FONTINTERFACE_H

#include "CoreUnits.h"
#include "ImageData.h"

DE_BEGIN

class FontInterface
{
public:
    FontInterface();
    Shared(FontInterface)
    
    ImageData* addText(const String& text,const String& fontName,int fontSize,FontData* fd);
    bool addFont(const String& filePath);
    void removeFont(const String& filePath);
    
    static String GetKeyByFont(const String& str,const String& fontName,int fontSize,int outlineSize) {
        return String::fromFormat("%s_%s_%d_%d",str.c_str(),fontName.c_str(),fontSize,outlineSize);
    }
};

DE_END

#endif // FONTINTERFACE_H
