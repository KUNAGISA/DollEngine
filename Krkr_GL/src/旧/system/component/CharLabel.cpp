//
//  CharLabel.cpp
//  Krkr_GL
//
//  Created by ios开发－b on 14/12/27.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "CharLabel.h"
#include "Object.h"
#include "PaintEngine.h"
#include "StringUtils.h"

CharLabel::CharLabel()
:m_frame(null)
,m_outlineFrame(null)
,m_x(0)
,m_y(0)
,m_width(0)
,m_fontSize(0)
,m_fontName(DEFFONT)
,m_offsetY(0)
,m_imageHeight(0)
,m_bottom(0)
,m_bearingY(0)
{
    setComName(L"CharLabel");
    setTriggerType(TRIGGER_NONE);
    m_trans = new Transform();
    m_worldTrans = new Transform();
    m_program = PaintEngine::GetInstance()->getDefaultProgram();
}

CharLabel::~CharLabel()
{
    SAFF_RELEASE_NULL(m_frame);
    SAFF_RELEASE_NULL(m_outlineFrame);
    delete m_trans;
    delete m_worldTrans;
}

void CharLabel::setFrame(CharFrame *v)
{
    SAFF_RELEASE(m_frame);
    m_frame = v;
    SAFF_RETAIN(m_frame);
}

void CharLabel::setOutlineFrame(CharFrame *v)
{
    SAFF_RELEASE(m_outlineFrame);
    m_outlineFrame = v;
    SAFF_RETAIN(m_outlineFrame);
}

void CharLabel::refresh()
{
    if (m_wstring.size() == 0)
    {
        setFrame(null);
        m_width = 0;
        return;
    }
    CharFrame* frame = PaintEngine::GetInstance()->addSpriteFrame(m_wstring, m_fontName, m_fontSize);
    setFrame(frame);
    m_width = frame->getAdvance();
    m_bearingY = frame->getBearingY();
    m_imageHeight = frame->getHeight();
    System::GetInstance()->setTransChanged(true);
}

void CharLabel::trigger()
{
    if (!getEnabled() ||!getFrame() || !getObject()) {
        return;
    }
    Transform* objTrans = getObject()->getWorldTrans();
    if(!objTrans)
    {
        return;
    }
    m_trans->setX(getX()+getFrame()->getBearingX());
    m_trans->setY(getY()+getOffsetY());
    m_trans->setWidth(getFrame()->getRect().width);
    m_trans->setHeight(getFrame()->getRect().height);
    m_trans->refresh();
    m_worldTrans->set(objTrans, m_trans);
    m_worldTrans->setWidth(getFrame()->getRect().width);
    m_worldTrans->setHeight(getFrame()->getRect().height);
    float op = getObject()->getRealyOpacity();
    PaintEngine::GetInstance()->draw(m_worldTrans, getFrame(), m_program,Vector2F(getFrame()->getWidth(),getFrame()->getHeight()),Vector4F(op, op, op, op));
}


