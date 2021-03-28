#include <string>

#include "pipeline.h"

class EffectPipeline : Pipeline {
 public:
  EffectPipeline();
  ~EffectPipeline();

  void AddEffect(std::string &sourcePath);

 private:
  GstElement *pipe;

  void createPipeline();
};