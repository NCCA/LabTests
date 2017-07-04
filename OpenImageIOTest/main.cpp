#include <iostream>
#include <gtest/gtest.h>
#include <algorithm>
#include <memory>
#include <string>
#include <array>
#include <OpenImageIO/imageio.h>

void generateImages();
void removeFiles();
constexpr  int           WIDTH     = 800;
constexpr  int           HEIGHT    = 800;

int main(int argc, char** argv)
{
  generateImages();

  testing::InitGoogleTest(&argc, argv);

  auto ret=RUN_ALL_TESTS();
  if(argc <=1)
    removeFiles();

  return ret;
}




OpenImageIO::ImageSpec loadImage(const std::string &_fname)
{
  using namespace OpenImageIO;
  std::unique_ptr<ImageInput> in (ImageInput::create (_fname));
  ImageSpec spec;
  in->open (_fname, spec);
  auto xres = spec.width;
  auto yres = spec.height;
  auto channels = spec.depth;
//  std::unique_ptr<unsigned char[]> pixels=std::make_unique<unsigned char []>(xres*yres*channels);
  std::unique_ptr<unsigned char[]> pixels(new unsigned char [xres*yres*channels]);
  in->read_image (TypeDesc::UINT8, pixels.get());
  in->close ();
  return spec;
}

TEST(SDL_Image,tga)
{
 auto spec=loadImage("test.tga");
 EXPECT_EQ(spec.width,WIDTH);
 EXPECT_EQ(spec.height,HEIGHT);
 EXPECT_EQ(spec.depth,3);
}


TEST(SDL_Image,bmp)
{
  auto spec=loadImage("test.bmp");
  EXPECT_EQ(spec.width,WIDTH);
  EXPECT_EQ(spec.height,HEIGHT);
  EXPECT_EQ(spec.depth,3);
}

TEST(SDL_Image,pbm)
{
   auto spec=loadImage("test.pbm");
   EXPECT_EQ(spec.width,WIDTH);
   EXPECT_EQ(spec.height,HEIGHT);
   EXPECT_EQ(spec.depth,3);
}

TEST(SDL_Image,pgm)
{
   auto spec=loadImage("test.pgm");
   EXPECT_EQ(spec.width,WIDTH);
   EXPECT_EQ(spec.height,HEIGHT);
   EXPECT_EQ(spec.depth,3);

}

TEST(SDL_Image,ppm)
{
   auto spec=loadImage("test.ppm");
   EXPECT_EQ(spec.width,WIDTH);
   EXPECT_EQ(spec.height,HEIGHT);
   EXPECT_EQ(spec.depth,3);

}


TEST(SDL_Image,jpg)
{
  auto spec=loadImage("test.jpg");
  EXPECT_EQ(spec.width,WIDTH);
  EXPECT_EQ(spec.height,HEIGHT);
  EXPECT_EQ(spec.depth,3);
}

TEST(SDL_Image,tiff)
{
  auto spec=loadImage("test.tiff");
  EXPECT_EQ(spec.width,WIDTH);
  EXPECT_EQ(spec.height,HEIGHT);
  EXPECT_EQ(spec.depth,3);

}



TEST(SDL_Image,png)
{
  auto spec=loadImage("test.png");
  EXPECT_EQ(spec.width,WIDTH);
  EXPECT_EQ(spec.height,HEIGHT);
  EXPECT_EQ(spec.depth,3);
}

TEST(SDL_Image,exr)
{
  auto spec=loadImage("test.exr");
  EXPECT_EQ(spec.width,WIDTH);
  EXPECT_EQ(spec.height,HEIGHT);
  EXPECT_EQ(spec.depth,3);
}


constexpr std::array<const char *, 9> gExtensions={
  {"tga","bmp","pbm","pgm","ppm","jpg","tiff","png","exr"}
};

void generateImages()
{
  constexpr auto                   imageSize = WIDTH * HEIGHT * 3 * sizeof(unsigned char);
  // c++ 11
  std::unique_ptr<unsigned char[]> image( new unsigned char[imageSize]);
  // c++ 14
  //std::unique_ptr<unsigned char[]> image=std::make_unique<unsigned char []>(imageSize);
  // set background colour
  std::for_each(image.get(), image.get() + imageSize, [](unsigned char& n) { n = 255; });
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

  for (size_t y = 0; y < HEIGHT; ++y)
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


  using namespace OpenImageIO;

  for(auto ext : gExtensions)
  {
    std::string fname("test.");
    fname+=ext;
    const int channels = 3; // RGB
    ImageOutput *out = ImageOutput::create (fname);
    ImageSpec spec (WIDTH, HEIGHT, channels, TypeDesc::UINT8);
    std::cout<<fname<<'\n';
    out->open (fname, spec);
    out->write_image (TypeDesc::UINT8, &image[0]);
    out->close ();
    delete out;

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



