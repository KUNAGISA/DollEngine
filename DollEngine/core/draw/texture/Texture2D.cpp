#include "Texture2D.h"
#include "DrawEngine.h"

DE_BEGIN

Texture2D::Texture2D(Target target)
    :QOpenGLTexture(target)
    ,m_retainCount(0)
{
    
}

Texture2D::Texture2D(const QImage & image, MipMapGeneration genMipMaps)
    :QOpenGLTexture(image,genMipMaps)
    ,m_retainCount(0)
{
    
}

Texture2D::~Texture2D()
{
    DrawEngine::GetInstance()->removeTextureCache(this);
}

void Texture2D::retain()
{
    m_retainCount++;
}

void Texture2D::release()
{
    m_retainCount--;
    if (m_retainCount <= 0) {
        delete this;
    }
}

DE_END
