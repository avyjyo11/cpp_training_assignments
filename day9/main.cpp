

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

struct Coordinate {
    int x;
    int y;
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw(std::vector<std::vector<RGB>>& input) = 0;

protected:
    int width;
    int height;
    RGB stroke;
    RGB fill;
    Coordinate xy;
};

class Rectangle: public Shape {
public:
    Rectangle(int x, int y, int width, int height, RGB stroke, RGB fill) {
        this->xy = {x, y};
        this->width = width;
        this->height = height;
        this->stroke = stroke;
        this->fill = fill;
    }

    void draw(std::vector<std::vector<RGB>>& input) override {
        int x = xy.x;
        int y = xy.y;
        for(int i=x;i<x+width;++i){
            input[y][i]= stroke;
            input[y+height][i]= stroke;
        }
        for(int i=y;i<y+height;++i){
            input[i][x] = stroke;
            input[i][x+width] = stroke;
        }
        for(int i=x+1; i<x+width;++i){
            for(int j=y+1;j<y+height;++j){
                input[j][i] = fill;
            }
        }
    }
};

class Polygon: public Shape {
public:
    Polygon(int centerX, int centerY, int radius, int sides, RGB stroke, RGB fill): centerX(centerX), centerY(centerY), radius(radius), sides(sides) {
        this->stroke = stroke;
        this->fill = fill;
        if (sides < 3) {
            throw std::invalid_argument("A polygon must have at least 3 sides.");
        }
        calculateVertices();
    }

    void draw(std::vector<std::vector<RGB>>& input) override {
        drawEdges(input);
        fillPolygon(input);
    }

private:
    int centerX;
    int centerY;
    int radius;
    int sides; // Number of sides (6 for a hexagon)
    std::vector<Coordinate> vertices;

    void calculateVertices() {
        vertices.clear();
        const double angleStep = 2 * M_PI / sides; // Full circle divided by number of sides

        for (int i = 0; i < sides; ++i) {
            double angle = i * angleStep;
            int x = centerX + static_cast<int>(radius * cos(angle));
            int y = centerY + static_cast<int>(radius * sin(angle));
            vertices.push_back({x, y});
        }
    }

    void drawEdges(std::vector<std::vector<RGB>>& input) {
        for (size_t i = 0; i < vertices.size(); ++i) {
            const Coordinate& start = vertices[i];
            const Coordinate& end = vertices[(i + 1) % vertices.size()];
            drawLine(input, start.x, start.y, end.x, end.y, stroke);
        }
    }

    void fillPolygon(std::vector<std::vector<RGB>>& input) {
        // Simple scan-line filling
        int minY = centerY - radius;
        int maxY = centerY + radius;

        for (int y = minY; y <= maxY; ++y) {
            std::vector<int> intersections;

            // Find intersection points for the current scan line
            for (size_t i = 0; i < vertices.size(); ++i) {
                const Coordinate& p1 = vertices[i];
                const Coordinate& p2 = vertices[(i + 1) % vertices.size()];

                if ((p1.y <= y && p2.y > y) || (p2.y <= y && p1.y > y)) {
                    float slope = (p2.x - p1.x) / static_cast<float>(p2.y - p1.y);
                    int intersectX = p1.x + static_cast<int>((y - p1.y) * slope);
                    intersections.push_back(intersectX);
                }
            }

            // Sort intersection points and fill between them
            std::sort(intersections.begin(), intersections.end());
            for (size_t j = 0; j < intersections.size(); j += 2) {
                if (j + 1 < intersections.size()) {
                    int startX = intersections[j];
                    int endX = intersections[j + 1];
                    for (int x = startX; x <= endX; ++x) {
                        input[y][x] = fill;
                    }
                }
            }
        }
    }

    void drawLine(std::vector<std::vector<RGB>>& input, int x1, int y1, int x2, int y2, RGB color) {
        // Bresenham's line algorithm for edge drawing
        int dx = std::abs(x2 - x1), dy = std::abs(y2 - y1);
        int sx = x1 < x2 ? 1 : -1, sy = y1 < y2 ? 1 : -1;
        int err = dx - dy;

        while (true) {
            if (x1 >= 0 && x1 < input[0].size() && y1 >= 0 && y1 < input.size()) {
                input[y1][x1] = color;
            }

            if (x1 == x2 && y1 == y2) break;

            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x1 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y1 += sy;
            }
        }
    }
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


    void draw(Shape& shape) {
        shape.draw(data);
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

void convertToGrayscale(std::vector<std::vector<RGB>>& imageData,int width, int height){
     for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            RGB& color = imageData[i][j];
            float gray = color.r * 0.2989f+color.r * 0.5870f+color.r * 0.1140f;
            color.r = gray;
            color.g = gray;
            color.b = gray;
        }
    }
}

void sobelEdgeDetection(std::vector<std::vector<RGB>>& imageData,int width, int height) {
    const int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    const int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    std::vector<std::vector<RGB>> originalImage = imageData;

    for (int i = 1; i < height - 1; ++i) {
        for (int j = 1; j < width - 1; ++j) {
            float gx = 0.0f;
            float gy = 0.0f;

            for (int k = -1; k <= 1; ++k) {
                for (int l = -1; l <= 1; ++l) {
                    float intensity = originalImage[i + k][j + l].r; 
                    gx += Gx[k + 1][l + 1] * intensity;
                    gy += Gy[k + 1][l + 1] * intensity;
                }
            }

            float gradientMagnitude = std::sqrt(gx * gx + gy * gy);

            gradientMagnitude = std::min(std::max(gradientMagnitude, 0.0f), 255.0f);

            imageData[i][j].r = gradientMagnitude;
            imageData[i][j].g = gradientMagnitude;
            imageData[i][j].b = gradientMagnitude;
        }
    }
}

void rotate90Clockwise(std::vector<std::vector<RGB>>& imageData, int& width, int& height) {
    std::vector<std::vector<RGB>> rotatedData(width, std::vector<RGB>(height));

    // Map pixels from the original image to the rotated image
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            rotatedData[j][height - 1 - i] = imageData[i][j];
        }
    }
    // Swap width and height since the image is rotated
    std::swap(width, height);
    // Update the original image data with the rotated data
    imageData = std::move(rotatedData);
}

int main(){
    Image image("./images/traffic.jpg");
    auto& data = image.getData();

    convertToGrayscale(data, image.getWidth(), image.getHeight());
    sobelEdgeDetection(data, image.getWidth(), image.getHeight());
    image.saveToPNG("test.png");

    rotate90Clockwise(data, image.getWidth(), image.getHeight());
    image.saveToPNG("rotated.png");

    Image image2;
    Rectangle rect(100,100,200,50,{0,0,0},{0xff,0,0});
    image2.draw(rect);
    Polygon hexagon(250, 200, 100, 6, {0, 0, 0}, {0, 255, 0});
    image2.draw(hexagon);
    image2.saveToPNG("test2.png");

    return 0;
}

