//
//  Macros.h
//  DollEngine
//
//  Created by DollStudio on 15/4/13.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#ifndef DollEngine_Macros_h
#define DollEngine_Macros_h

#include <string>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "kazmath.h"

using namespace std;


#define null NULL
#define PI 3.14159265358979323846264338327950288

#define DE_BEGIN namespace DE {
#define DE_END }

#define NEED_REDRAW 
//Device::GetInstance()->setNeedRedraw(true)
#define NEED_RETOUCH 
//Device::GetInstance()->setNeedRetouch(true)

#define Shared(type) static type* GetInstance() \
{\
static type* _instance=NULL;\
if(!_instance) \
_instance = new type(); \
return  _instance; \
}

#define PROPERTY(type,func,value) \
protected:\
type value;\
public:\
type get##func(){return value;}\
virtual void set##func(type v)

#define PROPERTY_CONST(type,func,value) \
protected:\
type value;\
public:\
type get##func(){return value;}\
virtual void set##func(const type & v)

#define PROPERTY_RO(type,func,value) \
protected:\
type value;\
public:\
type get##func(){return value;}

#define TRANSFORM_PROPERTY_FUNC(NAME,VALUE) \
void set##NAME(float v) \
{\
if (m_transform) { \
m_transform->set##VALUE(v);\
NEED_REDRAW;\
}\
}\
float get##NAME()\
{\
if (m_transform) {\
return m_transform->get##VALUE();\
}\
return 0;\
}

#define SAFF_DELETE(OBJ) if(OBJ){delete OBJ;OBJ=NULL;}
#define SAFF_DELETE_ARRAY(OBJ) if(OBJ){delete[] OBJ;OBJ=NULL;}
#define SAFF_RETAIN(OBJ) if(OBJ){OBJ->retain();}
#define SAFF_RELEASE(OBJ) if(OBJ){OBJ->release();OBJ=NULL;}

#pragma mark -
#pragma mark GL相关

#include <OpenGL/gl.h>

#define CHECK_GL_ERROR if(glGetError()){printf("OpenGL 出错:%x",glGetError());}

#endif
