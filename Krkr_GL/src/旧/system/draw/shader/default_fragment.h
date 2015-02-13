//
//  default_fragment.h
//  DollEngine
//
//  Created by DollStudio on 15/2/1.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//
#include "Macros.h"

STRING(
\n#ifdef GL_ES\n
precision lowp float;
\n#endif\n

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
uniform sampler2D tex_fore;

void main()
{
    gl_FragColor = v_fragmentColor * texture2D(tex_fore, v_texCoord);
}
);