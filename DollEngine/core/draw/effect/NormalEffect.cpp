#include "NormalEffect.h"

DE_BEGIN

NormalEffect::NormalEffect()
{
    
}

NormalEffect::~NormalEffect()
{
    
}

bool NormalEffect::init()
{
    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "attribute highp vec4 vertex;\n"
        "attribute mediump vec4 texCoord;\n"
        "varying mediump vec4 texc;\n"
        "uniform mediump mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix * vertex;\n"
        "    texc = texCoord;\n"
        "}\n";
    if(!vshader->compileSourceCode(vsrc)) {
        return false;
    }

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
        "uniform sampler2D texture;\n"
        "varying mediump vec4 texc;\n"
        "void main(void)\n"
        "{\n"
        "    gl_FragColor = texture2D(texture, texc.st);\n"
        "}\n";
    if(!fshader->compileSourceCode(fsrc)) {
        return false;
    }

    addShader(vshader);
    addShader(fshader);
    bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    link();

    bind();
    setUniformValue("texture", 0);
    return true;
}

void NormalEffect::actived()
{
    enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
    setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));
}

DE_END
