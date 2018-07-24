#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <sys/time.h>
#include <omp.h>

#include "libppm.h"

int thread_count;

void flipHorizontal(PPM_header&, RGB_8*, RGB_8*, int, int);
void toGrayscale(PPM_header&, RGB_8*, int, int);

int main(int argc, char *argv[]) {
  
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " in_ppm_file out_ppm_file thread_count" << std::endl;
    return 1;
  }
  
  PPM_header img_header;
  std::ifstream ifs;
  std::ofstream ofs;

  thread_count = std::atoi(argv[3]);
  
  try {
    ifs.open(argv[1], std::ios::binary);
    if (!ifs) {
      throw std::runtime_error("Cannot open input file");
    }
    PPM_read_header(ifs, img_header);
    
    std::cout << img_header << std::endl; 
  } catch (std::runtime_error &re) {
    std::cout << re.what() << std::endl;
    return 2;
  }

  try {
    ofs.open(argv[2], std::ios::binary);
    if (!ofs) {
      throw std::runtime_error("Cannot open output file");
    }
  } catch (std::runtime_error &re) {
    std::cout << re.what() << std::endl;
    return 2;
  }
   
  RGB_8* img = new RGB_8[img_header.height * img_header.width];
  RGB_8* out = new RGB_8[img_header.height * img_header.width];
  PPM_read_rgb_8(ifs, img_header.width, img_header.height, (RGB_8 *) img);

  flipHorizontal(img_header, img, out, img_header.width, img_header.height);
  toGrayscale(img_header, out, img_header.width, img_header.height);

  PPM_write_header_8(ofs, img_header.width, img_header.height);
  PPM_write_rgb_8(ofs, img_header.width, img_header.height, (RGB_8 *) out);

  ifs.close();
  ofs.close();
  return 0;     
}

void flipHorizontal(PPM_header& img_header, RGB_8 *img, RGB_8 *out, int width, int height) {
  #pragma omp parallel num_threads(thread_count)
  {
      #pragma omp parallel for
      for (int h = 0; h < img_header.height; h++) {
          for (int w = 0; w < img_header.width; w++) {
              out[h * img_header.width + (img_header.width - w)] = img[h * img_header.width + w];
          }
      }
  }
}

void toGrayscale(PPM_header& img_header, RGB_8 *img, int width, int height) {
  #pragma omp parallel num_threads(thread_count)
  {
      #pragma omp parallel for
      for (int h = 0; h < img_header.height; h++) {
          for (int w = 0; w < img_header.width; w++) {
              RGB_8 pixel = img[h * img_header.width + w];
              uint8_t value = pixel.r * 0.21 + pixel.g * 0.72 + pixel.b * 0.07;
              pixel.r = value;
              pixel.g = value;
              pixel.b = value;
              img[h * img_header.width + w] = pixel;
          }
      }
  }
}
