//
//  de-painter-engine.h
//  DollEngine
//
//  Created by DollStudio on 15/2/23.
//  Copyright (c) 2015年 血染的玩偶. All rights reserved.
//

#ifndef __DollEngine__de_painter_engine__
#define __DollEngine__de_painter_engine__

#include "de-functions.h"
#include "de-painter-spriteframe.h"
#include "de-painter-texture.h"
#include "de-transform.h"

NAMESPACE_DE_PAINTER

class Engine
{
public:
    Engine();
    Shared(Engine);
//    void initGL();
    
    Transform* getDeviceTrans(){return &m_deviceTrans;}
    PROPERTY(bool, TransChanged, m_transChanged){m_transChanged=v;}
    PROPERTY(bool, TransMatrixChanged, m_transMatrixChanged){m_transMatrixChanged=v;}
public:
//    void addProgram(ShaderProgram::PROGRAM_TYPE type);
//    ShaderProgram* getDefaultProgram();
//    ShaderProgram* getProgram(ShaderProgram::PROGRAM_TYPE type);
//    void enableAttributeArray(ShaderProgram::PROGRAM_ATTRIBUTE location);
//    void disableAttributeArray(ShaderProgram::PROGRAM_ATTRIBUTE location);
public:
//    void removeUnUsedTexture();
//    //添加圆角矩形
//    SpriteFrame* addSpriteFrame(int r);
//    //添加图片
//    SpriteFrame* addSpriteFrame(const wstring& fullpath);
//    SpriteFrame* addSpriteFrame(const wstring& fullpath,const DERect& rect);
//    //添加文字
////    CharFrame* addSpriteFrame(const wstring& str,const wstring& fontName,float fontSize,float outlineSize=0);
//    
//    //添加圆角矩形
//    Texture2D* addTexture(int r);
//    //添加图片
//    Texture2D* addTexture(const wstring& fullpath);
//    SpriteFrame* getSpriteFrameByKey(const wstring& key);
//    Texture2D* getTextureByKey(const wstring& key);
//    Texture2D* getTextTexture();
//    void insertObject(const wstring& key, SpriteFrame* frame, Texture2D* texture);
public:
//    void draw(Transform* trans, SpriteFrame* frame, ShaderProgram* program,const Vector2F& imageSize,const Vector4F& color,bool isFlipY=false);
    
private:
    map<wstring,Texture2D*> m_textureCache;
    map<wstring,SpriteFrame*> m_spriteFrameCache;
//    map<ShaderProgram::PROGRAM_TYPE, ShaderProgram*> m_allProgram;
    Transform m_deviceTrans;
    GLuint m_frame_buffer;
    GLuint m_colorRenderbuffer;
};

NAMESPACE_DE_END2

#endif /* defined(__DollEngine__de_painter_engine__) */
