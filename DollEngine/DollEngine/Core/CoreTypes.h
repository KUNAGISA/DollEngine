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
typedef GLuint DrawTexId;//贴图手柄
typedef GLuint DrawActiveTexId;//生效的贴图
typedef GLuint DrawPrgId; //program
typedef GLuint DrawShaderId; //shader
typedef GLuint DrawVAOId;
typedef GLenum DrawBlendId;

typedef GLsizei DrawSizeI;
typedef GLclampf DrawClampF;
typedef GLbitfield DrawMask;

class Rect
{
public:
    Rect():x(0),y(0),width(0),height(0){}
    Rect(float x,float y,float w,float h);
    void set(float x,float y,float w,float h);
    static const Rect& Zero();
    
    
    float x;
    float y;
    float width;
    float height;
};

class Size
{
public:
    Size():width(0),height(0){}
    Size(float w,float h);
    void set(float w,float h);
    static const Size& Zero();
    
    float width;
    float height;
};

class FontData
{
public:
    FontData()
    :xMin(0),xMax(0),yMin(0),yMax(0),advance(0),bearingX(0),bearingY(0),outlineSize(0){}
    int xMin;//左右宽高与orgin的偏移量
    int xMax;
    int yMin;
    int yMax;
    
    int advance;//字间距
    
    int bearingX;//图片应该的orgin偏移量
    int bearingY;
    
    float outlineSize;
};


struct GLV2F
{
    float v1;
    float v2;
};

struct GLV3F
{
    float v1;
    float v2;
    float v3;
};

struct GLV4F
{
    float v1;
    float v2;
    float v3;
    float v4;
};

struct GLVertex {
    GLV2F vertex;
    GLV4F color;
    GLV2F uv;
};

class Transform;
struct GLDrawData
{
    void setPos(float x, float y,float w,float h,Transform* trans);
    void setFrameRect(float l,float t,float r,float b);
    void setInnerRect(float l,float r,float b,float t);
    void setStart(Color* color);
    void setEnd(Color* color);
    
    GLVertex lt;
    GLVertex rt;
    GLVertex rb;
    GLVertex lb;
};

struct Scale9Config
{
    float l;
    float t;
    float b;
    float r;
};

class SpriteFrame;
class GLProgram;
struct PaintConfig
{
    Transform* trans;
    SpriteFrame* frame;
    float width;
    float height;
    Scale9Config* scale9;
    Color* start;
    Color* end;
    int gradVector;
    GLProgram* program;
    GLenum blendSrc;
    GLenum blendDst;
    bool flipY;
};

DE_END


#endif /* defined(__DollEngine__Types__) */
