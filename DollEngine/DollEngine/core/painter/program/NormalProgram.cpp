//
//  NormalProgram.cpp
//  DollEngine
//
//  Created by DollStudio on 15/4/19.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "NormalProgram.h"

DE_BEGIN


NormalProgram::NormalProgram()
{
    
}

NormalProgram::~NormalProgram()
{
    
}

bool NormalProgram::init()
{
    GLShaderObject *vshader = new GLShaderObject();
    vshader->setType(SHADER_TYPE_VERTEX);
    const char *vsrc =
    "uniform mat4 matrix;"
    "attribute vec4 a_position;"
    "attribute vec2 a_texCoord;"
    "attribute vec4 a_color;"
    "\n#ifdef GL_ES\n"
    "varying lowp vec4 v_fragmentColor;"
    "varying mediump vec2 v_texCoord;"
    "\n#else\n"
    "varying vec4 v_fragmentColor;"
    "varying vec2 v_texCoord;"
    "\n#endif\n"
    "void main()"
    "{"
        "gl_Position = matrix * a_position;"
        "v_fragmentColor = a_color;"
        "v_texCoord = a_texCoord;"
    "}";
    if(!vshader->compileShaderCode(vsrc)) {
        return false;
    }
    
    GLShaderObject *fshader = new GLShaderObject();
    fshader->setType(SHADER_TYPE_FRAGMENT);
    const char *fsrc =
    "#ifdef GL_ES\n"
    "precision lowp float;"
    "\n#endif\n"
    "varying vec4 v_fragmentColor;"
    "varying vec2 v_texCoord;"
    "uniform sampler2D tex_fore;"
    "void main()"
    "{"
        "gl_FragColor = v_fragmentColor * texture2D(tex_fore, v_texCoord);"
    "}";
    if(!fshader->compileShaderCode(fsrc)) {
        return false;
    }
    
    addShader(vshader);
    addShader(fshader);
    
    link();
    
    bind();
    return true;
}

void NormalProgram::actived(PaintConfig& config)
{
    static GLfloat vertices[] = {
        0,0,
        0,0,
        0,0,
        0,0
    };
#define VE0(p) vertices[p]=0
#define VEH(p) vertices[p]=config.height
#define VEW(p) vertices[p]=config.width
    
    VE0(0);VE0(1);//左下
    VE0(2);VEH(3);//左上
    VEW(4);VEH(5);//右上
    VEW(6);VE0(7);//右下
    
    GLfloat colors[4][4];
    memset(colors, 1.0f, 16);
    if (config.end) {
        int idx[4];
        if(config.gradVector == 1){
            idx[0]=1;idx[1]=2;idx[2]=3;idx[3]=0;
        }
        else if(config.gradVector == 2){
            idx[0]=0;idx[1]=1;idx[2]=2;idx[3]=3;
        }
        else if(config.gradVector == 3){
            idx[0]=2;idx[1]=3;idx[2]=0;idx[3]=1;
        }
        else {
            idx[0]=3;idx[1]=0;idx[2]=1;idx[3]=2;
        }
        config.color->toColorF(colors[idx[0]]);
        config.color->toColorF(colors[idx[1]]);
        config.end->toColorF(colors[idx[2]]);
        config.end->toColorF(colors[idx[3]]);
    }
    else {
        for (int j = 0; j < 4; ++j) {
            config.color->toColorF(colors[j]);
        }
    }
    enableVertexAttribs(VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    
    glVertexAttribPointer(PROGRAM_VERTEX_ATTRIBUTE, 2, GL_FLOAT, GL_TRUE, 0, vertices);
    glVertexAttribPointer(PROGRAM_COLOR_ATTRIBUTE, 4, GL_FLOAT, GL_TRUE, 0, colors);
    glVertexAttribPointer(PROGRAM_TEXCOORD_ATTRIBUTE, 2, GL_FLOAT, GL_TRUE, 0, config.frame->getGLCoord());
    CHECK_GL_ERROR;
    
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

DE_END