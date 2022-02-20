#include <stdio.h>
#include "WebpWriter.h"

int main(void) {
    WebpWriter web(200, 100);//宽200，高100 像素的图片

    printf("webp version : %06x\n", web.v());
    
    web.write("111.webp");//输出文件

    printf("output size : %d\n", web.getoutsize());//输出文件的大小，以字节为单位（注意必须在输出文件后调用）

}