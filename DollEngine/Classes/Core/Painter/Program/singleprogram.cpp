#include "singleprogram.h"
#include "PaintEngine.h"

DE_BEGIN

SingleProgram::SingleProgram()
{
    
}

bool SingleProgram::init()
{
    addShader(SHADER_TYPE_VERTEX,getShader_V());
    addShader(SHADER_TYPE_FRAGMENT,getShader_F());
    
    if(link()) {
        bind();
        return true;
    }
    return false;
}

const char* SingleProgram::getShader_V()
{
    return
    "attribute vec4 a_position;\n"
    "attribute vec4 a_texCoord;\n"
    "varying vec4 texc;\n"
    "uniform mat4 matrix;\n"
    "void main(void)\n"
    "{\n"
    "    gl_Position = matrix * a_position;\n"
    "    texc = a_texCoord;\n"
    "}\n";
}

const char* SingleProgram::getShader_F()
{
    return
    "uniform sampler2D tex_fore;\n"
    "varying vec4 texc;\n"
    "void main(void)\n"
    "{\n"
    "    gl_FragColor = texture2D(tex_fore, texc.st);\n"
    "}\n";

}


DE_END
