#include <string>

#include "pipeline.h"

class BgmPipeline : Pipeline {
 public:
  BgmPipeline();
  ~BgmPipeline();

  void SetBGM(std::string &location);

 private:
  GstElement *pipe;
  guint busID;
  GstBus *bus;

  void createPipeline();

  void flush();
};