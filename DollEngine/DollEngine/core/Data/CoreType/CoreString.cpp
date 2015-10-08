//
//  String.cpp
//  DollEngine
//
//  Created by DollStudio on 15/10/7.
//  Copyright (c) 2015年 DollStudio. All rights reserved.
//

#include "CoreString.h"

DE_BEGIN

String String::fromFormat(const char* format,...)
{

}

String::String()
{

}

String::String(char v)
{

}

String::String(wchar_t v)
{

}

String::String(char* v,int len)
{

}

String::String(wchar_t* v,int len)
{

}

String::String(const string& v)
{

}

String::String(const wstring& v)
{

}

String::String(const String& v)
{

}

String::String(int v)
{

}

String::String(double v)
{

}

String::String(float v)
{

}

String::String(int64_t v)
{

}

String::~String()
{

}

bool String::readFromFile(const String& path)
{

}

const String::String& operator+ (const String& v)
{

}

const String::String& operator+= (const String& v)
{

}

const String::String& operator<< (const String& v)
{

}

String String::operator[] (const String& v)
{

}

bool String::operator< (const String& v)
{

}

bool String::operator> (const String& v)
{

}

bool String::operator== (const String& v)
{

}


int String::toInt()
{

}

int64_t String::toInt64()
{

}

double String::toDouble()
{

}

char String::toChar()
{

}

wchar_t String::toWChar()
{

}

const string& String::toUtf8()
{

}

const wstring& String::toUnicode()
{

}

const char* String::c_str()
{

}

const wchar_t* String::c_wstr()
{

}


DE_END
