# Linux Lab install test suite

The following programs are going to be a test suite for the various libraries we use on the NCCA linux build.

Eventually a single make test will allow for automated testing of everything for now it will have to be done manually whilst I write the code etc.

Will require that gtest is installed on the system, will also use Qt / qmake

These examples will also serve as a reference implementation for the various libs we use. If you look at the .pro or CMakelists.txt files you will see how to include the named libraries for your own projects.

- OpenImageIOTest test writing and reading images using OpenImageIO
- RendermanPython test the renderman python API will need $RMANTREE set in .bashrc
- SDLImageImageMagicTest Test writing images with ImageMagick (C++ API) and read with SDL2_image




