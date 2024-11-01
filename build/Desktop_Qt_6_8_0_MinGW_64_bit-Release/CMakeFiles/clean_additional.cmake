# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\PlaneWar_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PlaneWar_autogen.dir\\ParseCache.txt"
  "PlaneWar_autogen"
  )
endif()
