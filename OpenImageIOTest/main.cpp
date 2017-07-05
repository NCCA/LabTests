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




void loadImage(const std::string &_fname)
{
  using namespace OpenImageIO;
  std::unique_ptr<ImageInput> in (ImageInput::create (_fname));
  ImageSpec spec;
  in->open (_fname, spec);
//  std::unique_ptr<unsigned char[]> pixels=std::make_unique<unsigned char []>(xres*yres*channels);
  std::unique_ptr<unsigned char[]> pixels(new unsigned char [spec.width*spec.height*spec.nchannels]);
  EXPECT_EQ(spec.width,WIDTH);
  EXPECT_EQ(spec.height,HEIGHT);
  EXPECT_EQ(spec.nchannels,3);

  in->read_image (TypeDesc::UINT8, pixels.get());
  // test pixels to be honest this is a bit crap but hey
  // use 25 for jpg compression
  EXPECT_NEAR(pixels[0],255,25);
  EXPECT_NEAR(pixels[1],255,25);
  EXPECT_NEAR(pixels[2],255,25);

  size_t index           = (2 * WIDTH * 3) + 2 * 3;
  // red
  EXPECT_NEAR(pixels[index],255,25);
  EXPECT_NEAR(pixels[index+1],0,25);
  EXPECT_NEAR(pixels[index+2],0,25);

  in->close ();


}

TEST(OIIO_Image,tga)
{
 loadImage("test.tga");
}


TEST(OIIO_Image,bmp)
{
  loadImage("test.bmp");
}

TEST(OIIO_Image,pbm)
{
  loadImage("test.pbm");
}

TEST(OIIO_Image,pgm)
{
  loadImage("test.pgm");
}

TEST(OIIO_Image,ppm)
{
  loadImage("test.ppm");
}


TEST(OIIO_Image,jpg)
{
  loadImage("test.jpg");
}

TEST(OIIO_Image,tiff)
{
  loadImage("test.tiff");
}



TEST(OIIO_Image,png)
{
  loadImage("test.png");
}

TEST(OIIO_Image,exr)
{
 loadImage("test.exr");
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



