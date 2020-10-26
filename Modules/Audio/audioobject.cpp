#include "audioobject.h"

AudioObj::AudioObj(std::string &fileroute, bool isloop)
  : pipe(nullptr), 
    volume(1.0f) {
    this->isloop = isloop;

    // create audio pipeline by using fileroute
    createPipeline(fileroute);
}

void AudioObj::createPipeline(std::string &fileroute){
  pipe = gst_pipeline_new("audiopipeline");

  // the audio codec is always mp3
  GstElement *src = gst_element_factory_make("filesrc", nullptr);
  GstElement *parser = gst_element_factory_make("mpegaudioparse", nullptr);
  GstElement *dec = gst_element_factory_make("avdec_mp3", nullptr); // mpg123audiodec?
  GstElement *converter =
        gst_element_factory_make("audioconvert", nullptr);
  GstElement *resampler =
        gst_element_factory_make("audioresample", nullptr);
  // I should care about cross-platform.
  // Maybe have to use OpenAL? (oh no)
  GstElement *sink = gst_element_factory_make("directsoundsink", nullptr);

  gst_element_link_many(src, parser, dec, converter, resampler, sink, nullptr);

  g_object_set(G_OBJECT(src), "location", fileroute.c_str(), nullptr);
}

void AudioObj::Play(){
  gst_element_set_state(pipe, GST_STATE_PLAYING);
}

void AudioObj::Pause(){
  gst_element_set_state(pipe, GST_STATE_PAUSED);
}

bool AudioObj::Unload(){
  gst_element_set_state(pipe, GST_STATE_NULL);

  return true;
}