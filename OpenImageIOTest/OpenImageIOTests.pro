TARGET=OpenImageIOTests
SOURCES+=main.cpp
CONFIG+=c++14
INCLUDEPATH+=/usr/local/include
# for Catch Unit Testing Framework
INCLUDEPATH+=../catch/
LIBS+= -L/usr/local/lib -lOpenImageIO -lOpenImageIO_Util -lPtex
CONFIG -=app_bundle
