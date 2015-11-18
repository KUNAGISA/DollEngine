//
//  PaintEngine.cpp
//  DEPainter
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "PaintEngine.h"
#include "System.h"
#include "Window.h"
#include "NormalProgram.h"
#include "GrowProgram.h"
#include "Texture.h"
#include "Storages.h"
#include "PaintComponent/Image.h"
#include "CharacterInfo.h"
#include <QDebug>

DE_BEGIN



PaintEngine* PaintEngine::GetInstance()
{
    static PaintEngine* _instance=NULL;
    if(!_instance) {
        _instance = new PaintEngine();
    }
    return _instance;
}

PaintEngine::PaintEngine() :
m_layerHeight(1)
,m_layerWidth(1)
,m_layerX(0)
,m_layerY(0)
,m_layerZoom(0)
,m_initialized(false)
,m_curTexture(-1)
,m_curBlendDst(-1)
,m_curBlendSrc(-1)
,m_curProgram(NULL)
{
    m_globalTrans = new Transform();
}

PaintEngine::~PaintEngine()
{
    SAFF_DELETE(m_globalTrans);
}

void PaintEngine::initialize()
{
    if (!m_initialized) {
        m_initialized = true;
#ifdef __QT__
        initializeOpenGLFunctions();
        glEnable(GL_TEXTURE_2D);
#endif
        glDisable(GL_DEPTH_TEST);

        clearColor(GL_COLOR_BUFFER_BIT,0,0,0,0);

        CHECK_GL_ERROR;

        
        resize(Window::GetInstance()->getWidth(),
                 Window::GetInstance()->getHeight() );
        addProgram(L"normal", new NormalProgram());
        addProgram(L"grow", new GrowProgram());
    }
}

void PaintEngine::resize(float deviceWidth,float deviceHeight)
{
    if (m_initialized) {
        float layerWidth = getLayerWidth();
        float layerHeight = getLayerHeight();
        float p = layerWidth/layerHeight;
        float sc_p = deviceWidth/deviceHeight;
        float layerZoom = 1, layerX = 0, layerY = 0;
        if (p > sc_p) {
            //上下留边
            layerZoom = deviceWidth/layerWidth;
            layerX = 0;
            layerY = (deviceHeight - layerHeight*layerZoom)/2;
        }
        else {
            //左右留边
            layerZoom = deviceHeight/layerHeight;
            layerX = (deviceWidth - layerWidth * layerZoom)/2;
            layerY = 0;
        }
        
        m_globalTrans->setX(layerX*2.0f/deviceWidth-1);
        m_globalTrans->setY(layerY*2.0f/deviceHeight-1);
        m_globalTrans->setScaleX(2.0f/deviceWidth * layerZoom);
        m_globalTrans->setScaleY(2.0f/deviceHeight * layerZoom);
        m_globalTrans->flush();
        
        setLayerX(layerX);
        setLayerY(layerY);
        
        setLayerZoom(layerZoom);
#ifdef __QT__
        glViewport(0,0,deviceWidth,deviceHeight);
#endif
        CHECK_GL_ERROR;
        NEED_REDRAW;
    }
}

void PaintEngine::beforeMainLoop()
{
    
    clearColor(GL_COLOR_BUFFER_BIT,0,0,0,0);
}

void PaintEngine::afterMainLoop()
{
    paint();
}

void PaintEngine::pushDrawData(GLDrawData& data)
{
    m_quads.push_back(data);
}

void PaintEngine::setGlobalTrans(Transform *v)
{
    if(m_globalTrans){
        delete m_globalTrans;
    }
    m_globalTrans = v;
}

Transform* PaintEngine::getGlobalTrans()
{
    return m_globalTrans;
}
void PaintEngine::addProgram(String pm,PaintProgram* effect)
{
    if(effect->init()) {
        m_allPrograms[pm] = effect;
    }
    else {
        DM("Program %s 加载失败",pm.c_nstr());
        delete effect;
    }
}

PaintProgram* PaintEngine::getProgram(String pm)
{
    return m_allPrograms[pm];
}

Texture* PaintEngine::addTexture(const String& path)
{
    String fullPath = Storages::GetInstance()->getFullPath(path);
    if(fullPath.empty()){
        if(path.find(L'.') == String::npos) {
            fullPath = Storages::GetInstance()->getFullPath(path+L".png");
            if(fullPath.empty()) {
                fullPath = Storages::GetInstance()->getFullPath(path+L".jpg");
                if(fullPath.empty()) {
                    fullPath = Storages::GetInstance()->getFullPath(path+L".jpeg");
                    if(fullPath.empty()) {
                        EM(ERROR_FILE_NOT_EXIST,path);
                    }
                }
            }
        }
        else {
            EM(ERROR_FILE_NOT_EXIST,path);
        }
    }
    auto iter2 = m_allTextures.find(fullPath);
    Texture* tex=NULL;
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {
        PictureData image;
        if(image.loadFromFile(fullPath))
        {
            tex = new Texture();
            tex->initWithImage(&image);
        }
        else {
            EM(ERROR_IMAGE_LOAD_FAILD,path);
            return NULL;
        }
        m_allTextures[fullPath] = tex;
        tex->setCacheKey(fullPath);
        tex->retain();
    }
    return tex;
}

