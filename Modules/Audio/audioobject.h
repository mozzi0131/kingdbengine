#ifndef __KINGDBENGINE_MODULES_AUDIO_AUDIOOBJECT_HPP__
#define __KINGDBENGINE_MODULES_AUDIO_AUDIOOBJECT_HPP__

#include <gst/gst.h>

#include <string>

class AudioObj {
  // TODO : make the class func as virtual, so we can use this on the other
  // platform with more flexibility
 public:
  AudioObj(std::string &fileRoute, bool isloop = false);
  ~AudioObj();

  void Play();
  void Pause();
  bool Unload();

 private:
  GstBus *bus;
  GMainLoop *loop;
  // whole pipeline
  GstElement *pipe;

  bool bIsloop;
  guint busID;
  float volume;

  void createPipeline(std::string &fileroute);
};

#endif  // __KINGDBENGINE_MODULES_AUDIO_AUDIOOBJECT_HPP__
