TARGET=OpenImageIOTests
SOURCES+=main.cpp
CONFIG+=c++14
INCLUDEPATH+=/usr/local/include
# for Catch Unit Testing Framework
INCLUDEPATH+=../catch/
LIBS+= -L/usr/local/lib -lOpenImageIO -lOpenImageIO_Util
CONFIG -=app_bundle
#LIBS+= -L/usr/local/lib -lgtest
#LIBS+=`pkg-config  --static --libs libtiff-4`
#LIBS+=-ltiff -ljpeg -lz
