#include "Layer.h"
#include "DrawEngine.h"
#include "TouchManager.h"

DE_BEGIN

Layer::Layer()
    :m_parent(null)
    ,m_displayFrame(null)
    ,m_enabled(false)
{
    m_transform = new Transform();
    m_transInWorld = new Transform();
    m_effect = DrawEngine::GetInstance()->getEffect(DrawEngine::NORMAL_EFFECT);
    m_color.reset();
}

Layer::~Layer()
{
    setEnabled(false);
    TouchManager::GetInstance()->removeTouchLayer(this);
    NEED_RETOUCH;
    NEED_REDRAW;
}

bool Layer::loadImages(const QString& path,const QString& plist)
{
    SpriteFrame* spframe = DrawEngine::GetInstance()->addImage(path,plist);
    if(m_displayFrame) {
        m_displayFrame->release();
    }
    m_displayFrame = spframe;
    m_displayFrame->retain();
    setWidth(m_displayFrame->getRect().width());
    setHeight(m_displayFrame->getRect().height());
    NEED_REDRAW;
}

void Layer::draw()
{
    transform();
    auto iter = m_children.begin();
    for(;iter != m_children.end(); ++iter) {
        if((*iter)->m_zOrder < 0) {
            (*iter)->draw();
        }
        else {
            break;
        }
    }
    
    onPaint();
    
    for(;iter != m_children.end();++iter) {
        (*iter)->draw();
    }
}

void Layer::transform() {
    m_transform->flush();
    if(getParent()) {
        m_transInWorld->set(getParent()->m_transInWorld,m_transform);
    }
    else {
        m_transInWorld->set(Device::GetInstance()->getDeviceTrans(),m_transform);
    }
    m_transInWorld->setWidth(getWidth());
    m_transInWorld->setHeight(getHeight());
}

void Layer::touchUpdate()
{
    if(getEnabled()) {
        if(m_children.size() > 0) {
            auto iter = m_children.end();
            --iter;
            for(;true; --iter)
            {
                (*iter)->touchUpdate();
                if(iter == m_children.begin()) {
                    break;
                }
            }
        }
        TouchManager::GetInstance()->addTouchLayer(this);
    }
}

void Layer::onPaint()
{
    if(m_displayFrame) {
        DrawEngine::GetInstance()->draw(m_displayFrame,m_transInWorld,m_color,m_effect);
    }
}

void Layer::addChild(Layer* lay)
{
    NEED_REDRAW;
    NEED_RETOUCH;
    m_needSortChildren=true;
    lay->removeFromParent(false);
    lay->m_parent = this;
    m_children.append(lay);
}

void Layer::removeChild(Layer* lay,bool isRelease)
{
    if(lay->m_parent == this) {
        NEED_REDRAW;
        NEED_RETOUCH;
        m_children.removeOne(lay);
        lay->m_parent = NULL;
        if(isRelease) {
            delete lay;
        }
    }
    else {
        throw Debug::throwMsg("[Layer::removeChild]父类不正确");
    }
}

void Layer::removeFromParent(bool isRelease)
{
    if(m_parent) {
        getParent()->removeChild(this,isRelease);
    }
}

void Layer::sortChildren()
{
    if(m_needSortChildren) {
        m_needSortChildren=false;
        qSort(m_children.begin(),m_children.end(),[](Layer* a,Layer* b){
            return a->m_zOrder < b->m_zOrder;
        });
    }
}

void Layer::setZOrder(int v)
{
    m_zOrder=v;
    m_parent->m_needSortChildren=true;
    NEED_REDRAW;
    NEED_RETOUCH;
}

void Layer::setParent(Layer* lay)
{
    lay->addChild(this);
}

void Layer::setEnabled(bool v)
{
    if(m_enabled != v) {
        m_enabled = v;
        NEED_RETOUCH;
    }
}

DE_END
