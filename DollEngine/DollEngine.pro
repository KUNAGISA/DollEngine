#-------------------------------------------------
#
# Project created by QtCreator 2015-04-03T23:08:27
#
#-------------------------------------------------

QT       += core gui opengl

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DollEngine
TEMPLATE = app

INCLUDEPATH += widget \
	    core \
	    core/widget \
	    core/draw \
	    core/draw/texture \
	    core/draw/effect \
	    core/system \

SOURCES += main.cpp\
        MainWindow.cpp \
    core/widget/BaseCanvas.cpp \
    core/CoreTypes.cpp \
    core/draw/texture/SpriteFrame.cpp \
    core/draw/DrawEngine.cpp \
    core/system/Storages.cpp \
    core/system/Device.cpp \
    core/draw/texture/Texture2D.cpp \
    core/system/Debug.cpp \
    ProjectDirSelect.cpp \
    core/draw/effect/Effect.cpp \
    core/widget/Layer.cpp \
    core/system/Transform.cpp \
    core/draw/effect/NormalEffect.cpp \
    core/system/TouchManager.cpp

HEADERS  += MainWindow.h \
    core/widget/BaseCanvas.h \
    core/Macros.h \
    core/CoreTypes.h \
    core/draw/texture/SpriteFrame.h \
    core/draw/DrawEngine.h \
    core/system/Storages.h \
    core/system/Device.h \
    core/draw/texture/Texture2D.h \
    core/system/Debug.h \
    ProjectDirSelect.h \
    core/draw/effect/Effect.h \
    core/widget/Layer.h \
    core/system/Transform.h \
    core/draw/effect/NormalEffect.h \
    core/system/TouchManager.h

FORMS    += MainWindow.ui \
    ProjectDirSelect.ui
