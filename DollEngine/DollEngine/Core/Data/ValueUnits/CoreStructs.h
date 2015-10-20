#ifndef CORESTRUCTS
#define CORESTRUCTS

#include "CoreMacros.h"

DE_BEGIN

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
class Color;
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
    Scale9Config(){
        l=t=b=r=1/3.0f;
    }
    float l;
    float t;
    float b;
    float r;
};

class ImageInfo;
class PaintProgram;
struct PaintConfig
{
    Transform* trans;
    ImageInfo* frame;
    float width;
    float height;
    Scale9Config* scale9;
    Color* start;
    Color* end;
    int gradVector;
    PaintProgram* program;
    GLenum blendSrc;
    GLenum blendDst;
    bool flipY;
};

DE_END

#endif // CORESTRUCTS

