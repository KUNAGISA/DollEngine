//
//  PaintEngine.cpp
//  DEPainter
//
//  Created by DollStudio on 15/7/14.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "PaintEngine.h"
#include "System.h"
#include "NormalProgram.h"
#include "GrowProgram.h"
#include "Texture.h"
#include "Storages.h"
#include "CharacterInfo.h"

DE_BEGIN

PaintEngine::PaintEngine()
:m_layerHeight(0)
,m_layerWidth(0)
,m_layerX(0)
,m_layerY(0)
,m_layerZoom(0)
,m_initialized(false)
{
    m_globalTrans = new Transform();
}

PaintEngine::~PaintEngine()
{
    delete m_globalTrans;
}


void PaintEngine::initializeGL()
{
    if (!m_initialized) {
        m_initialized = true;
        
        initialize();
        
        resizeGL(System::GetInstance()->getDesktopWidth(),
                 System::GetInstance()->getDesktopHeight());
        addProgram("normal", new NormalProgram());
        addProgram("grow", new GrowProgram());
    }
}

void PaintEngine::resizeGL(float deviceWidth,float deviceHeight)
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
        
        m_globalTrans->setX(layerX*2/deviceWidth-1);
        m_globalTrans->setY(layerY*2/deviceHeight-1);
        m_globalTrans->setScaleX(2/deviceWidth * layerZoom);
        m_globalTrans->setScaleY(2/deviceHeight * layerZoom);
        m_globalTrans->flush();
        
        setLayerX(layerX);
        setLayerY(layerY);
        
        setLayerZoom(layerZoom);
#ifdef OS_MAC
        glViewport(0,0,deviceWidth,deviceHeight);
        glOrtho(-1, 1, -1, 1, -1, 1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
#endif
        NEED_REDRAW;
    }
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
    if(!fullPath.empty()){
        EM(ERROR_FILE_NOT_EXIST,path);
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
    if (info &&
        info->getTexture() &&
        info->getTexture()->getTextureId() != 0)
    {
        if(m_curProgram != config.program ||
                m_curBlendSrc != config.blendSrc ||
                m_curBlendDst != config.blendDst){
            
            paint();
            
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
    
    m_curProgram->setUniformValue("matrix", getGlobalTrans()->getMatrix());
    bindVAO(0);
    
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
}

DE_END
