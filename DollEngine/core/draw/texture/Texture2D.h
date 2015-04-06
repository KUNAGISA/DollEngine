#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "CoreTypes.h"

DE_BEGIN

class Texture2D : public QOpenGLTexture
{
public:
    Texture2D(Target target);
    Texture2D(const QImage & image, MipMapGeneration genMipMaps = GenerateMipMaps);
    virtual ~Texture2D();
    void retain();
    void release();
    PROPERTY_RO(int,RetainCount,m_retainCount)
    PROPERTY_CONST(QString,CacheKey,m_cacheKey){m_cacheKey=v;}
};

DE_END
#endif // TEXTURE2D_H
