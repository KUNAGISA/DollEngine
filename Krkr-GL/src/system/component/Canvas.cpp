//
//  Canvas.cpp
//  DollEngine
//
//  Created by DollStudio on 14/11/23.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "Canvas.h"
#include "Krkr-GL.h"

Canvas::Canvas()
:m_program(null)
,m_spriteFrame(null)
,m_scale9(false)
,m_imageHeight(0)
,m_imageWidth(0)
,m_leftInside(0)
,m_topInside(0)
,m_rightInside(0)
,m_bottomInside(0)
,m_opacity(1)
{
    setComName(L"Canvas");
    m_program = PaintEngine::GetInstance()->getDefaultProgram();
    for (int i=0; i<9; ++i)
    {
        m_scale9Frame[i] = new SpriteFrame();
        m_scale9Trans[i] = new Transform();
    }
    setEnabled(true);
}

Canvas::~Canvas()
{
    for (int i=0; i<9; ++i)
    {
        delete m_scale9Frame[i];
        delete m_scale9Trans[i];
    }
    SAFF_RELEASE_NULL(m_spriteFrame);
}

bool Canvas::colorRect(int r)
{
    SAFF_RELEASE(m_spriteFrame);
    m_spriteFrame = PaintEngine::GetInstance()->addSpriteFrame(r);
    SAFF_RETAIN(m_spriteFrame);
    
    if (getObject())
    {
        auto trans = getObject()->getTransform();
        if (trans)
        {
            m_imageWidth = m_spriteFrame->getWidth();
            m_imageHeight = m_spriteFrame->getHeight();
            trans->setWidth(m_spriteFrame->getWidth());
            trans->setHeight(m_spriteFrame->getHeight());
        }
    }
    System::GetInstance()->setTransChanged(true);
    if (r == 0)
    {
        setScale9(false);
    }
    else
    {
        setScale9(true);
    }
    m_graphPath = StringUtils::StringFromFormat(L"[COLORRECT]%d",r);
    return true;
}

bool Canvas::loadImages(const wstring& path)
{
    wstring ext = Storages::GetInstance()->extractStorageExt(path);
    wstring fullPath;
    if (ext == L"jpg" || ext == L"jpeg" || ext == L"png")
    {
        fullPath = Storages::GetInstance()->getFullPath(path);
    }
    else if(ext.size() == 0)
    {
        fullPath = Storages::GetInstance()->getFullPath(path+L".png");
        if (fullPath.size() == 0)
        {
            fullPath = Storages::GetInstance()->getFullPath(path+L".jpg");
            if (fullPath.size() == 0)
            {
                fullPath = Storages::GetInstance()->getFullPath(path+L".jpeg");
                if (fullPath.size() == 0)
                {
                    EM(ERROR_FILE_OPENFAIL_PATH_CANTFIND,path.c_str());
                    return false;
                }
            }
        }
    }
    else
    {
        EM(ERROR_FILE_OPENFAIL_PATH_CANTFIND,path.c_str());
        return false;
    }
    
    SAFF_RELEASE(m_spriteFrame);
    m_spriteFrame = PaintEngine::GetInstance()->addSpriteFrame(fullPath);
    SAFF_RETAIN(m_spriteFrame);
    if (!m_spriteFrame)
    {
        return false;
    }
    if (getObject())
    {
        auto trans = getObject()->getTransform();
        if (trans)
        {
            m_imageWidth = m_spriteFrame->getWidth();
            m_imageHeight = m_spriteFrame->getHeight();
            trans->setWidth(m_spriteFrame->getWidth());
            trans->setHeight(m_spriteFrame->getHeight());
        }
    }
    setScale9(false);
    System::GetInstance()->setTransChanged(true);
    m_graphPath = fullPath;
    return true;
}

void Canvas::freeImages()
{
    SAFF_RELEASE(m_spriteFrame);
    m_spriteFrame = null;
    if (getObject())
    {
        auto trans = getObject()->getTransform();
        if (trans)
        {
            trans->setWidth(0);
            trans->setHeight(0);
        }
    }
    m_imageWidth = 0;
    m_imageHeight = 0;
    System::GetInstance()->setTransChanged(true);
    m_graphPath = L"";
}

void Canvas::setScale9(bool v)
{
    if (m_scale9 != v)
    {
        m_scale9 = v;
        if (v)
        {
            for (int i=0; i<9; ++i) {
                m_scale9Frame[i]->initWithTexture(getSpriteFrame()->getTexture());
            }
        }
        else
        {
            for (int i=0; i<9; ++i) {
                m_scale9Frame[i]->initWithTexture(null);
            }
        }
    }
}


