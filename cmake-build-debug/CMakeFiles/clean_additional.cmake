# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CommandWidget_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CommandWidget_autogen.dir\\ParseCache.txt"
  "CommandWidget_autogen"
  )
endif()
