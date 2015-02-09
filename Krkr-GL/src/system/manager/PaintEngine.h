//
//  PaintEngine.h
//  DollEngine
//
//  Created by DollStudio on 14/11/5.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__PaintEngine__
#define __DollEngine__PaintEngine__

#include "Functions.h"
#include "Transform.h"
#include "ShaderProgram.h"

#define VBO_SIZE 65536 / 6

class PaintEngine;
class Texture2D;
class SpriteFrame;
class CharFrame;
class PaintEngine
{
public:
    Shared(PaintEngine)
    PaintEngine();
    void initGL();
    
    Transform* getDeviceTrans(){return &m_deviceTrans;}
    PROPERTY(bool, TransChanged, m_transChanged){m_transChanged=v;}
    PROPERTY(bool, TransMatrixChanged, m_transMatrixChanged){m_transMatrixChanged=v;}
public:
    void addProgram(ShaderProgram::PROGRAM_TYPE type);
    ShaderProgram* getDefaultProgram();
    ShaderProgram* getProgram(ShaderProgram::PROGRAM_TYPE type);
    void enableAttributeArray(ShaderProgram::PROGRAM_ATTRIBUTE location);
    void disableAttributeArray(ShaderProgram::PROGRAM_ATTRIBUTE location);
public:
    void removeUnUsedTexture();
    //添加圆角矩形
    SpriteFrame* addSpriteFrame(int r);
    //添加图片
    SpriteFrame* addSpriteFrame(const wstring& fullpath);
    SpriteFrame* addSpriteFrame(const wstring& fullpath,const kRect& rect);
    //添加文字
    CharFrame* addSpriteFrame(const wstring& str,const wstring& fontName,float fontSize,float outlineSize=0);
    
    //添加圆角矩形
    Texture2D* addTexture(int r);
    //添加图片
    Texture2D* addTexture(const wstring& fullpath);
    SpriteFrame* getSpriteFrameByKey(const wstring& key);
    Texture2D* getTextureByKey(const wstring& key);
    Texture2D* getTextTexture();
    void insertObject(const wstring& key, SpriteFrame* frame, Texture2D* texture);
public:
    void draw(Transform* trans, SpriteFrame* frame, ShaderProgram* program,const Vector2F& imageSize,const Vector4F& color,bool isFlipY=false);
    
private:
    map<wstring,Texture2D*> m_textureCache;
    map<wstring,SpriteFrame*> m_spriteFrameCache;
    map<ShaderProgram::PROGRAM_TYPE, ShaderProgram*> m_allProgram;
    Transform m_deviceTrans;
    GLuint m_frame_buffer;
    GLuint m_colorRenderbuffer;
};

#endif /* defined(__DollEngine__PaintEngine__) */
