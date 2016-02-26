#include <stdio.h>

int height, width;

/* 坐标结构体 */
typedef struct point{
    double x, y;
}point;

int main()
{
    double line_width;    //线的宽度
    int count_of_points;  //顶点的数量
    char bmpHead[54];     //用于存文件头的缓存
    FILE *readin;         //用于读入文件
    FILE *out;            //用于输出bmp文件
    int i;                //循环变量
    point p[100];         //用于存放顶点的数组
    int x_min, x_max;     //读入的顶点x坐标的最小最大值
    int y_min, y_max;     //读入的顶点y坐标的最小最大值

    int bfSize, biWidth, biHeight, biSizeImage;  //位图信息头部分需要计算的量


    out    = fopen("out.bmp", "w");    //打开要生成的位图文件
    readin = fopen("readin.txt", "r"); //打开要读入数据的文件

    /* 读入数据 */
    fscanf(readin, "线宽     :  %lf\n", &line_width);        //读入线宽
    fscanf(readin, "点的数量 :  %d\n",  &count_of_points);   //读入点的数量
    fscanf(readin, "顶点     :\n");                          //准备读入顶点坐标

    /* 读入顶点坐标 */
    for (i = 0; i < count_of_points; ++i) {
        fscanf(readin, "(%lf, %lf)\n", &(p[i].x), &(p[i].y));
    }

    /* 初始化坐标最大最小值 */
    x_min = (int)p[0].x;
    x_max = (int)p[0].x;
    y_min = (int)p[0].y;
    y_max = (int)p[0].y;

    /* 遍历一下所有顶点，找出所有顶点中x, y坐标的最大最小值 */
    for (i = 1; i < count_of_points; ++i) {
        if (p[i].x > x_max) x_max = p[i].x;
        if (p[i].x < x_min) x_min = p[i].x;
        if (p[i].y > y_max) y_max = p[i].y;
        if (p[i].y < y_min) y_min = p[i].y;
    }

    /* 设置画布的大小 */
    height = (y_max - y_min) + line_width * 2;  //设置画布的高度
    width  = (x_max - x_min) + line_width * 2;  //设置画布的宽度
    width  = (width / 4 + 1) * 4;      //当画布的宽度不是4的倍数时,适当调整画布的宽度,使它是4的倍数

    /* 计算文件头中需要填写部分的数据 */
    bfSize      = 54 + 3 * height * width;  //位图文件的大小, 包括信息头和文件部分, 单位字节
    biWidth     = width;                    //图像的宽度
    biHeight    = height;                   //图像的高度
    biSizeImage = width * height * 3;       //图像部分的大小, 单位字节

    /* 设置bfType字段, 位图文件类型, 2字节 */
    bmpHead[0] = 'B';
    bmpHead[1] = 'M';

    /* 位图文件的大小, bfSize字段 4字节 */
    bmpHead[2] = (char)(bfSize % 256);
    bfSize = bfSize / 256;
    bmpHead[3] = (char)(bfSize % 256);
    bfSize = bfSize / 256;
    bmpHead[4] = (char)(bfSize % 256);
    bfSize = bfSize / 256;
    bmpHead[5] = (char)(bfSize % 256);
    bfSize = bfSize / 256;

    /* bfReserved1字段 2字节 */
    bmpHead[6] = (char)0;
    bmpHead[7] = (char)0;

    /* bfReserved2字段 2字节 */
    bmpHead[8] = (char)0;
    bmpHead[9] = (char)0;

    /* bfOffBits字段 4字节 */
    bmpHead[10] = (char)54;
    bmpHead[11] = (char)0;
    bmpHead[12] = (char)0;
    bmpHead[13] = (char)0;

    /* biSize字段, 位图描述信息块的大小,4字节 */
    bmpHead[14] = (char)40;
    bmpHead[15] = (char)0;
    bmpHead[16] = (char)0;
    bmpHead[17] = (char)0;

    /* biWidth字段, 图像的宽度, 4字节 */
    bmpHead[18] = (char)(biWidth % 256);
    biWidth = biWidth / 256;
    bmpHead[19] = (char)(biWidth % 256);
    biWidth = biWidth / 256;
    bmpHead[20] = (char)(biWidth % 256);
    biWidth = biWidth / 256;
    bmpHead[21] = (char)(biWidth % 256);
    biWidth = biWidth / 256;

    /* biHeight字段, 图像的高度, 4字节 */
    bmpHead[22] = (char)(biHeight % 256);
    biHeight = biHeight / 256;
    bmpHead[23] = (char)(biHeight % 256);
    biHeight = biHeight / 256;
    bmpHead[24] = (char)(biHeight % 256);
    biHeight = biHeight / 256;
    bmpHead[25] = (char)(biHeight % 256);
    biHeight = biHeight / 256;

    /* biPlanes字段, 目标设备级别, 设置为1, 2字节 */
    bmpHead[26] = (char)1;
    bmpHead[27] = (char)0;

    /* biBitCount字段, 每个像素所需要的位数, 本程序中设置为24, 2字节 */
    bmpHead[28] = (char)24;
    bmpHead[29] = (char)0;

    /* biCompression字段, 压缩类型, 本程序不压缩, 设置为0, 4字节 */
    bmpHead[30] = (char)0;
    bmpHead[31] = (char)0;
    bmpHead[32] = (char)0;
    bmpHead[33] = (char)0;

    /* biSizeImage字段, 位图图像部分的大小, 4字节 */
    bmpHead[34] = (char)(biSizeImage % 256);
    biSizeImage = biSizeImage / 256;
    bmpHead[35] = (char)(biSizeImage % 256);
    biSizeImage = biSizeImage / 256;
    bmpHead[36] = (char)(biSizeImage % 256);
    biSizeImage = biSizeImage / 256;
    bmpHead[37] = (char)(biSizeImage % 256);
    biSizeImage = biSizeImage / 256;

    /* biXpelsPerMeter字段, 位图水平分辨率, 设置为0, 4字节 */
    bmpHead[38] = (char)0;
    bmpHead[39] = (char)0;
    bmpHead[40] = (char)0;
    bmpHead[41] = (char)0;

    /* biYpelsPerMeter字段, 位图垂直分辨率, 设置为0, 4字节 */
    bmpHead[42] = (char)0;
    bmpHead[43] = (char)0;
    bmpHead[44] = (char)0;
    bmpHead[45] = (char)0;

    /* biClrUsed字段, 位图实际使用的颜色表中的颜色数, 在24位图中不需要, 设置为0, 4字节 */
    bmpHead[46] = (char)0;
    bmpHead[47] = (char)0;
    bmpHead[48] = (char)0;
    bmpHead[49] = (char)0;

    /* biClrImportant字段, 重要颜色数, 设置为0, 4字节 */
    bmpHead[50] = (char)0;
    bmpHead[51] = (char)0;
    bmpHead[52] = (char)0;
    bmpHead[53] = (char)0;

    /* 将文件信息头部分写入到位图文件中 */
    fwrite(bmpHead, 54, 1, out);
    return 0;
}
