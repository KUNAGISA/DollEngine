//
//  Types.h
//  DollEngine
//
//  Created by DollStudio on 14-9-18.
//  Copyright (c) 2014年 DollStudio. All rights reserved.
//

#ifndef DollEngine_Types_h
#define DollEngine_Types_h

#include "Macros.h"

enum TEXT_ENCODING
{
    ENCODING_UTF8_WITHOUT_BOM=0,
    ENCODING_UTF8,
    ENCODING_UTF16_LITE,
    ENCODING_UTF16_BIG,
    ENCODING_UTF32_LITE,
    ENCODING_UTF32_BIG
};

enum MOUSE_BUTTON
{
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_4,
    MOUSE_BUTTON_5,
    MOUSE_BUTTON_6,
};

enum KEYBOARD_VALUE
{
    VK_LBUTTON        =0x01,
    VK_RBUTTON        =0x02,
    VK_CANCEL         =0x03,
    VK_MBUTTON        =0x04,
    VK_BACK           =0x08,
    VK_TAB            =0x09,
    VK_CLEAR          =0x0C,
    VK_RETURN         =0x0D,
    VK_SHIFT          =0x10,
    VK_CONTROL        =0x11,
    VK_MENU           =0x12,
    VK_PAUSE          =0x13,
    VK_CAPITAL        =0x14,
    VK_KANA           =0x15,
    VK_HANGEUL        =0x15,
    VK_HANGUL         =0x15,
    VK_JUNJA          =0x17,
    VK_FINAL          =0x18,
    VK_HANJA          =0x19,
    VK_KANJI          =0x19,
    VK_ESCAPE         =0x1B,
    VK_CONVERT        =0x1C,
    VK_NONCONVERT     =0x1D,
    VK_ACCEPT         =0x1E,
    VK_MODECHANGE     =0x1F,
    VK_SPACE          =0x20,
    VK_PRIOR          =0x21,
    VK_NEXT           =0x22,
    VK_END            =0x23,
    VK_HOME           =0x24,
    VK_LEFT           =0x25,
    VK_UP             =0x26,
    VK_RIGHT          =0x27,
    VK_DOWN           =0x28,
    VK_SELECT         =0x29,
    VK_PRINT          =0x2A,
    VK_EXECUTE        =0x2B,
    VK_SNAPSHOT       =0x2C,
    VK_INSERT         =0x2D,
    VK_DELETE         =0x2E,
    VK_HELP           =0x2F,
    VK_0              =0x30,
    VK_1              =0x31,
    VK_2              =0x32,
    VK_3              =0x33,
    VK_4              =0x34,
    VK_5              =0x35,
    VK_6              =0x36,
    VK_7              =0x37,
    VK_8              =0x38,
    VK_9              =0x39,
    VK_A              =0x41,
    VK_B              =0x42,
    VK_C              =0x43,
    VK_D              =0x44,
    VK_E              =0x45,
    VK_F              =0x46,
    VK_G              =0x47,
    VK_H              =0x48,
    VK_I              =0x49,
    VK_J              =0x4A,
    VK_K              =0x4B,
    VK_L              =0x4C,
    VK_M              =0x4D,
    VK_N              =0x4E,
    VK_O              =0x4F,
    VK_P              =0x50,
    VK_Q              =0x51,
    VK_R              =0x52,
    VK_S              =0x53,
    VK_T              =0x54,
    VK_U              =0x55,
    VK_V              =0x56,
    VK_W              =0x57,
    VK_X              =0x58,
    VK_Y              =0x59,
    VK_Z              =0x5A,
    VK_LWIN           =0x5B,
    VK_RWIN           =0x5C,
    VK_APPS           =0x5D,
    VK_NUMPAD0        =0x60,
    VK_NUMPAD1        =0x61,
    VK_NUMPAD2        =0x62,
    VK_NUMPAD3        =0x63,
    VK_NUMPAD4        =0x64,
    VK_NUMPAD5        =0x65,
    VK_NUMPAD6        =0x66,
    VK_NUMPAD7        =0x67,
    VK_NUMPAD8        =0x68,
    VK_NUMPAD9        =0x69,
    VK_MULTIPLY       =0x6A,
    VK_ADD            =0x6B,
    VK_SEPARATOR      =0x6C,
    VK_SUBTRACT       =0x6D,
    VK_DECIMAL        =0x6E,
    VK_DIVIDE         =0x6F,
    VK_F1             =0x70,
    VK_F2             =0x71,
    VK_F3             =0x72,
    VK_F4             =0x73,
    VK_F5             =0x74,
    VK_F6             =0x75,
    VK_F7             =0x76,
    VK_F8             =0x77,
    VK_F9             =0x78,
    VK_F10            =0x79,
    VK_F11            =0x7A,
    VK_F12            =0x7B,
    VK_F13            =0x7C,
    VK_F14            =0x7D,
    VK_F15            =0x7E,
    VK_F16            =0x7F,
    VK_F17            =0x80,
    VK_F18            =0x81,
    VK_F19            =0x82,
    VK_F20            =0x83,
    VK_F21            =0x84,
    VK_F22            =0x85,
    VK_F23            =0x86,
    VK_F24            =0x87,
    VK_NUMLOCK        =0x90,
    VK_SCROLL         =0x91,
    VK_LSHIFT         =0xA0,
    VK_RSHIFT         =0xA1,
    VK_LCONTROL       =0xA2,
    VK_RCONTROL       =0xA3,
    VK_LMENU          =0xA4,
    VK_RMENU          =0xA5,
    VK_PADLEFT        =0x1B5,
    VK_PADUP          =0x1B6,
    VK_PADRIGHT       =0x1B7,
    VK_PADDOWN        =0x1B8,
    VK_PAD1           =0x1C0,
    VK_PAD2           =0x1C1,
    VK_PAD3           =0x1C2,
    VK_PAD4           =0x1C3,
    VK_PAD5           =0x1C4,
    VK_PAD6           =0x1C5,
    VK_PAD7           =0x1C6,
    VK_PAD8           =0x1C7,
    VK_PAD9           =0x1C8,
    VK_PAD10          =0x1C9,
    VK_PADANY         =0x1DF,
    VK_PROCESSKEY     =0xE5,
    VK_ATTN           =0xF6,
    VK_CRSEL          =0xF7,
    VK_EXSEL          =0xF8,
    VK_EREOF          =0xF9,
    VK_PLAY           =0xFA,
    VK_ZOOM           =0xFB,
    VK_NONAME         =0xFC,
    VK_PA1            =0xFD,
    VK_OEM_CLEAR      =0xFE,
};

