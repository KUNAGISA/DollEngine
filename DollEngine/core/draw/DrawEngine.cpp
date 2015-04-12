#include "DrawEngine.h"
#include "Storages.h"
#include "NormalEffect.h"
#include "Device.h"

DE_BEGIN

DrawEngine::DrawEngine()
    :m_context(null)
{
}

DrawEngine::~DrawEngine()
{
    
}

void DrawEngine::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_TEXTURE_2D);
    initDefaultEffect();
    
}

void DrawEngine::clearGL()
{
    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DrawEngine::resizeGL(int width, int height)
{
    if(isInitialized(d_ptr)) {
        glViewport(0,0, width, height);
    }
}

void DrawEngine::initDefaultEffect()
{
    if (m_allEffects.size() == 0) {
        auto effect = new NormalEffect();
        addEffect(NORMAL_EFFECT,effect);
    }
}

void DrawEngine::addEffect(EFFECT_PROGRAM pm,Effect* effect)
{
    if(effect->init()) {
        m_allEffects[pm] = effect;
    }
    else {
        delete effect;
    }
}

Effect* DrawEngine::getEffect(EFFECT_PROGRAM pm)
{
    initDefaultEffect();
    return m_allEffects[pm];
}

SpriteFrame* DrawEngine::addImage(const QString& picKey,const QString& plist)
{
    if (plist == "") {
        QString fullPath = Storages::GetInstance()->getFullPath(picKey);
        if(fullPath == "") {
            throw Debug::throwMsg(ERROR_FILE_EXIST_FAILD,picKey);
        }
        auto iter = m_allSpriteFrames.find(fullPath);
        if (iter != m_allSpriteFrames.end()) {
            return iter.value();
        }
        auto iter2 = m_allTextures.find(fullPath);
        Texture2D* tex=null;
        if(iter2 != m_allTextures.end()) {
            tex = iter2.value();
        }
        else {
            QImage image(fullPath);
            if(image.isNull()) {
                throw Debug::throwMsg(ERROR_IMAGE_LOAD_FAILD,picKey);
            }
            tex = new Texture2D(image);
            m_allTextures[fullPath] = tex;
            tex->setCacheKey(fullPath);
            tex->retain();
        }
        
        SpriteFrame* frame = new SpriteFrame();
        frame->setTexture(tex);
        
        m_allSpriteFrames[fullPath] = frame;
        frame->setCacheKey(fullPath);
        frame->retain();
        return frame;
    }
    else {
        QString fullPath = Storages::GetInstance()->getFullPath(plist);
        throw Debug::throwMsg("暂时不支持Plist格式");
        return null;
    }
}

void DrawEngine::draw(SpriteFrame* frame,Transform* trans,const GradientColor& color,Effect* effect)
{
    static int coords[4][3] = { 
        { 1024, 768, 0 }, 
        { 0, 768, 0 }, 
        { 0, 0, 0 }, 
        { 1024, 0, 0 } 
    };
    QRect rect = frame->getRect();
    coords[0][0] = coords[3][0] = rect.width();
    coords[0][1] = coords[1][1] = rect.height();
    QVector<GLfloat> vertData;
    for (int j = 0; j < 4; ++j) {
        // vertex position
        vertData.append(coords[j][0]);
        vertData.append(coords[j][1]);
        vertData.append(coords[j][2]);
        // texture coordinate
        vertData.append(j == 0 || j == 3);
        vertData.append(j == 0 || j == 1);
    }
    m_vbo.destroy();
    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
    
    effect->setUniformValue("matrix", trans->getMatrix());
    effect->actived();
    
    frame->getTexture()->bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void DrawEngine::removeSpriteFrameCache(SpriteFrame* frame)
{
    m_allSpriteFrames.remove(frame->getCacheKey());
}

void DrawEngine::removeTextureCache(Texture2D* frame)
{
    m_allTextures.remove(frame->getCacheKey());
}

DE_END
