#ifndef __MODULES_AUDIO_PIPELINE_PIPELINE_H__
#define __MODULES_AUDIO_PIPELINE_PIPELINE_H__

#include <gst/gst.h>

class Pipeline {
 public:
  Pipeline();
  ~Pipeline();

  void Play();
  void Pause();
  void Ready();
  void Unload();

 private:
  GstPipeline *pipe;
  virtual void createPipeline() = 0;
};

#endif  // __MODULES_AUDIO_PIPELINE_PIPELINE_H__