//
//  PaintEngine.cpp
//  DollEngine
//
//  Created by DollStudio on 14/11/5.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#include "PaintEngine.h"
#include "Window.h"
#include "System.h"
#include "Canvas.h"
#include "CharFrame.h"
#include "StringUtils.h"

static const char* s_default_vertcode =
#include "default_vertex.h"
;
static const char* s_default_fragcode =
#include "default_fragment.h"
;



PaintEngine::PaintEngine()
:m_transChanged(true)
{
}

void PaintEngine::initGL()
{
#ifdef OS_IOS
    glGenFramebuffers(1, &m_frame_buffer);
    if(!m_frame_buffer) {THROW_EM(ERROR_PaintEngine_INIT_FAILD_FRAME);}
    glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer);
    
    glGenRenderbuffers(1, &m_colorRenderbuffer);
    if(!m_colorRenderbuffer) {THROW_EM(ERROR_PaintEngine_INIT_FAILD_RENDER);}
    glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8,
                          System::GetInstance()->getScreenWidth(),
                          System::GetInstance()->getScreenHeight());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRenderbuffer);
    
    CHECK_GL_ERROR;
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER) ;
    if(status != GL_FRAMEBUFFER_COMPLETE) {
        DM("failed to make complete framebuffer object %x", status);
    }
#endif

#ifdef OS_MAC
    glEnable(GL_TEXTURE_2D);
    CHECK_GL_ERROR;
#endif
    glDisable(GL_DEPTH_TEST);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    GL::blendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    CHECK_GL_ERROR;
    addProgram(ShaderProgram::PROGRAM_TYPE_DEFAULT);
    GL::setProjectionMatrixDirty();
}

void PaintEngine::addProgram(ShaderProgram::PROGRAM_TYPE type)
{
    ShaderProgram* program = new ShaderProgram();
    CHECK_GL_ERROR;
    switch (type)
    {
        case ShaderProgram::PROGRAM_TYPE_DEFAULT:
        {
            program->addShaderFromCode(ShaderObject::SHADER_TYPE_VERTEX, s_default_vertcode);
            program->addShaderFromCode(ShaderObject::SHADER_TYPE_FRAGMENT, s_default_fragcode);
            program->bind();
        }
            break;
            
        default:
            break;
    }
    if (m_allProgram.find(type) != m_allProgram.end())
    {
        delete m_allProgram[type];
    }
    m_allProgram[type] = program;
}

ShaderProgram* PaintEngine::getDefaultProgram()
{
    return getProgram(ShaderProgram::PROGRAM_TYPE_DEFAULT);
}

ShaderProgram* PaintEngine::getProgram(ShaderProgram::PROGRAM_TYPE type)
{
    auto iter = m_allProgram.find(type);
    if(iter == m_allProgram.end())
    {
        return null;
    }
    return iter->second;
}

void PaintEngine::enableAttributeArray(ShaderProgram::PROGRAM_ATTRIBUTE location)
{
    glEnableVertexAttribArray(location);
}

void PaintEngine::disableAttributeArray(ShaderProgram::PROGRAM_ATTRIBUTE location)
{
    glDisableVertexAttribArray(location);
}

