//
//  PaintEngine.h
//  DEPainter
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DEPainter__PaintEngine__
#define __DEPainter__PaintEngine__

#include "CoreTypes.h"
#include "Transform.h"

#ifdef __QT__
#include <QOpenGLFunctions>
#endif
DE_BEGIN

class PictureData;
class PaintProgram;
class Texture;
class CharacterInfo;

#ifdef __QT__
class PaintEngine : protected QOpenGLFunctions
{
#else
class PaintEngine
{
#endif
public:
    static PaintEngine* GetInstance();
    PaintEngine();
    virtual ~PaintEngine();
    
public:
    
    void initialize();
    void resize(float deviceW,float deviceH);
    void beforeMainLoop();
    void afterMainLoop();
    void pushDrawData(GLDrawData& data);
    void preparePaint(PaintConfig& config);
    void paint();
    void testPaint();
public:
    Transform* m_globalTrans;
    virtual void setGlobalTrans(Transform *v);
    virtual Transform* getGlobalTrans();
    void addProgram(String pm,PaintProgram*);
    PaintProgram* getProgram(String pm);
    Texture* addTexture(const String& path);
    Texture* addTexture(int r);//创建圆角矩形
    CharacterInfo* addText(const String& text,const String& fontName,int fontSize);//添加文字
    void removeTexture(Texture* tex);
public:
    void blendFunc(DrawBlendId src,DrawBlendId dst);
    
    void deleteFBO(DrawSizeI n, const DrawFBOId * framebuffers);
    void createFBO(DrawTexId texId,DrawOldFBOId* oldFBO, DrawFBOId* fbo );
    void switchFBO(DrawOldFBOId* oldFBO,DrawFBOId newFBO);
    
    PictureData* getPictureByRTT(Texture* tex,DrawFBOId fbo);
    
    void clearColor(DrawMask mask,DrawClampF red,DrawClampF green,DrawClampF blue,DrawClampF alpha);
    
    DrawTexId loadTexture(void* data, int width,int height);
    void bindTexture(DrawActiveTexId aid,DrawTexId bid);
    void deleteTexture(DrawSizeI count,DrawTexId* texId);
    void readPixels(GLint x,GLint y,GLsizei width,GLsizei height,GLenum format,GLenum type,GLvoid *pixels);
    
    DrawPrgId createProgram();
    bool linkProgram(DrawPrgId pId);
    void useProgram(DrawPrgId pId);
    void deleteProgram(DrawPrgId pId);
    
    DrawShaderId createShader(GLenum type,const char* code);
    void attachShader(DrawPrgId pId,DrawShaderId sId);
    void detachShader(DrawPrgId pId,DrawShaderId sId);
    void deleteShader(DrawShaderId sId);
    
    int getUniform(DrawPrgId pId, const char* v);
    void bindAttribute(DrawPrgId pId,const char * name, int location);
    void bindVAO(DrawVAOId vaoId);
    void enableVertexAttribs(uint32_t flags);
    void vertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr);
    
    void setUniform1f(GLint location, GLfloat x);
    void setUniform1i(GLint location, GLint x);
    void setUniform2fv(GLint location, GLsizei count, GLfloat* x);
    void setUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    
    void drawElements(GLenum mode,GLsizei count,GLenum type,const GLvoid *indices);
    
    void checkError();
    void checkProgramError(PaintProgram* program);
public:
   
    PROPERTY(float,LayerWidth,m_layerWidth){m_layerWidth=v;}
    PROPERTY(float,LayerHeight,m_layerHeight){m_layerHeight=v;} //逻辑大小
    PROPERTY(float,LayerX,m_layerX){m_layerX=v;}
    PROPERTY(float,LayerY,m_layerY){m_layerY = v;}
    PROPERTY(float,LayerZoom,m_layerZoom){m_layerZoom=v;}
    
    PROPERTY_RO(bool,IsInitialized,m_initialized)
protected:
    map<String,PaintProgram*> m_allPrograms;
    map<String,Texture*> m_allTextures;
    map<String,CharacterInfo*> m_allCharacterInfos;
    vector<GLDrawData> m_quads;
    vector<GLushort> m_indexs;
    
    
    PaintProgram* m_curProgram;
    DrawTexId m_curTexture;
    DrawBlendId m_curBlendSrc;
    DrawBlendId m_curBlendDst;
    
};

DE_END

#endif /* defined(__DEPainter__PaintEngine__) */
