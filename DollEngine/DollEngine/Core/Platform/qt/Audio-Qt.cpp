#include "Audio.h"
#include "Storages.h"
#include <QSoundEffect>

DE_BEGIN

#define AUDIO_OBJ ((QSoundEffect*)m_object)

Audio::Audio()
{
    m_object = new QSoundEffect();
}

Audio::~Audio()
{
    delete AUDIO_OBJ;
}

bool Audio::preload(const String& path)
{
    String fullpath = Storages::GetInstance()->getFullPath(path);
    AUDIO_OBJ->setSource(QUrl(fullpath.c_nstr()));
    AUDIO_OBJ->stop();
    AUDIO_OBJ->setVolume(m_volume/100.0f);
}

void Audio::play(bool isloop,int fadeMS)
{
    if(fadeMS == 0){
        AUDIO_OBJ->play();
    }
}

void Audio::stop(int fadeMS)
{
    if(fadeMS == 0){
        AUDIO_OBJ->stop();
    }
}

void Audio::pause()
{
    AUDIO_OBJ
}

void Audio::resume()
{
    
}

void Audio::fadeTo(int tarVol)
{
    
}


void Audio::setLoop(bool v)
{
    
}

void Audio::setVolume(float v)
{
    
}

DE_END
