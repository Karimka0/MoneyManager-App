# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/Wallet_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Wallet_autogen.dir/ParseCache.txt"
  "Wallet_autogen"
  )
endif()
