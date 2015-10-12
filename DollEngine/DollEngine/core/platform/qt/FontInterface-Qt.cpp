#include "FontInterface.h"

DE_BEGIN

FontInterface::FontInterface()
{
    
}

ImageData* FontInterface::addText(const String& text,const String& fontName,int fontSize,FontData* fd)
{
    return NULL;
}

String FontInterface::addFont(const String& filePath)
{
    return "";
}

void* FontInterface::getFont(const String& fontName)
{
    return NULL;
}

void FontInterface::removeFont(const String& filePath)
{
    
}

DE_END
