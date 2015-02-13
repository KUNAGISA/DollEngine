//
//  default_vertex.h
//  DollEngine
//
//  Created by DollStudio on 15/2/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "Macros.h"

STRING(
uniform mat4 matrix;
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

\n#ifdef GL_ES\n
varying lowp vec4 v_fragmentColor;
varying mediump vec2 v_texCoord;
\n#else\n
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
\n#endif\n

void main()
{
    gl_Position = matrix * a_position;
    v_fragmentColor = a_color;
    v_texCoord = a_texCoord;
}	
);
