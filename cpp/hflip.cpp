#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <sys/time.h>

#include "libppm.h"

int main(int argc, char *argv[]) {
  
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " in_ppm_file out_ppm_file" << std::endl;
    return 1;
  }
  
  PPM_header img_header;
  
  try {
    
    std::ifstream ifs(argv[1], std::ios::binary);
    if (!ifs) {
      throw std::runtime_error("Cannot open input file");
    }
    PPM_read_header(ifs, img_header);
    
    std::cout << img_header << std::endl; 
    
    RGB_8 *img = new RGB_8[img_header.height * img_header.width];
    PPM_read_rgb_8(ifs, img_header.width, img_header.height, (RGB_8 *) img);

    std::ofstream ofs(argv[2], std::ios::binary);
    if (!ofs) {
      throw std::runtime_error("Cannot open output file");
    }
    PPM_write_header_8(ofs, img_header.width, img_header.height);
    PPM_write_rgb_8(ofs, img_header.width, img_header.height, (RGB_8 *) img);
    
    ifs.close();
    ofs.close();
    
  } catch (std::runtime_error &re) {
    std::cout << re.what() << std::endl;
    return 2;
  }
  return 0;     
}

