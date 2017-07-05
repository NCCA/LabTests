#include <iostream>
#include <gtest/gtest.h>
#include <SDL.h>
#include <SDL_image.h>
#include <Magick++.h>
#include <algorithm>
#include <memory>
#include <string>
#include <array>

void SDLErrorExit(const std::string& _msg);
void generateImages();
void removeFiles();

int main(int argc, char** argv)
{
  generateImages();
  // Initialize SDL's Video subsystem
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    // Or die on error
    SDLErrorExit("Unable to initialize SDL");
  }

  testing::InitGoogleTest(&argc, argv);

  auto ret=RUN_ALL_TESTS();
  if(argc <=1)
    removeFiles();

  SDL_Quit();
  return ret;
}

SDL_Surface *loadImage(const std::string &_fname)
{
  SDL_Surface *image;
  image=IMG_Load(_fname.c_str());
  if(!image)
  {
    std::cerr<<"Error loading image "<<_fname<<' '<<IMG_GetError()<<'\n';
  }
  return image;
}

TEST(SDL_Image,tga)
{
   EXPECT_TRUE(loadImage("test.tga") !=0);
}


TEST(SDL_Image,bmp)
{
   EXPECT_TRUE(loadImage("test.bmp") !=0);
}

TEST(SDL_Image,pbm)
{
   EXPECT_TRUE(loadImage("test.pbm") !=0);
}

TEST(SDL_Image,pgm)
{
   EXPECT_TRUE(loadImage("test.pgm") !=0);
}

TEST(SDL_Image,ppm)
{
   EXPECT_TRUE(loadImage("test.ppm") !=0);
}

TEST(SDL_Image,xpm)
{
   EXPECT_TRUE(loadImage("test.xpm") !=0);
}

TEST(SDL_Image,pcx)
{
   EXPECT_TRUE(loadImage("test.pcx") !=0);
}

TEST(SDL_Image,gif)
{
   EXPECT_TRUE(loadImage("test.gif") !=0);
}

TEST(SDL_Image,jpg)
{
   EXPECT_TRUE(loadImage("test.jpg") !=0);
}

TEST(SDL_Image,tiff)
{
   EXPECT_TRUE(loadImage("test.tiff") !=0);
}

TEST(SDL_Image,lbm)
{
   EXPECT_TRUE(loadImage("test.lbm") !=0);
}

TEST(SDL_Image,png)
{
   EXPECT_TRUE(loadImage("test.png") !=0);
}

constexpr std::array<const char *, 12> gExtensions={
  {"tga","bmp","pbm","pgm","ppm","xpm","pcx","gif","jpg","tiff","lbm","png"}
};

void generateImages()
{
  constexpr unsigned int           WIDTH     = 800;
  constexpr unsigned int           HEIGHT    = 800;
  constexpr auto                   imageSize = WIDTH * HEIGHT * 3 * sizeof(unsigned char);
  // c++ 11
  std::unique_ptr<unsigned char[]> image( new unsigned char[imageSize]);
  // c++ 14
  //std::unique_ptr<unsigned char[]> image=std::make_unique<unsigned char []>(imageSize);
  // set background colour
  std::for_each(image.get(), image.get() + imageSize, [](unsigned char &n) { n = 255; });
  // or use std::fill
  // std::fill(image.get(), image.get() + imageSize,  255);

  // set pixel as lambda
  auto setPixel = [&image](size_t _x, size_t _y, unsigned char _r, unsigned char _g, unsigned char _b)
  {
    size_t index           = (_y * WIDTH * 3) + _x * 3;
    image.get()[index]     = _r;
    image.get()[index + 1] = _g;
    image.get()[index + 2] = _b;
  };

/*  for (size_t y = 0; y < HEIGHT; ++y)
  {
    for (size_t x = 0; x < WIDTH; ++x)
    {
      if ((y % 20) && (x % 20))
      {
        setPixel(x, y, 255, 0, 0);
      }
      else
      {
        setPixel(x, y, 255, 255, 255);
      }
    }
  }
*/
  Magick::InitializeMagick("./");

  for(auto ext : gExtensions)
  {
    std::string fname("test.");
    fname+=ext;
    Magick::Image output(WIDTH, HEIGHT, "RGB", Magick::CharPixel, image.get());
    output.depth(16);
    output.write(fname.c_str());
  }
}

void removeFiles()
{
  for(auto ext : gExtensions)
  {
    std::string fname("test.");
    fname+=ext;
    std::remove(fname.c_str());
  }
}

void SDLErrorExit(const std::string& _msg)
{
  std::cerr << _msg << '\n';
  std::cerr << SDL_GetError() << '\n';
  SDL_Quit();
  exit(EXIT_FAILURE);
}