Texture* PaintEngine::addTexture(int r)
{
    //创建圆角矩形
    String pickKey = String::fromFormat("round%d",r);
    auto iter2 = m_allTextures.find(pickKey);
    Texture* tex=NULL;
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {
        tex = new Texture();
        PictureData* image = PictureData::createRoundRect(r);
        tex->initWithImage(image);
        delete image;
        m_allTextures[pickKey] = tex;
        tex->setCacheKey(pickKey);
        tex->retain();
    }
    return tex;
}

CharacterInfo* PaintEngine::addText(const String& text,const String& fontName,int fontSize)
{
    //添加文字
    String _fontName;
    if (fontName.empty() || text.empty()) {
        _fontName = DEFFONT;
    }
    else {
        _fontName = fontName;
    }

    if (fontSize == 0 || text.empty()) {
        fontSize = DEFFONTSIZE;
    }
    String key = System::GetKeyByFont(text,fontName,fontSize,0);
    auto iter = m_allCharacterInfos.find(key);
    if (iter != m_allCharacterInfos.end()) {
        return iter->second;
    }
    
    CharacterInfo* frame = new CharacterInfo();
    Texture* tex= NULL;
    auto iter2 = m_allTextures.find(key);
    if(iter2 != m_allTextures.end()) {
        tex = iter2->second;
    }
    else {

        FontData* fd = new FontData();

        PictureData* image = System::GetInstance()->addText(text, fontName, fontSize,fd);

        tex = new Texture();
        if(tex->initWithImage(image)) {
            delete image;
        }
        else {
            delete image;
            delete tex;
            delete frame;
            delete fd;
            return NULL;
        }
        m_allTextures[key] = tex;
        tex->retain();
        frame->setFont(fd);
    }
    return frame;
}

void PaintEngine::removeTexture(Texture* tex)
{
    m_allPrograms.erase(tex->getCacheKey());
}

void PaintEngine::preparePaint(PaintConfig& config)
{
    ImageInfo* info = config.info;
    if(m_curTexture)
    if (info &&
        info->getTexture() &&
        info->getTexture()->getTextureId() != 0)
    {
        if(
                m_curTexture != info->getTexture()->getTextureId() ||
                m_curProgram != config.program ||
                m_curBlendSrc != config.blendSrc ||
                m_curBlendDst != config.blendDst ){
            
            paint();
            m_curTexture = info->getTexture()->getTextureId();
            m_curProgram = config.program;
            blendFunc(config.blendSrc,config.blendDst);
            useProgram(config.program->getProgramId());
        }
        config.program->preparePaint(config);
    }
}

void PaintEngine::paint()
{
    if (m_quads.size() == 0) {
        return;
    }
    bindVAO(0);
    bindTexture(GL_TEXTURE0,m_curTexture);
//    getGlobalTrans()->setX(-1);
//    getGlobalTrans()->setY(-1);
//    getGlobalTrans()->setScale(1.0/1024.0f);
//    getGlobalTrans()->flush();
    m_curProgram->setUniformValue("matrix", getGlobalTrans()->getMatrix());
#define kQuadSize sizeof(GLVertex)
    long offset = (long)m_quads.data();
    enableVertexAttribs(VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    
    int diff = offsetof( GLVertex, vertex);
    vertexAttribPointer(PROGRAM_VERTEX_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    diff = offsetof( GLVertex, color);
    vertexAttribPointer(PROGRAM_COLOR_ATTRIBUTE, 4, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    diff = offsetof( GLVertex, uv);
    vertexAttribPointer(PROGRAM_TEXCOORD_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, kQuadSize,(void*) (offset + diff));
    int size = (int)m_quads.size()*4;
    
    for (int i=0; i<m_quads.size(); ++i) {
        m_indexs.push_back(i*4);
        m_indexs.push_back(i*4+1);
        m_indexs.push_back(i*4+2);
        m_indexs.push_back(i*4+2);
        m_indexs.push_back(i*4+3);
        m_indexs.push_back(i*4);
    }
    drawElements(GL_TRIANGLES, m_quads.size()*2*3, GL_UNSIGNED_SHORT, m_indexs.data());
//    glDrawArrays(GL_TRIANGLE_FAN, 0, size);
    
    CHECK_GL_ERROR;
    m_quads.clear();
    m_indexs.clear();
    m_curProgram = NULL;
    m_curBlendSrc = -1;
    m_curBlendDst = -1;
    m_curTexture = -1;
}

void PaintEngine::testPaint()
{
    glFlush();
}

void PaintEngine::blendFunc(DrawBlendId src,DrawBlendId dst)
{
    if (src != m_curBlendSrc || dst != m_curBlendDst)
    {
        m_curBlendSrc = src;
        m_curBlendDst = dst;
        if (src == GL_ONE && dst == GL_ZERO)
        {
            glDisable(GL_BLEND);
        }
        else
        {
            glEnable(GL_BLEND);
            glBlendFunc(src, dst);
        }
    }
}

void PaintEngine::deleteFBO(DrawSizeI n, const DrawFBOId * framebuffers)
{
    glDeleteFramebuffers(n,framebuffers);
}

void PaintEngine::createFBO(DrawTexId texId,DrawOldFBOId* oldFBO, DrawFBOId* fbo )
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, oldFBO);
    
    GLint oldRBO;
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRBO);
    
    glGenFramebuffers(1, fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texId, 0);
    
    ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    
    glBindRenderbuffer(GL_RENDERBUFFER, oldRBO);
    glBindFramebuffer(GL_FRAMEBUFFER, *oldFBO);
}

