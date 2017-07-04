TARGET=OpenImageIOTests
SOURCES+=main.cpp
CONFIG+=c++14
INCLUDEPATH+=/usr/local/include
LIBS+= -L/usr/local/lib -lOpenImageIO
CONFIG -=app_bundle
LIBS+= -L/usr/local/lib -lgtest
