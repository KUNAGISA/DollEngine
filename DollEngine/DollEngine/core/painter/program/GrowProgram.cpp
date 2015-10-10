//
//  GrowProgram.cpp
//  DollEngine
//
//  Created by DollStudio on 15/8/23.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "GrowProgram.h"

DE_BEGIN

GrowProgram::GrowProgram()
{
    
}

GrowProgram::~GrowProgram()
{
    
}

bool GrowProgram::bind()
{
    int index =DI->getUniform(m_programId,"resolutionX");
    if (index != -1) m_allUniformIndex["resolutionX"]=index;
    
    index =DI->getUniform(m_programId,"resolutionY");
    if (index != -1) m_allUniformIndex["resolutionY"]=index;
    
    index =DI->getUniform(m_programId,"blurRadius");
    if (index != -1) m_allUniformIndex["blurRadius"]=index;
    
    index =DI->getUniform(m_programId,"sampleNum");
    if (index != -1) m_allUniformIndex["sampleNum"]=index;
    return NormalProgram::bind();
}

const char* GrowProgram::getShader_F()
{
    return
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"
    ""
    "varying vec4 v_fragmentColor;"
    "varying vec2 v_texCoord;"
    ""
    "uniform float resolutionX;"
    "uniform float resolutionY;"
    "uniform float blurRadius;"
    "uniform float sampleNum;"
    "uniform sampler2D tex_fore;"
    ""
    "vec3 blur(vec2);"
    ""
    "void main(void)"
    "{"
        "vec3 col = blur(v_texCoord);"
        "gl_FragColor = vec4(col, 1.0) * v_fragmentColor;"
    "}"
    ""
    "vec3 blur(vec2 p)"
    "{"
        "if (blurRadius > 0.0)"
        "{"
            "vec3 col = vec3(0);"
            "float rx = 1.0/resolutionX;"
            "float ry = 1.0/resolutionY;"
            "float r = blurRadius;"
            "float count = 0.0;"
            "for (float i=-r; i<=r; i+=sampleNum) {"
                "for (float k=-r; k<=r; k+=sampleNum) {"
                    "float weight = (r - abs(i)) * (r - abs(k));"
                    "col += texture2D(tex_fore, vec2(p.x + k*r*rx, p.y + i*r*ry)).rgb * weight;"
                    "count += weight;"
                "}"
            "}"
            "return col / count + texture2D(tex_fore, p).rgb;"
        "}"
    "    "
        "return texture2D(tex_fore, p).rgb + texture2D(tex_fore, p).rgb;"
    "}";

}


void GrowProgram::actived(PaintConfig& config)
{
    float dt = 0.75f;
    setUniformValue("resolutionX", config.width);
    setUniformValue("resolutionY", config.height);
    setUniformValue("blurRadius", dt*4);
    setUniformValue("sampleNum", dt);
    NormalProgram::actived(config);
}
    //--------------------------------------------------------
    // Gaussian weighting:
    // 1  4  7  4 1
    // 4 16 26 16 4
    // 7 26 41 26 7 / 273 (i.e. divide by total of weightings)      
    // 4 16 26 16 4
    // 1  4  7  4 1    


    //--------------------------------------------------------      
    //   1 3 1
    //   3 1 3   / 11
    //   1 3 1
    
    //gl_FragColor = (sample[0] + (3.0*sample[1]) + sample[2] +     
    //  (3.0*sample[3]) + sample[4] + (3.0*sample[5]) +
    //  sample[6] + (3.0*sample[7]) + sample[8]) / 11.0;          
DE_END
