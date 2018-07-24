#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <sys/time.h>
#include <omp.h>

#include "libppm.h"

int main(int argc, char *argv[]) {
  
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " in_ppm_file out_ppm_file thread_count" << std::endl;
    return 1;
  }
  
  PPM_header img_header;
  std::ifstream ifs;
  std::ofstream ofs;

  int thread_count = std::atoi(argv[3]);
  
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
   
  RGB_8 *img = new RGB_8[img_header.height * img_header.width];
  RGB_8 *flip = new RGB_8[img_header.height * img_header.width];
  PPM_read_rgb_8(ifs, img_header.width, img_header.height, (RGB_8 *) img);

  #pragma omp parallel num_threads(thread_count)
  {
      #pragma omp parallel for
      for (int h = 0; h < img_header.height; h++) {
          for (int w = 0; w < img_header.width; w++) {
              flip[h * img_header.width + (img_header.width - w)] = img[h * img_header.width + w];
          }
      }
  }

  PPM_write_header_8(ofs, img_header.width, img_header.height);
  PPM_write_rgb_8(ofs, img_header.width, img_header.height, (RGB_8 *) flip);

  ifs.close();
  ofs.close();
  return 0;     
}