enum KEYBOARD_SHIFT_VALUE
{
    SV_NONE = 0,
    SV_SHIFT = KEYBOARD_VALUE::VK_SHIFT,
    SV_ALT = KEYBOARD_VALUE::VK_MENU,
    SV_CONTROL = KEYBOARD_VALUE::VK_CONTROL,//window下，两个的值是一样的，mac不同
    SV_COMMAND = KEYBOARD_VALUE::VK_CONTROL,
};

enum MOUSE_STATE
{
    MOUSE_EMPTY=0,
    MOUSE_DOWN,
    MOUSE_UP,
    MOUSE_MOVE,
    MOUSE_CANCEL,
};

struct kRect
{
    kRect():left(0),top(0),width(0),height(0){}
    kRect(float x,float y,float w,float h):left(x),top(y),width(w),height(h){}
    float left;
    float top;
    float width;
    float height;
};
struct Vector4F
{
    Vector4F():r(1),g(1),b(1),a(1){}
    Vector4F(float tr,float tg,float tb,float ta):r(tr),g(tg),b(tb),a(ta){}
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

struct Color3B
{
    GLubyte r;
    GLubyte g;
    GLubyte b;
};

struct Color4B
{
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};

struct GradualColor
{
    Vector4F top;
    Vector4F bottom;
    bool vertical;
};

struct Vector2F
{
    Vector2F():x(0),y(0){}
    Vector2F(float tx,float ty):x(tx),y(ty){}
    GLfloat x;
    GLfloat y;
    void set(float x,float y){this->x=x,this->y=y;}
};

struct Vector3F
{
    float x;
    float y;
    float z;
};



#endif
