# This specifies the exe name
TARGET=HelloBullet
# where to put the .o files
OBJECTS_DIR=obj
# core Qt Libs to use add more here if needed.

# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
	cache()
	DEFINES +=QT5BUILD
}
QMAKE_CXXFLAGS+=$$system('pkg-config --cflags bullet')
LIBS+=$$system('pkg-config --libs bullet')
# where to put moc auto generated files
# on a mac we don't create a .app bundle file ( for ease of multiplatform use)
CONFIG-=app_bundle
# Auto include all .cpp files in the project src directory (can specifiy individually if required)
SOURCES+= $$PWD/main.cpp

# and add the include dir into the search path for Qt and make
INCLUDEPATH +=./include
# where our exe is going to live (root of project)
DESTDIR=./

# were are going to default to a console app
CONFIG += console