void PaintEngine::switchFBO(DrawOldFBOId* oldFBO,DrawFBOId newFBO)
{
    if(oldFBO){
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)oldFBO);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, newFBO);
    qDebug()<<"--------";
    if(oldFBO) {
        qDebug()<< (*oldFBO);
    }
    else {
        qDebug()<< "null";
    }
    qDebug()<< newFBO;
    CHECK_GL_ERROR;
}

PictureData* PaintEngine::getPictureByRTT(Texture* tex,DrawFBOId _FBO)
{
    int savedBufferWidth = tex->getWidth();
    int savedBufferHeight = tex->getHeight();
    IOData* data = new IOData();
    data->initWithSize(savedBufferWidth*savedBufferHeight*4);
    GLint _oldFBO;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &_oldFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
    
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0,0,savedBufferWidth, savedBufferHeight,GL_RGBA,GL_UNSIGNED_BYTE, data->getBuffer());
    glBindFramebuffer(GL_FRAMEBUFFER, _oldFBO);
    PictureData* picture = new PictureData();
    picture->setWidth(savedBufferWidth);
    picture->setHeight(savedBufferHeight);
    picture->setData(data);
    return picture;
}

void PaintEngine::clearColor(DrawMask mask,DrawClampF red,DrawClampF green,DrawClampF blue,DrawClampF alpha)
{
    glClearColor(red,green,blue,alpha);
    if(mask!=0)
    {
        glClear(mask);
    }
}

DrawTexId PaintEngine::loadTexture(void* data, int width,int height)
{
    CHECK_GL_ERROR;
    DrawTexId m_textureId;
    glGenTextures(1,&m_textureId);
    glBindTexture(GL_TEXTURE_2D,m_textureId);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width,height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data );
    CHECK_GL_ERROR;
    return m_textureId;
}

static DrawActiveTexId g_aid = GL_TEXTURE0;
void PaintEngine::bindTexture(DrawActiveTexId aid,DrawTexId bid)
{
    glActiveTexture(aid);
    glBindTexture(GL_TEXTURE_2D, bid);
    CHECK_GL_ERROR;
}

void PaintEngine::deleteTexture(DrawSizeI count,DrawTexId* texId)
{
    glDeleteTextures(count,texId);
}

void PaintEngine::readPixels(GLint x,GLint y,GLsizei width,GLsizei height,GLenum format,GLenum type,GLvoid *pixels)
{
    glReadPixels(x,y,width,height,format,type,pixels);
    CHECK_GL_ERROR;
}

DrawPrgId PaintEngine::createProgram()
{
    return glCreateProgram();
}

bool PaintEngine::linkProgram(DrawPrgId pId)
{
    glLinkProgram(pId);
    CHECK_GL_ERROR;

    GLint status;
    glGetProgramiv(pId, GL_LINK_STATUS, &status);
    CHECK_GL_ERROR;
    if (status == 0) {
        GLint logLength;
        glGetProgramiv(pId, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLchar *log = (GLchar *)malloc(logLength);
            glGetProgramInfoLog(pId, logLength, &logLength, log);
            DM("Program link log:\n%s", log);
            free(log);
        }
        return false;
    }
    return true;
}

static DrawPrgId g_lastProgramId = -1;
void PaintEngine::useProgram(DrawPrgId pId)
{
    glUseProgram(pId);
    CHECK_GL_ERROR;
}

