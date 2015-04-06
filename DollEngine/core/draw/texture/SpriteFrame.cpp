#include "SpriteFrame.h"
#include "DrawEngine.h"

DE_BEGIN
SpriteFrame::SpriteFrame()
    :m_texture(null)
    ,m_rect(RectZero)
    ,m_retainCount(0)
{
    
}

SpriteFrame::~SpriteFrame()
{
    DrawEngine::GetInstance()->removeSpriteFrameCache(this);
    m_texture->release();
}

void SpriteFrame::retain()
{
    m_retainCount++;
}

void SpriteFrame::release()
{
    m_retainCount--;
    if (m_retainCount <= 0) {
        delete this;
    }
}

void SpriteFrame::setTexture(Texture2D* tex)
{
    if(m_texture) {
        m_texture->release();
        m_rect = RectZero;
    }
    m_texture = tex;
    if(m_texture) {
        m_texture->retain();
        m_rect = QRect(0,0,m_texture->width(),m_texture->height());
    }
}

DE_END
