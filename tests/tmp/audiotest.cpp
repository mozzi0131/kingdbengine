#include <gst/gst.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "bgmpipeline.h"

int main() {
  std::string mp3dir =
      "C:"
      "\\Users\\User\\Desktop\\workspace\\kingdbengine\\tests\\resource\\kingdb"
      "1_resource.mp3";

  std::string newMp3dir =
      "C:"
      "\\Users\\User\\Desktop\\workspace\\kingdbengine\\tests\\resource\\freeja"
      "zz.mp3";

  BgmPipeline *obj = new BgmPipeline();
  obj->SetBGM(mp3dir);

  // std::string mp3dir2 =
  // "C:\\Users\\User\\Desktop\\workspace\\kingdbengine\\tests\\resource\\freejazz.mp3";
  // AudioObj *obj2 = new AudioObj(mp3dir2);

  // obj2->Play();
  sleep(10);

  obj->SetBGM(newMp3dir);

  sleep(10);
  obj->SetBGM(mp3dir);

  sleep(10);
  obj->Pause();
  // obj2->Pause();

  // sleep(5);
  obj->Unload();
  // obj2->Unload();

  delete obj;
  // delete obj2;

  return 0;
}
