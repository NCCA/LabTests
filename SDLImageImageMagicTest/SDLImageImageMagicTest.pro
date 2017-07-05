# This specifies the exe name
TARGET=SDLImageImageMagicTest
# where to put the .o files
OBJECTS_DIR=obj
# core Qt Libs to use add more here if needed.
QT-=gui opengl core

CONFIG-=app_bundle
# Auto include all .cpp files in the project src directory (can specifiy individually if required)
SOURCES+= $$PWD/main.cpp
INCLUDEPATH+=/usr/local/include
CONFIG+=c++11
# same for the .h files

DEPENDPATH+=$$PWD
# where our exe is going to live (root of project)
DESTDIR=./
# were are going to default to a console app
CONFIG += console
LIBS+= -L/usr/local/lib -lgtest

# this demo uses SDL so add the paths using the sdl2-config tool
QMAKE_CXXFLAGS+=$$system(sdl2-config  --cflags)
message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)

LIBS+=$$system(sdl2-config  --libs)
LIBS += -l SDL2_image
message(output from sdl2-config --libs added to LIB=$$LIBS)

QMAKE_CXXFLAGS+=$$system(Magick++-config --cppflags )
LIBS+=$$system(Magick++-config --ldflags --libs )

#macx:QMAKE_CXXFLAGS+=-DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16 -I/usr/local/include/ImageMagick-6
#macx:LIBS+= -L/usr/local/lib -lMagick++-6.Q16 -lMagickWand-6.Q16 -lMagickCore-6.Q16