void PaintEngine::removeUnUsedTexture()
{
    for (auto iter = m_textureCache.begin() ;
         iter != m_textureCache.end(); )
    {
        if (iter->second->getRetainCount() <= 0)
        {
            delete iter->second;
            iter = m_textureCache.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

SpriteFrame* PaintEngine::addSpriteFrame(int r)
{
    wstring key = StringUtils::StringFromFormat(L"[COLORRECT]:%d",r);
    SpriteFrame* frame = getSpriteFrameByKey(key);
    if (frame) {
        return frame;
    }
    Texture2D* tex = addTexture(r);
    if (!tex)
    {
        return null;
    }
    frame = new SpriteFrame();
    kRect rect;
    if (r == 0) {
        rect.width = 2;
        rect.height = 2;
    }
    else {
        rect.width = r*3;
        rect.height = r*3;
    }
    frame->initWithTexture(tex, rect);
    frame->retain();
    m_spriteFrameCache[key] = frame;
    return frame;
}

SpriteFrame* PaintEngine::addSpriteFrame(const wstring& fullpath)
{
    Texture2D* tex = addTexture(fullpath);
    if (!tex) {
        return NULL;
    }
    return addSpriteFrame(fullpath,kRect(0,0,tex->getWidth(),tex->getHeight()));
}

SpriteFrame* PaintEngine::addSpriteFrame(const wstring& fullpath,const kRect& rect)
{
    SpriteFrame* frame = getSpriteFrameByKey(fullpath);
    if (frame) {
        return frame;
    }
    Texture2D* tex = addTexture(fullpath);
    if (!tex) {
        return NULL;
    }
    frame = new SpriteFrame();
    frame->initWithTexture(tex, rect);
    frame->retain();
    m_spriteFrameCache[fullpath] = frame;
    return frame;
}

CharFrame* PaintEngine::addSpriteFrame(const wstring& str,const wstring& fontName,float fontSize,float outlineSize)
{
    wstring face;
    if (fontName.size() == 0) {
        face = DEFFONT;
    }
    else
    {
        face = fontName;
    }
    wstring key = CharFrame::CreateKey(str,face,fontSize,outlineSize);
    SpriteFrame* frame = getSpriteFrameByKey(key);
    if (frame)
    {
        return dynamic_cast<CharFrame*>(frame);
    }
    else
    {
        CharFrame* image = new CharFrame();
        if (image->initWithConfig(str,face,fontSize,outlineSize))
        {
            return image;
        }
        delete image;
        return null;
    }
}

SpriteFrame* PaintEngine::getSpriteFrameByKey(const wstring& key)
{
    auto iter = m_spriteFrameCache.find(key);
    if (iter != m_spriteFrameCache.end())
    {
        return iter->second;
    }
    return null;
}

Texture2D* PaintEngine::addTexture(int r)
{
    wstring key = StringUtils::StringFromFormat(L"[COLORRECT]:%d",r);
    Texture2D* tex = getTextureByKey(key);
    if (tex) {
        return tex;
    }
    Image* image = Image::createRoundRect(r);
    if (image)
    {
        tex = new Texture2D();
        if(tex->initWithImage(image))
        {
            m_textureCache[key] = tex;
        }
        else
        {
            delete tex;
            tex = null;
        }
        delete image;
        return tex;
    }
    return null;
}

Texture2D* PaintEngine::addTexture(const wstring& fullpath)
{
    Texture2D* tex = getTextureByKey(fullpath);
    if (tex) {
        return tex;
    }
    Image* image = get_image_data(fullpath);
    if (image)
    {
        tex = new Texture2D();
        if(tex->initWithImage(image))
        {
            m_textureCache[fullpath] = tex;
        }
        else
        {
            delete tex;
            tex = null;
        }
        delete image;
        return tex;
    }
    return null;
}

Texture2D* PaintEngine::getTextureByKey(const wstring& key)
{
    auto iter = m_textureCache.find(key);
    if (iter != m_textureCache.end())
    {
        return iter->second;
    }
    return null;
}

Texture2D* PaintEngine::getTextTexture()
{
    Texture2D* tex = new Texture2D();
    return tex;
}

void PaintEngine::insertObject(const wstring& key, SpriteFrame* frame, Texture2D* texture)
{
    m_textureCache[key] = texture;
    m_spriteFrameCache[key] = frame;
}

static GLfloat vertices[] = {
    0,0,
    0,0,
    0,0,
    0,0};
void PaintEngine::draw(Transform* trans,
                       SpriteFrame* frame,
                       ShaderProgram* program,
                       const Vector2F& imageSize,
                       const Vector4F& color,
                       bool isFlipY)
{
    if(isFlipY)
    {
        vertices[0]=0,          vertices[1]=imageSize.y,
        vertices[2]=0,          vertices[3]=0,
        vertices[4]=imageSize.x,vertices[5]=imageSize.y,
        vertices[6]=imageSize.x,vertices[7]=0;
    }
    else
    {
        vertices[0]=0,          vertices[1]=0,
        vertices[2]=0,          vertices[3]=imageSize.y,
        vertices[4]=imageSize.x,vertices[5]=0,
        vertices[6]=imageSize.x,vertices[7]=imageSize.y;
    }
    
    Vector4F colors[4];
    colors[0] = color;
    colors[1] = color;
    colors[2] = color;
    colors[3] = color;
    
    program->use();
    program->setUniformValue("matrix",trans->getMatrix());
    
    GL::blendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
    GL::bindTexture2D(frame->getTexture()->getTexId());
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    
    glVertexAttribPointer(ShaderProgram::PROGRAM_VERTEX_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(ShaderProgram::PROGRAM_COLOR_ATTRIBUTE, 4, GL_FLOAT, GL_FALSE, 0, colors);
    glVertexAttribPointer(ShaderProgram::PROGRAM_TEXCOORD_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, 0, frame->getGLCoord());
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    CHECK_GL_ERROR;
}


//void PaintEngine::draw16(Transform* trans, Texture2D* tex2d, ShaderProgram* program,const kRect& rectBig,const kRect& rectSmall)
//{
//    
//}
