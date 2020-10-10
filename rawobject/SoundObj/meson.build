# test commit

glib_dep = dependency('glib-2.0', version : '>=2.44.0' )
gst_dep = dependency('gstreamer-1.0',
              fallback : ['gstreamer', 'gst_dep'])

sources = ['soundobj.cpp']

soundlib = library('kingsoundlib', sources, 
      dependencies : [glib_dep, gst_dep])
