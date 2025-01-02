#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include<iostream>
#include<vector>
#include "./stb/stb_image.h"
#include "./stb/stb_image_write.h"

struct RGB{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class Image {
public:
    Image() {
        width = 500;
        height = 400;
        channels = 3;
        data = std::vector<std::vector<RGB>>(height,std::vector<RGB>(width,{0xff,0xff,0xff}));
    }

    Image(const char* filename){
        rawData = stbi_load(filename, &width, &height, &channels, 3);
        if (rawData == nullptr) {
            throw std::runtime_error("Image loading failed");
        }
        data = convertTo2D(rawData, width, height);
    }

    void saveToPNG(const char* filename) {
        std::vector<unsigned char> imageFlat;
        imageFlat.reserve(width * height * 3); 

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                const RGB& color = data[i][j];
                imageFlat.push_back(color.r);  
                imageFlat.push_back(color.g); 
                imageFlat.push_back(color.b);  
            }
        }

        if (stbi_write_png(filename, width, height, 3, imageFlat.data(), width * 3)) {
            std::cout << "Image saved successfully to " << filename << std::endl;
        } else {
            std::cout << "Failed to save image!" << std::endl;
        }
    }

    std::vector<std::vector<RGB>>& getData() {
        return data;
    }

    unsigned char* getRawData() {
        return rawData;
    }

    int& getHeight() {
        return height;
    }

    int& getWidth() {
        return width;
    }

    ~Image() {
        if (rawData != nullptr) {
            stbi_image_free(rawData);
        }
    }

private:
    std::vector<std::vector<RGB>> data;
    unsigned char* rawData = nullptr;
    int width;
    int height;
    int channels;

    std::vector<std::vector<RGB>> convertTo2D(const unsigned char* imageData, int width, int height) {
        std::vector<std::vector<RGB>> output;
        int length = width*height*3;
        RGB color;

        for(int i=0;i<height;++i){
            std::vector<RGB> row;
            for(int j=0; j<width*3;j+=3){
                color.r = imageData[i*width*3+j+0];
                color.g = imageData[i*width*3+j+1];
                color.b = imageData[i*width*3+j+2];
                row.emplace_back(color);
            }
            output.emplace_back(row);
        }

        return output;
    }
};

void convertToColorJet(std::vector<std::vector<RGB>>& data, int& width, int& height) {
    std::vector<RGB> colormap;
    for (int i = 0; i < 256; i++) {
        RGB color;
        if (i < 85) { // Low intensities
            color.r = 255 * i / 85; 
            color.g = 0;
            color.b = 0;
        } else if (i < 170) { // Medium intensities
            color.r = 0;
            color.g = 255 * (i - 85) / 85;
            color.b = 0;
        } else { // High intensities
            color.r = 0;
            color.g = 0;
            color.b = 255 * (i - 170) / 85;
        }
        colormap.emplace_back(color);
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            RGB& color = data[i][j];
            float gray = color.r * 0.2989f + color.g * 0.5870f + color.b * 0.1140f;
            int intensity = static_cast<int>(std::round(gray));
            color.r = colormap[intensity].r;
            color.g = colormap[intensity].g;
            color.b = colormap[intensity].b;
        }
    }
}

int main(){
    Image image("rose-gray.png");
    convertToColorJet(image.getData(), image.getWidth(), image.getHeight());
    image.saveToPNG("rose-gray-jet.png");
    convertToColorJet(image.getData(), image.getWidth(), image.getHeight());
    image.saveToPNG("rose-gray-jet.png");
    return 0;
}