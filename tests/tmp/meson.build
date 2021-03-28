audioinc = include_directories('../../Modules/Audio')
pipelineinc = include_directories('../../Modules/Audio/pipeline')

tmpsrc = ['audiotest.cpp']

testexe = executable(
  'kingdbtest', tmpsrc,
  dependencies : [kingdbaudio_dep, pipeline_dep]
)