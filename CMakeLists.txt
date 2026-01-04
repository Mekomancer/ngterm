cmake_minimum_required(VERSION 4.2) # nice
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_COMPILER_IMPORT_STD 23 26)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY target)

project(ngterm
  VERSION 0.1.2 # SemVer
  DESCRIPTION "'Nother go termnial"
  LANGUAGES CXX
)

set(cxx_modules_path NOTFOUND)
set(homedir NOTFOUND)

file(REAL_PATH ~ homedir EXPAND_TILDE) 

find_path(cxx_modules_path std.cppm 
  PATHS ${homedir}
  PATH_SUFFIXES /llvm-project/build/modules/c++/v1/
  REQUIRED
)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
     "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(FetchContent)
FetchContent_Declare(
  std
  SOURCE_DIR ${cxx_modules_path}
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  SYSTEM
)
FetchContent_MakeAvailable(std)

add_executable(ngterm
  src/main.cpp
)

target_sources(ngterm 
  PRIVATE
  FILE_SET CXX_MODULES
  BASE_DIRS src
  FILES
  src/types.cxx
)

add_custom_target(format 
  COMMAND clang-format -i
  "$<PATH:ABSOLUTE_PATH,$<TARGET_PROPERTY:ngterm,SOURCES>
  ,${CMAKE_SOURCE_DIR}>"
  "$<PATH:ABSOLUTE_PATH,$<TARGET_PROPERTY:ngterm,CXX_MODULE_SET>
  ,${CMAKE_SOURCE_DIR}>"
  COMMAND_EXPAND_LISTS
  VERBATIM
)

target_compile_definitions(ngterm PRIVATE VERSION=\"${PROJECT_VERSION}\")

target_link_libraries(ngterm std)
