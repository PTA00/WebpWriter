#ifndef WEBP_WRITER_H
#define WEBP_WRITER_H

#include "encode.h"

#pragma warning(disable : 4996)//隐藏警告

class WebpWriter
{
public:
    WebpWriter(const int width, const int height);
    ~WebpWriter();
    void set(const int i, const int j, const unsigned char r, const unsigned char g, const unsigned char b);
    void write(const char* filename);
    int v();
    int getoutsize();

private:
    uint8_t(*buffer)[3]; // 0 <= r,g,b < 255 
    uint8_t(*bufferout)[3];
    int nx, ny;
    int outsize;
};

int WebpWriter::v() {
    return WebPGetEncoderVersion();
}

WebpWriter::WebpWriter(const int width, const int height)
{
    nx = width;
    ny = height;

    buffer = new uint8_t[width * height][3];

    // fill buffer with a "nice" cyan [73,175,205] -- eventually a designer should choose this ;)
    for (int i = 0; i < nx * ny; ++i) {
        buffer[i][0] = 73;
        buffer[i][1] = 175;
        buffer[i][2] = 205;
    }
}

WebpWriter::~WebpWriter()
{
    delete[] buffer;
    delete[] bufferout;
}

void WebpWriter::set(const int i, const int j, const unsigned char r, const unsigned char g, const unsigned char b) {
    // recall that for png files, the pixels are ordered from the top left, so modify 
    // this set routine's passed j so that zero is at the bottom left...
    /*buffer[(ny-j-1)*nx+i][0] = r;
    buffer[(ny-j-1)*nx+i][1] = g;
    buffer[(ny-j-1)*nx+i][2] = b;*/

    //现在是左上角原点，笛卡尔y取反
    buffer[j * nx + i][0] = r;
    buffer[j * nx + i][1] = g;
    buffer[j * nx + i][2] = b;
}

void WebpWriter::write(const char* filename) {

    //打开文件流
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        printf("Warning: could not open png file.\n");
        return;
    }
    outsize = WebPEncodeLosslessRGB((const uint8_t*)buffer, nx, ny, nx * 3, (uint8_t**)&bufferout);
    if (!outsize) {
        printf("Error: WebPEncodeLosslessRGB return '0'.\n");
    }

    fwrite(bufferout, 1, outsize, fp);

    fclose(fp);

}

int WebpWriter::getoutsize() {
    return outsize;
}


#endif
//感谢你的参考！
//Thank you for the reference！