void PaintEngine::deleteProgram(DrawPrgId pId)
{
    glDeleteProgram(pId);
}


DrawShaderId PaintEngine::createShader(GLenum type,const char* code)
{
    CHECK_GL_ERROR;
    DrawShaderId m_id = glCreateShader(type);
    CHECK_GL_ERROR;
    if (m_id)
    {
        const GLchar* ptr[] = {code};
        glShaderSource(m_id,sizeof(ptr)/sizeof(*ptr), ptr, NULL);
        glCompileShader(m_id);
        CHECK_GL_ERROR;
        //检查
        GLint compiled;
        glGetShaderiv ( m_id, GL_COMPILE_STATUS, &compiled );
        if ( !compiled )
        {
            GLint infoLen = 0;


            glGetShaderiv ( m_id, GL_INFO_LOG_LENGTH, &infoLen );

            if ( infoLen > 1 )
            {
                char infoLog[infoLen+1];
                memset(infoLog, 0, infoLen+1);

                glGetShaderInfoLog ( m_id, infoLen, NULL, infoLog );
                DM("Error compiling shader:\n%s", (const char*)infoLog);
            }

            glDeleteShader ( m_id );
            m_id=0;
            return 0;
        }
        return m_id;
    }
    return 0;
}

void PaintEngine::attachShader(DrawPrgId pId,DrawShaderId sId)
{
    glAttachShader(pId,sId);
    CHECK_GL_ERROR;
}

void PaintEngine::detachShader(DrawPrgId pId,DrawShaderId sId)
{
    glDetachShader(pId, sId);
}

void PaintEngine::deleteShader(DrawShaderId sId)
{
    glDeleteShader(sId);
}


int PaintEngine::getUniform(DrawPrgId pId, const char* v)
{
    int index = glGetUniformLocation(pId,v);
    return index;
}

void PaintEngine::bindAttribute(DrawPrgId pId,const char * name, int location)
{
    glBindAttribLocation(pId,location,name);
    CHECK_GL_ERROR;
}

static GLuint s_VAO=-1;
void PaintEngine::bindVAO(DrawVAOId vaoId)
{
    if (s_VAO != vaoId)
    {
        s_VAO = vaoId;
#ifndef __QT__
        glBindVertexArray(vaoId);
#endif
    }
}

static int MAX_ATTRIBUTES = 16;
static uint32_t s_attributeFlags = 0;
void PaintEngine::enableVertexAttribs(uint32_t flags)
{
    if(s_attributeFlags != flags) {
        for(int i=0; i < MAX_ATTRIBUTES; i++) {
            unsigned int bit = 1 << i;
            bool enabled = flags & bit;
            bool enabledBefore = s_attributeFlags & bit;
            if(enabled != enabledBefore) {
                if( enabled )
                    glEnableVertexAttribArray(i);
                else
                    glDisableVertexAttribArray(i);
            }
        }
        CHECK_GL_ERROR;
        s_attributeFlags = flags;
    }
}

void PaintEngine::vertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* ptr)
{
    glVertexAttribPointer(indx,size,type,normalized,stride,ptr);
    CHECK_GL_ERROR;
}


void PaintEngine::setUniform1f(GLint location, GLfloat x)
{
    glUniform1f(location, x);
}

void PaintEngine::setUniform1i(GLint location, GLint x)
{
    glUniform1i(location, x);
}

void PaintEngine::setUniform2fv(GLint location, GLsizei count, GLfloat* x)
{
    glUniform2fv(location, count, x);
}

void PaintEngine::setUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    glUniformMatrix4fv(location,count,transpose,value);
}


void PaintEngine::drawElements(GLenum mode,GLsizei count,GLenum type,const GLvoid *indices)
{
    glDrawElements(mode,count,type,indices);
}

void PaintEngine::checkError()
{
    GLint v = glGetError();
    if(v){
        DM("OpenGL 出错:%x\n%s",v);
        EM("不知道哪里出问题了");
    }
}

void PaintEngine::checkProgramError(PaintProgram* program)
{
    GLint v = glGetError();
    if (v) {
        DM("Error GL:0x%x", v);
        char infoLog[128];
        memset(infoLog, 0, 128);

        glGetProgramInfoLog ( program->getProgramId(), 127, NULL, infoLog );
        DM("Error program:%s", (const char*)infoLog);

        for (int i=0; i< program->getShaderCount(); ++i)
        {
            PaintShader* obj = program->getShader(i);
            memset(infoLog, 0, 128);
            glGetShaderInfoLog ( obj->getId(), 127, NULL, infoLog );
            DM("Error shader:%s", (const char*)infoLog);
        }
    }
}

DE_END
