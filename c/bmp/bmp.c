/*************************************************************************
    > File Name: bmp.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年02月24日 星期三 20时11分56秒
 ************************************************************************/

#include <stdio.h>
#include <stdint32_t.h>

/* 坐标结构体 */
typedef struct point{
    double x, y;
}point;

/* bmp文件头结构体 */
typedef struct tagBITMAPFILEHEADER {
    int16_t bfType;
    int32_t bfSize;
    int16_t bfReserved;
    int32_t bfOffBits;

    int32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    int16_t biPlanes;
    int16_t biBitCount;
    int32_t biCompression;
    int32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    int32_t biClrUsed;
    int32_t biClrImportant;
} BITMAPFILEHEADER;

int32_t main()
{
    char bmpHead[60];
    FILE *readin;  //用于读入文件
    FILE *out;     //用于输出bmp文件

    out = fopen("out.bmp", "w");

    /* 设置bmp文件头部分 */
    BITMAPFILEHEADER bmpHeader;  //

    bmpHeader.bfType          = 19778;
    bmpHeader.bfSize          = 100;
    bmpHeader.bfReserved      = 0;
    bmpHeader.bfOffBits       = 54;

    bmpHeader.biSize          = 40;
    bmpHeader.biWidth         = ;
    bmpHeader.biHeight        = ;
    bmpHeader.biPlanes        = 1;
    bmpHeader.biBitCount      = 24;
    bmpHeader.biCompression   = 0;
    bmpHeader.biSizeImage     = ;
    bmpHeader.biXPelsPerMeter = ;
    bmpHeader.biYPelsPerMeter = ;
    bmpHeader.biClrUsed       = ;
    bmpHeader.biClrImportant  = ;

    fwrite((void *)&bmpHeader, 1, sizeof(BITMAPFILEHEADER), out);
    return 0;
}
