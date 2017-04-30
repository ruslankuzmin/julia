#ifndef TARGET_SOUND_H
#define TARGET_SOUND_H

#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include "data_types.h"


const int SRATE = 44100;
const int SSIZE = 1024;


class TargetSound {
public:
    TargetSound();
    ~TargetSound();
    void getSound(SoundChunk sound);
private:
    ALbyte buffer[22050];
    ALint sample;
    ALCdevice *device;
};

/*
void WorkWithSound(ALshort **input_audio,ALshort **output_audio)
{
    SoundManager s;
    std::cout<<1;
    while (1) {
        s.input(input_audio,output_audio);
        //s.output();
    }
}

//Sound init begin
    int  play_buf_size = 44100;
    const unsigned int frequ=44100;
    ALshort *input_audio[frequ];
    ALshort *output_audio[frequ];
    std::thread sound_thread(WorkWithSound,std::ref(input_audio),std::ref(output_audio));
    sound_thread.detach();
//Sound init end
*/



#endif // TARGET_SOUND_H
