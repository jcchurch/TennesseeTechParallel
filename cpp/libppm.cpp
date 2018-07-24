#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "libppm.h"


void PPM_read_header(std::ifstream &inp, PPM_header &ppm_header) {
	char ppm_magic_1, ppm_magic_2;
	inp >> ppm_magic_1;
	inp >> ppm_magic_2;
	
	if (ppm_magic_1 != PPM_MAGIC_1 || ppm_magic_2 != PPM_MAGIC_2) {
		throw std::runtime_error("File does not begin with PPM magic number");
	}
	
	int width;
	inp >> width;
	ppm_header.width = width;
	int height;
	inp >> height;
	ppm_header.height = height;

	int max_color;
	inp >> max_color;
	ppm_header.max_color = max_color;

	char space;
	//inp >> space;		// finish the header
	inp.read(&space, 1);

	return;
}

std::ostream &operator<<(std::ostream &os, const RGB_8 &rgb) {
	os << (int) rgb.r << " " << (int) rgb.g << " " << (int) rgb.b;
	return os;
}

void PPM_read_rgb_8(std::ifstream &inp, int width, int height, RGB_8 *img) {
  inp.read((char *)img, sizeof(RGB_8)*width*height);
  if (!inp) {
    std::stringstream ss;
    ss << "error: only " << inp.gcount() << " could be read";
    throw std::runtime_error(ss.str());		
  }
  
}

void PPM_write_header_8(std::ofstream &outp, int width, int height) {
  // write the header
  outp << PPM_MAGIC_1 << PPM_MAGIC_2 << (char) 10 << width << (char) 10 
       << height << (char) 10 << 255 << (char) 10;
}

void PPM_write_rgb_8(std::ofstream &outp, int width, int height, RGB_8 *img) {	
	// write the image
	outp.write((char *)img, sizeof(RGB_8) * width * height);
	if (!outp) {
	  std::stringstream ss;
	  ss << "error: only " << outp.tellp() << " could be written";
	  throw std::runtime_error(ss.str());		
	}

}

std::ostream &operator<<(std::ostream &os, const PPM_header &header) {
	os << header.width << " " << header.height << " " << header.max_color;
	return os;
}

