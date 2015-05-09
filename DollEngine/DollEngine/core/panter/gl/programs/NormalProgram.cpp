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

static GLfloat colors[4][4] = {
    {1.0,1.0,1.0,1.0},
    {1.0,1.0,1.0,1.0},
    {1.0,1.0,1.0,1.0},
    {1.0,1.0,1.0,1.0},
};
void NormalProgram::actived(SpriteFrame* frame,Transform* trans,Color* color,bool isFlipY)
{
    Rect rect = frame->getRect();
    static GLfloat vertices[] = {
        0,0,
        0,rect.height,
        rect.width,rect.height,
        rect.width,0
    };
#define VE0(p) vertices[p]=0
#define VEH(p) vertices[p]=rect.height
#define VEW(p) vertices[p]=rect.width
    
    VE0(0);VE0(1);//左下
    VE0(2);VEH(3);//左上
    VEW(4);VEH(5);//右上
    VEW(6);VE0(7);//右下
//    if(isFlipY)
//    {
//        vertices[0]=0,          vertices[1]=rect.height,    vertices[2]=0,
//        vertices[3]=0,          vertices[4]=0,              vertices[5]=0,
//        vertices[6]=rect.width, vertices[7]=0,              vertices[8]=0,
//        vertices[9]=rect.width, vertices[10]=rect.height,    vertices[11]=0;
//    }
//    else
//    {
//        vertices[0]=0,          vertices[1]=0,
//        vertices[2]=0,          vertices[3]=rect.height,
//        vertices[4]=rect.width, vertices[5]=rect.height,
//        vertices[6]=rect.width, vertices[7]=0;
//    }
    
    static float coords[4][2] = {
        { 0, 0 },
        { 0, 1 },
        { 1, 1 },
        { 1, 0 }
    };
//    coords[0][0] = coords[3][0] = rect.width;
//  //    color->r/=2;
//    color->g/=2;
//    color->b/=2;
//    color->a/=2;
//  coords[0][1] = coords[1][1] = rect.height;
    //    vector<GLfloat> vertData;
    static GLubyte tcolors[4][4];
    for (int j = 0; j < 4; ++j) {
//        memcpy(tcolors[j], color, sizeof(GLubyte)*4);
        color->toColorF(colors[j]);
    }
    
    enableVertexAttribs(VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    
    glVertexAttribPointer(PROGRAM_VERTEX_ATTRIBUTE, 2, GL_FLOAT, GL_TRUE, 0, vertices);
    glVertexAttribPointer(PROGRAM_COLOR_ATTRIBUTE, 4, GL_FLOAT, GL_TRUE, 0, colors);
    glVertexAttribPointer(PROGRAM_TEXCOORD_ATTRIBUTE, 2, GL_FLOAT, GL_TRUE, 0, coords);
    
}

DE_END