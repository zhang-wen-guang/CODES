#include <stdio.h>
#include <stdint32_t.h>

/* 坐标结构体 */
typedef struct point{
    double x, y;
}point;


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

    bmpHeader.bfType          = 19778;  //BM
    bmpHeader.bfSize          = 100;    //文件大小
    bmpHeader.bfReserved      = 0;      //保留域
    bmpHeader.bfOffBits       = 54;     //图像数据区的起始位置

    bmpHeader.biSize          = 40;     //图像描述信息块的大小
    bmpHeader.biWidth         = 10;       //图像的宽度
    bmpHeader.biHeight        = 10;       //图像的高度
    bmpHeader.biPlanes        = 1;      //图像的plane总数（恒为1）
    bmpHeader.biBitCount      = 24;     //记录像素的位数，很重要的数值，图像的颜色数由该值决定
    bmpHeader.biCompression   = 0;      //数据压缩方式（数值位0：不压缩；1：8位压缩；2：4位压缩）
    bmpHeader.biSizeImage     = ;       //图像区数据的大小
    bmpHeader.biXPelsPerMeter = ;       //水平每米有多少像素，在设备无关位图（.DIB）中，每字节以00H填写
    bmpHeader.biYPelsPerMeter = ;       //垂直每米有多少像素，在设备无关位图（.DIB）中，每字节以00H填写
    bmpHeader.biClrUsed       = ;       //此图像所用的颜色数(本程序采用的是24位位图, 这个值没用)
    bmpHeader.biClrImportant  = ;       //重要颜色（本程序没用）

    fwrite((void *)&bmpHeader, 1, sizeof(BITMAPFILEHEADER), out);
    return 0;
}
