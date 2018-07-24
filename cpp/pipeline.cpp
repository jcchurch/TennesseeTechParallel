#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <sys/time.h>
#include <queue>
#include <omp.h>
#include "libppm.h"

std::queue<RGB_8*> pipeline;

void flipHorizontal(PPM_header&);
void toGrayscale(PPM_header&, RGB_8*);
RGB_8* dequeue();
void enqueue(RGB_8*);

int main(int argc, char *argv[]) {
  
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " in_ppm_file out_ppm_file" << std::endl;
      return 1;
    }
  
    PPM_header img_header;
    std::ifstream ifs;
    std::ofstream ofs;

    try {
        ifs.open(argv[1], std::ios::binary);
        if (!ifs) {
            throw std::runtime_error("Cannot open input file");
        }
        PPM_read_header(ifs, img_header);
    
        std::cout << img_header << std::endl; 
    }
    catch (std::runtime_error &re) {
        std::cout << re.what() << std::endl;
        return 2;
    }

    try {
        ofs.open(argv[2], std::ios::binary);
        if (!ofs) {
            throw std::runtime_error("Cannot open output file");
        }
    }
    catch (std::runtime_error &re) {
        std::cout << re.what() << std::endl;
        return 2;
    }
   
    RGB_8* img = new RGB_8[img_header.height * img_header.width];
    PPM_read_rgb_8(ifs, img_header.width, img_header.height, (RGB_8 *) img);

    double start = omp_get_wtime();

    #pragma omp parallel num_threads(2)
    {
        if (omp_get_thread_num() == 0) {
            toGrayscale(img_header, img);
        }
        else {
            flipHorizontal(img_header);
        }	
    }

    double end = omp_get_wtime();

    std::cout << "Elapsed time: " << (end - start) << " seconds." << std::endl;

    PPM_write_header_8(ofs, img_header.width, img_header.height);
    PPM_write_rgb_8(ofs, img_header.width, img_header.height, (RGB_8 *) img);

    ifs.close();
    ofs.close();
    return 0;     
}

void flipHorizontal(PPM_header& img_header) {
    RGB_8* row = dequeue(); 
    while (row != 0) {
       for (int w = 0; w < img_header.width / 2; w++) {
            RGB_8 x = row[w];
            row[w] = row[img_header.width - w];
            row[img_header.width - w] = x;
       }
       row = dequeue(); 
    }
}

void toGrayscale(PPM_header& img_header, RGB_8 *img) {
    for (int h = 0; h < img_header.height; h++) {
        for (int w = 0; w < img_header.width; w++) {
            RGB_8 pixel = img[h * img_header.width + w];
            uint8_t value = pixel.r * 0.21 + pixel.g * 0.72 + pixel.b * 0.07;
            pixel.r = value;
            pixel.g = value;
            pixel.b = value;
            img[h * img_header.width + w] = pixel;
        }
        enqueue(&img[h * img_header.width]);
    }
    enqueue(0);
}

RGB_8* dequeue() {
    RGB_8 *image_row;
    bool keep_checking = true;
    while (keep_checking) {
        #pragma omp critical (pipeline)
        {
            if (!pipeline.empty()) {
                image_row = pipeline.front();
                pipeline.pop();
                keep_checking = false;
            }
        }
        #pragma omp taskyield
    }
    return image_row;
}

void enqueue(RGB_8 *row) {
    #pragma omp critical (pipeline)
    {
        pipeline.push(row);
    }
}
