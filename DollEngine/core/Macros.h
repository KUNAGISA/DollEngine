#ifndef MACROS_H
#define MACROS_H

#include <math.h>
//Core
#include <QDebug>
#include <QString>
#include <QSettings>
#include <QFile>
#include <QMap>
#include <QList>
#include <QCoreApplication>
#include <QMatrix>
//Qt Opengl
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#define null NULL
#define PI 3.14159265358979323846264338327950288

#define DE_BEGIN namespace DE {
#define DE_END }

#define NEED_REDRAW Device::GetInstance()->setNeedRedraw(true)
#define NEED_RETOUCH Device::GetInstance()->setNeedRetouch(true)

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

#define LAYER_PROPERTY_FUNC(NAME,VALUE) \
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


//OpenGL

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

#endif // MACROS_H

