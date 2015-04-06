#ifndef SPRITEFRAME_H
#define SPRITEFRAME_H

#include "CoreTypes.h"
#include "Texture2D.h"

DE_BEGIN
class SpriteFrame
{
public:
    SpriteFrame();
    virtual ~SpriteFrame();
    void retain();
    void release();
    PROPERTY(Texture2D*,Texture,m_texture);
    PROPERTY_CONST(QRect,Rect,m_rect){m_rect=v;}
    PROPERTY_CONST(QString,CacheKey,m_cacheKey){m_cacheKey=v;}
    PROPERTY_RO(int,RetainCount,m_retainCount)
};
DE_END
#endif // SPRITEFRAME_H
