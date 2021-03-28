#ifndef __KINGDBENGINE_MODULES_AUDIO_AUDIOMANAGER_HPP__
#define __KINGDBENGINE_MODULES_AUDIO_AUDIOMANAGER_HPP__

#include <functional>
#include <string>
#include <vector>

#include "audioexport.h"

// class forward declarations
// is it 'really' needed?
class AudioObj;

// TODO : in audiomanager, the soundobj should be multiple: BGM, and multiple
// sound effects. So, the manager may use the thread pooling for playing
// multiple sounds.

// should add callback for each pipeline.
// 1. EOS (the pipeline should be unref)
// 2. UnloadComplete
// 3. LoadComplete

using AudioCallbackFunc =
    std::function<void(const int, const int64_t, const char *, void *)>;

//
void somethingAuidoObjectCallbackCalled(const int type, const int64_t value,
                                        const char *msg, void *data) {
  AudioObj *tmpobj = static_cast<AudioObj *>(data);

  switch (type) {
    case AUDIO_UNLOADCOMPLETE:
      break;
    case AUDIO_ERROR:
      break;
    default:
      break;
  }
}

class AudioManager {
 public:
  AudioManager();
  ~AudioManager();

  void add(std::string &fileroute,
           bool isloop);  // add sounds to the thread pooling.

  // add callback event

 private:
  // the loop is needed per one audio manager thread
  // GMainLoop *loop;
  std::vector<AudioObj *>
      playlist;  // should be implemented to thread pooling..
};

#endif  // __KINGDBENGINE_MODULES_AUDIO_AUDIOMANAGER_HPP__