void Canvas::trigger()
{
    if (!m_enabled || !m_spriteFrame || !getObject() || !m_program) {
        return;
    }
    if (m_imageHeight <=0 || m_imageWidth <= 0) {
        return;
    }
    Transform* trans = getObject()->getWorldTrans();
    if (trans) {
        Vector2F imageSize;
        
        float opacity = getObject()->getRealyOpacity()*m_opacity;
        Vector4F color(opacity,opacity,opacity,opacity);
        if (!m_scale9)
        {
            imageSize.set(m_imageWidth,m_imageHeight);
            PaintEngine::GetInstance()->draw(trans,m_spriteFrame, m_program,imageSize,color);
        }
        else
        {
            Transform res;
            Transform add;
            if (m_leftInside == 0 &&
                m_topInside == 0 &&
                m_rightInside == 0 &&
                m_bottomInside == 0)
            {
                m_leftInside = getSpriteFrame()->getWidth()/3+1;
                m_topInside = getSpriteFrame()->getHeight()/3+1;
                m_rightInside = getSpriteFrame()->getWidth()/3+1;
                m_bottomInside = getSpriteFrame()->getHeight()/3+1;
            }
            float l,t,w,h;
            
            //左上
            l=0,t=0,w=m_leftInside,h=m_topInside;
            m_scale9Frame[0]->setRect({l,t,w,h});
            add.setX(l);
            add.setY(t);
            add.refresh();
            m_scale9Trans[0]->set(trans,&add);
            imageSize.set(w,h);
            PaintEngine::GetInstance()->draw(m_scale9Trans[0],m_scale9Frame[0], m_program,imageSize,color);
            
            //中上
            l=m_leftInside,t=0,w=getSpriteFrame()->getWidth()-m_leftInside-m_rightInside,h=m_topInside;
            m_scale9Frame[1]->setRect({l,t,w,h});
            add.setX(l);
            add.setY(t);
            add.refresh();
            m_scale9Trans[1]->set(trans,&add);
            imageSize.set(m_imageWidth-m_leftInside-m_rightInside,h);
            PaintEngine::GetInstance()->draw(m_scale9Trans[1],m_scale9Frame[1], m_program,imageSize,color);

            //右上
            l=getSpriteFrame()->getWidth()-m_rightInside,t=0,w=m_rightInside,h=m_topInside;
            m_scale9Frame[2]->setRect({l,t,w,h});
            add.setX(m_imageWidth-m_rightInside);
            add.setY(t);
            add.refresh();
            m_scale9Trans[2]->set(trans,&add);
            imageSize.set(w,h);
            PaintEngine::GetInstance()->draw(m_scale9Trans[2],m_scale9Frame[2], m_program,imageSize,color);

            //左
            l=0,t=m_topInside,w=m_leftInside,h=getSpriteFrame()->getHeight()-m_topInside-m_bottomInside;
            m_scale9Frame[3]->setRect({l,t,w,h});
            add.setX(l);
            add.setY(t);
            add.refresh();
            m_scale9Trans[3]->set(trans,&add);
            imageSize.set(w,m_imageHeight-m_topInside-m_bottomInside);
            PaintEngine::GetInstance()->draw(m_scale9Trans[3],m_scale9Frame[3], m_program,imageSize,color);

            //中
            l=m_leftInside,t=m_topInside,w=getSpriteFrame()->getWidth()-m_leftInside-m_rightInside,h=getSpriteFrame()->getHeight()-m_topInside-m_bottomInside;
            m_scale9Frame[4]->setRect({l,t,w,h});
            add.setX(l);
            add.setY(t);
            add.refresh();
            m_scale9Trans[4]->set(trans,&add);
            imageSize.set(m_imageWidth-m_leftInside-m_rightInside,m_imageHeight-m_topInside-m_bottomInside);
            PaintEngine::GetInstance()->draw(m_scale9Trans[4],m_scale9Frame[4], m_program,imageSize,color);

            //右
            l=m_imageWidth-m_rightInside,t=m_topInside,w=m_rightInside,h=getSpriteFrame()->getHeight()-m_topInside-m_bottomInside;
            m_scale9Frame[5]->setRect({l,t,w,h});
            add.setX(m_imageWidth-m_rightInside);
            add.setY(t);
            add.refresh();
            m_scale9Trans[5]->set(trans,&add);
            imageSize.set(w,m_imageHeight-m_topInside-m_bottomInside);
            PaintEngine::GetInstance()->draw(m_scale9Trans[5],m_scale9Frame[5], m_program,imageSize,color);

            //左下
            l=0,t=getSpriteFrame()->getHeight()-m_bottomInside,w=m_leftInside,h=m_bottomInside;
            m_scale9Frame[6]->setRect({l,t,w,h});
            add.setX(l);
            add.setY(m_imageHeight-m_bottomInside);
            add.refresh();
            m_scale9Trans[6]->set(trans,&add);
            imageSize.set(w,h);
            PaintEngine::GetInstance()->draw(m_scale9Trans[6],m_scale9Frame[6], m_program,imageSize,color);

            //中下
            l=m_leftInside,t=getSpriteFrame()->getHeight()-m_bottomInside,w=getSpriteFrame()->getWidth()-m_leftInside-m_rightInside,h=m_bottomInside;
            m_scale9Frame[7]->setRect({l,t,w,h});
            add.setX(l);
            add.setY(m_imageHeight-m_bottomInside);
            add.refresh();
            m_scale9Trans[7]->set(trans,&add);
            imageSize.set(m_imageWidth-m_leftInside-m_rightInside,h);
            PaintEngine::GetInstance()->draw(m_scale9Trans[7],m_scale9Frame[7], m_program,imageSize,color);
            
            //右下
            l=getSpriteFrame()->getWidth()-m_rightInside,t=getSpriteFrame()->getHeight()-m_bottomInside,w=m_rightInside,h=m_bottomInside;
            m_scale9Frame[8]->setRect({l,t,w,h});
            add.setX(m_imageWidth-m_rightInside);
            add.setY(m_imageHeight-m_bottomInside);
            add.refresh();
            m_scale9Trans[8]->set(trans,&add);
            imageSize.set(w,h);
            PaintEngine::GetInstance()->draw(m_scale9Trans[8],m_scale9Frame[8], m_program,imageSize,color);
            
//            PaintEngine::GetInstance()->draw16(trans,m_spriteFrame, m_program);
        }
    }
}

