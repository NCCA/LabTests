# We will always try to use a version > 3.1 if avaliable
cmake_minimum_required(VERSION 3.12)

#-------------------------------------------------------------------------------------------
# I'm going to use vcpk in most cases for our install of 3rd party libs
# this is going to check the environment variable for CMAKE_TOOLCHAIN_FILE and this must point to where
# vcpkg.cmake is in the University this is set in your .bash_profile to
# export CMAKE_TOOLCHAIN_FILE=/public/devel/2020/vcpkg/scripts/buildsystems/vcpkg.cmake
#-------------------------------------------------------------------------------------------
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

# name of the project It is best to use something different from the exe name
project(Image_build)
# Here we set the C++ standard to use

find_package(OpenImageIO CONFIG REQUIRED)
find_package(freetype CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)


# Now we add our target executable and the file it is built from.
add_executable(Image)
target_sources(Image PRIVATE main.cpp )
target_link_libraries(Image PRIVATE OpenImageIO::OpenImageIO)

