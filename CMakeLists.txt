cmake_minimum_required(VERSION 4.2) # nice
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_COMPILER_IMPORT_STD 23 26)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BINARY_DIR build)
set(CMAKE_SOURCE_DIR src)

project(ngTerm
  VERSION 0.1.0 # SemVer
  DESCRIPTION "A terminal with an emphasis on features without overhead"
  LANGUAGES CXX
)

include(FetchContent)
FetchContent_Declare(
  std
  URL "file:///home/mark/llvm-project/build/modules/c++/v1/"
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
  src/ngterm.cxx
  src/cmdline.cxx
  src/pty.cxx
  src/types.cxx
)

add_custom_target(format 
  clang-format-20 -i $<TARGET_PROPERTY:ngterm,SOURCES> 
  $<TARGET_PROPERTY:ngterm,CXX_MODULE_SET>
  COMMAND_EXPAND_LISTS
  VERBATIM
)

target_compile_definitions(ngterm PRIVATE VERSION=\"${PROJECT_VERSION}\")

target_link_libraries(ngterm std)
