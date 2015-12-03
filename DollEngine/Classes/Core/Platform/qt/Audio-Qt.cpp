#include "Audio.h"
#include "Storages.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimeLine>

DE_BEGIN

#define AUDIO_OBJ ((QMediaPlayer*)m_object)
#define AUDIO_TIMELINE ((QTimeLine*)m_fadeTimerLine)

Audio::Audio()
    :m_object(NULL)
    ,m_fadeTimerLine(NULL)
    ,m_loop(1)
    ,m_muted(false)
    ,m_volume(100)
    ,m_position(0)
{
}

Audio::~Audio()
{
    if(m_object){
        delete (QMediaPlayer*)m_object;
    }
    if(m_fadeTimerLine){
        delete (QTimeLine*)m_fadeTimerLine;
    }
}

bool Audio::preload(const String& path)
{
    if(!m_object) {
        m_object = new QMediaPlayer();
    }
    m_fullPath = Storages::GetInstance()->getFullPath(path);
    QMediaPlaylist* playList = new QMediaPlaylist();
    playList->addMedia(QUrl(m_fullPath.c_nstr()));
    AUDIO_OBJ->setPlaylist(playList);
    AUDIO_OBJ->stop();
    setVolume(m_volume);
    setMuted(m_muted);
    setLoop(m_loop);
    setPosition(0);
}

void Audio::play(bool isloop,int fadeMS)
{
    if(!m_object) return;
    setLoop(isloop);
    if(fadeMS == 0){
        AUDIO_OBJ->play();
        onPlay();
    }
}

void Audio::stop(int fadeMS)
{
    if(!m_object) return;
    if(fadeMS == 0){
        AUDIO_OBJ->stop();
        onStop();
    }
}

void Audio::pause()
{
    if(!m_object) return;
    AUDIO_OBJ->pause();
    onPause();
}

void Audio::resume()
{
    if(!m_object) return;
    AUDIO_OBJ->play();
    onResume();
}

void Audio::fadeTo(float dut,int tarVol)
{
    m_volume = tarVol;
    if(!m_fadeTimerLine){
        m_fadeTimerLine = new QTimeLine();
    }
    AUDIO_TIMELINE->setDuration(dut*1000);
    AUDIO_TIMELINE->setFrameRange(AUDIO_OBJ->volume(),tarVol);
    AUDIO_OBJ->connect(AUDIO_TIMELINE,SIGNAL(frameChanged(int)),AUDIO_OBJ,SLOT(QMediaPlayer::setVolume(int)));
}


void Audio::setLoop(bool v)
{
    m_loop = v;
    if(!m_object) return;
    if(v){
        AUDIO_OBJ->playlist()->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }
    else {
        AUDIO_OBJ->playlist()->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    }
}

void Audio::setMuted(bool v)
{
    m_muted = v;
    onMutedChanged(v);
    if(!m_object) return;
    AUDIO_OBJ->setMuted(v);
}

void Audio::setVolume(float v)
{
    m_volume = v;
    onVolumeChanged(v);
    if(!m_object) return;
    AUDIO_OBJ->setVolume(v);
}

void Audio::setPosition(int v)
{
    m_position=v;
    onPositionChanged(v);
    if(!m_object) return;
    AUDIO_OBJ->setPosition(v);
}

void Audio::onMutedChanged(bool v)
{

}

void Audio::onVolumeChanged(bool v)
{

}

void Audio::onPositionChanged(int v)
{

}

void Audio::onPause()
{

}

void Audio::onResume()
{

}

void Audio::onPlay()
{

}

void Audio::onStop()
{

}


DE_END
