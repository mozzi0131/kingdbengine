#include "audioobject.h"

#include <iostream>
namespace {
static gboolean busCallback(GstBus *bus, GstMessage *msg, gpointer data) {
  // send the pipeline itself as a data
  printf("Got %s message\n", GST_MESSAGE_TYPE_NAME(msg));

  std::cout << "busCallback has been called" << std::endl;

  AudioObj *pipe = static_cast<AudioObj *>(data);
  if (pipe == nullptr) {
    std::cout << "AudioObj is null" << std::endl;
  }

  switch (GST_MESSAGE_TYPE(msg)) {
    case GST_MESSAGE_ERROR:
      std::cout << "error" << std::endl;
      // close itself
      // signal_emit
      pipe->Unload();
      break;
    case GST_MESSAGE_EOS:
      // signal_emit
      // close itself
      std::cout << "eos" << std::endl;
      pipe->Unload();
      break;
    default:
      std::cout << "msg is " << GST_MESSAGE_TYPE(msg) << std::endl;
      // print the type of the event
      break;
  }

  return true;
}
}  // namespace

AudioObj::AudioObj(std::string &fileroute, bool isloop)
    : pipe(nullptr), bus(nullptr), loop(nullptr), volume(1.0f) {
  gst_init(nullptr, nullptr);
  this->bIsloop = isloop;

  // create audio pipeline by using fileroute
  createPipeline(fileroute);
}

AudioObj::~AudioObj() {
  // do something
}

void AudioObj::createPipeline(std::string &fileroute) {
  pipe = gst_pipeline_new("audiopipeline");

  // the audio codec is always mp3
  GstElement *src = gst_element_factory_make("filesrc", nullptr);
  GstElement *parser = gst_element_factory_make("mpegaudioparse", nullptr);
  GstElement *dec =
      gst_element_factory_make("avdec_mp3", nullptr);  // mpg123audiodec?
  GstElement *converter = gst_element_factory_make("audioconvert", nullptr);
  GstElement *resampler = gst_element_factory_make("audioresample", nullptr);
  // I should care about cross-platform.
  // Maybe have to use OpenAL? (oh no)
  GstElement *sink = gst_element_factory_make("directsoundsink", nullptr);

  gst_bin_add_many(GST_BIN(pipe), src, parser, dec, converter, resampler, sink,
                   nullptr);

  if (!gst_element_link_many(src, parser, dec, converter, resampler, sink,
                             nullptr)) {
    // update error status
  }

  g_object_set(G_OBJECT(src), "location", fileroute.c_str(), nullptr);

  bus = gst_pipeline_get_bus(GST_PIPELINE(pipe));
  if (bus == nullptr) std::cout << "bus is NULL" << std::endl;
  busID = gst_bus_add_watch(bus, (GstBusFunc)busCallback, this);
  gst_object_unref(bus);
  std::cout << "Add busCallback" << std::endl;

  // loop = g_main_loop_new (NULL, FALSE);
  // g_main_loop_run (loop);
}

void AudioObj::Play() {
  std::cout << "Call the play" << std::endl;
  GstStateChangeReturn ret = gst_element_set_state(pipe, GST_STATE_PLAYING);

  if (GST_STATE_CHANGE_SUCCESS == ret) {
    // return true? call the Callback
    std::cout << "Call the Play\n";

    // get the bus from the pipeline
  }
}

void AudioObj::Pause() { gst_element_set_state(pipe, GST_STATE_PAUSED); }

bool AudioObj::Unload() {
  // g_main_loop_quit(loop);

  gst_element_set_state(pipe, GST_STATE_NULL);
  g_object_unref(pipe);
  g_source_remove(busID);
  g_main_loop_unref(loop);

  return true;
}