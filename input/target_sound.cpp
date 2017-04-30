#include "target_sound.h"

TargetSound::TargetSound() {
    device = alcCaptureOpenDevice(NULL, SRATE, AL_FORMAT_STEREO16, SSIZE);
    if (alGetError() != AL_NO_ERROR) {
        std::cerr<<"AL_NO_ERROR"<<std::endl;
        exit(0);
        return;
    }
    alcCaptureStart(device);
}

void TargetSound::getSound(SoundChunk sound)
{
    alcGetIntegerv(device, ALC_CAPTURE_SAMPLES, (ALCsizei)sizeof(ALint), &sample);
    alcCaptureSamples(device, (ALCvoid *)buffer, sample);
}

TargetSound::~TargetSound() {
    alcCaptureStop(device);
    alcCaptureCloseDevice(device);
}
