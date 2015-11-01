#include "singleprogram.h"

DE_BEGIN

SingleProgram::SingleProgram()
{
    
}

const char* SingleProgram::getShader_V()
{
    return
    "attribute highp vec4 vertex;\n"
    "attribute mediump vec4 texCoord;\n"
    "varying mediump vec4 texc;\n"
    "uniform mediump mat4 matrix;\n"
    "void main(void)\n"
    "{\n"
    "    gl_Position = matrix * vertex;\n"
    "    texc = texCoord;\n"
    "}\n";
}

const char* SingleProgram::getShader_F()
{
    return
    "uniform sampler2D texture;\n"
    "varying mediump vec4 texc;\n"
    "void main(void)\n"
    "{\n"
    "    gl_FragColor = texture2D(texture, texc.st);\n"
    "}\n";

}


DE_END
