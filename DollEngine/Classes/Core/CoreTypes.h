//
//  Types.h
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef __DollEngine__Types__
#define __DollEngine__Types__

#include "CoreMacros.h"
#include "Color.h"
#include "CoreString.h"
#include "CoreStructs.h"
#include "Console.h"

DE_BEGIN

enum {
    VERTEX_ATTRIB_FLAG_NONE       = 0,
    
    VERTEX_ATTRIB_FLAG_POSITION   = 1 << 0,
    VERTEX_ATTRIB_FLAG_COLOR      = 1 << 1,
    VERTEX_ATTRIB_FLAG_TEX_COORD = 1 << 2,
    
    VERTEX_ATTRIB_FLAG_POS_COLOR_TEX = (VERTEX_ATTRIB_FLAG_POSITION | VERTEX_ATTRIB_FLAG_COLOR | VERTEX_ATTRIB_FLAG_TEX_COORD),
};

enum PROGRAM_ATTRIBUTE
{
    PROGRAM_VERTEX_ATTRIBUTE=0,
    PROGRAM_COLOR_ATTRIBUTE,
    PROGRAM_TEXCOORD_ATTRIBUTE,
    PROGRAM_OPACITY_ATTRIBUTE,
    PROGRAM_TEXTURE_ATTRIBUTE,
    PROGRAM_FBO_ATTRIBUTE,
    PROGRAM_MATRIX_ATTRIBUTE,
};

enum PROGRAM_TYPE
{
    NORMAL_PROGRAM = 0,//正常模式
    CROSSFADE_PROGRAM = 1,//trans中使用的crossfade模式
};


typedef GLuint DrawFBOId;//fbo手柄
typedef GLint DrawOldFBOId;//fbo手柄
typedef GLuint DrawTexId;//贴图手柄
typedef GLuint DrawActiveTexId;//生效的贴图
typedef GLuint DrawPrgId; //program
typedef GLuint DrawShaderId; //shader
typedef GLuint DrawVAOId;
typedef GLenum DrawBlendId;

typedef GLsizei DrawSizeI;
typedef GLclampf DrawClampF;
typedef GLbitfield DrawMask;

typedef wchar_t kagchar;

DE_END


#endif /* defined(__DollEngine__Types__) */
