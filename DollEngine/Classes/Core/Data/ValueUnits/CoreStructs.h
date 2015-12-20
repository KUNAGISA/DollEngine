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

class Point
{
public:
    Point():x(0),y(0){}
    Point(float x,float y){set(x,y);}
    void set(float x,float y){
        this->x = x;
        this->y = y;
    }
    float x;
    float y;
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
    :xMin(0),xMax(0),yMin(0),yMax(0),width(0),height(0),advance(0),bearingX(0),bearingY(0),outlineSize(0){}
    int xMin;//左右宽高与orgin的偏移量
    int xMax;
    int yMin;
    int yMax;
    
    int width;//文字的逻辑高
    int height;//文字的逻辑宽
    
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
class GradientColor;
struct PaintConfig
{
    Transform* trans;
    ImageInfo* info;
    PaintProgram* program;
    GLenum blendSrc;
    GLenum blendDst;
    bool flipX;
    bool flipY;
};

DE_END

#endif // CORESTRUCTS

