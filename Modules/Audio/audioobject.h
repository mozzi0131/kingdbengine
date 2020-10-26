#ifndef __KINGDBENGINE_MODULES_AUDIO_AUDIOOBJECT_HPP__
#define __KINGDBENGINE_MODULES_AUDIO_AUDIOOBJECT_HPP__

#include <gst/gst.h>
#include <string>

class AudioObj {
  // virtual로 만들어서 Platform별로 확장해서 가져가게 하기
  public:
    AudioObj(std::string &fileRoute, bool isloop = false);
    ~AudioObj(){};

    void Play();
    void Pause();
    bool Unload();
    
  private:
    // whole pipeline
    GstElement *pipe;
    bool isloop;
    float volume;

    void createPipeline(std::string &fileroute);
};

#endif // __KINGDBENGINE_MODULES_AUDIO_AUDIOOBJECT_HPP__
