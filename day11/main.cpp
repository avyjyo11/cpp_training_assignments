#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include<iostream>
#include<vector>
#include "./stb/stb_image.h"
#include "./stb/stb_image_write.h"

struct RGB {
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

    Image(int&& width, int&& height): width(width), height(height) {
        data = std::vector<std::vector<RGB>>(height,std::vector<RGB>(width,{0xff,0xff,0xff}));
    }

    Image(const char* filename){
        rawData = stbi_load(filename, &width, &height, &channels, 3);
        if (rawData == nullptr) {
            throw std::runtime_error("Image loading failed");
        }
        std::cout << rawData << "\n";

        data = convertTo2D(rawData, width, height);

      // for (auto i : data) {
      //   for (auto j : i) {
      //     std::cout << "j: " << j.r << "," << j.g << "," << j.b << "\n";
      //   }
      // }
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

void fillCanvasWithTiles(Image& tile, Image& canvas) {
  const int GAP = 10;

    int tileWidth = tile.getWidth();
    int tileHeight = tile.getHeight();
    int canvasWidth = canvas.getWidth();
    int canvasHeight = canvas.getHeight();

    auto tileData = tile.getData();
    auto canvasData = canvas.getData();

    int tilesPerRow = (canvasWidth + GAP) / (tileWidth + GAP);
    int tilesPerCol = (canvasHeight + GAP) / (tileHeight + GAP);

    for (int row = 0; row < tilesPerCol; ++row) {
        for (int col = 0; col < tilesPerRow; ++col) {
            int xOffset = col * (tileWidth + GAP);
            int yOffset = row * (tileHeight + GAP);

            for (int y = 0; y < tileHeight; ++y) {
                for (int x = 0; x < tileWidth; ++x) {
                    if ((yOffset + y < canvasHeight) && (xOffset + x < canvasWidth)) {
                        canvasData[yOffset + y][xOffset + x] = tileData[y][x];
                    }
                }
            }
        }
    }
}

int main(){
  Image tile("./tile1.jpg");
  Image canvas(1100, 1100);

  fillCanvasWithTiles(tile, canvas);
  canvas.saveToPNG("output.png");

  return 0;
}

