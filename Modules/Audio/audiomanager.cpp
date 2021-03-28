#include "audiomanager.h"

#include <gst/gst.h>

#include "audioobject.h"

AudioManager::AudioManager() { gst_init(nullptr, nullptr); }

AudioManager::~AudioManager() {}

void AudioManager::add(std::string &fileroute, bool isloop) {
  AudioObj *obj = new AudioObj(fileroute, isloop);
  playlist.push_back(obj);

  obj->Play();
}

// callback(audioobject this, event type)
// -> if the signal has emitted by the callback, release the resource on the
// playlist. Do I really need "playlist"?
