#ifndef TARGET_SOUND_H
#define TARGET_SOUND_H

#include <iostream>

#include "AL/al.h"
#include "AL/alc.h"

#define BUF_COUNT 5

class SoundManager {
public:
    SoundManager();
    ~SoundManager();
    void input(ALshort ** input_audio,ALshort ** output_audio);
    void process();
private:
    ALCdevice * in_device;
    ALCdevice * out_device;
    ALCcontext * context;
    ALuint al_source;
    ALuint al_buffers[BUF_COUNT];
    ALshort *play_buf[44100];
    int read_buf_size;
    int play_buf_size;
    ALenum  error;
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
