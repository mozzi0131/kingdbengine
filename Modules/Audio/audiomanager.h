#ifndef __KINGDBENGINE_MODULES_AUDIO_AUDIOMANAGER_HPP__
#define __KINGDBENGINE_MODULES_AUDIO_AUDIOMANAGER_HPP__

#include <vector>

// class forward declarations
// is it 'really' needed?
class AudioObj;

// TODO : in audiomanager, the soundobj should be multiple: BGM, and multiple sound effects.
// So, the manager may use the thread pooling for playing multiple sounds. (ㅠㅠ)
class AudioManager {
  public:
    AudioManager(){}
    ~AudioManager(){}
    
    void add(AudioObj *obj); // add sounds to the thread pooling.
    void shutdown(AudioObj *obj = nullptr);

  private:
    std::vector<AudioObj *> playlist; // should be implemented to thread pooling..
};

#endif // __KINGDBENGINE_MODULES_AUDIO_AUDIOMANAGER_HPP__
