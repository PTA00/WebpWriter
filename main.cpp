#include <stdio.h>
#include "WebpWriter.h"

int main(void) {
    WebpWriter web(200, 100);//��200����100 ���ص�ͼƬ

    printf("webp version : %06x\n", web.v());
    
    web.write("111.webp");//����ļ�

    printf("output size : %d\n", web.getoutsize());//����ļ��Ĵ�С�����ֽ�Ϊ��λ��ע�����������ļ�����ã�

}