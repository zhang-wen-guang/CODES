#include <stdio.h>
#include <stdlib.h>


/****************************此部分定义各种结构体*********************************/

/* 坐标结构体 */
typedef struct point{
    double x, y;
}point;

/* 四边形结构体 */
typedef struct quadrangle{
    point p1, p2, p3, p4;
}quadrangle;

/* 颜色结构体 */
typedef struct color{
    unsigned char R, G, B;
}color;

/* 定义方向结构体 */
typedef struct direction{
    double x, y;  //用向量表示方向, (x, y)表示方向向量
}direction;

/* 定义一条直线 */
typedef struct line{
    double k, b;   //k为斜率, b为截距
}line;

/****************************结构体定义部分结束************************************/


/****************************全局变量部分******************************************/

int height, width;    //图像的高度与宽度
char bmpHead[54];     //用于存文件头的缓存
double **pixel_area;  //用于存放像素被图像覆盖的面积
color **buf;          //用于暂存图像信息, 最后统一写入文件
FILE *out;            //用于输出bmp文件
double line_width;    //线的宽度
color  line_color;    //折线的颜色

/****************************全局变量部分结束**************************************/


/****************************定义各种函数******************************************/

/* 交换两个浮点类型的数字 */
void swapDouble(double *a, double *b) {
    double tmp;
    tmp = *a;
    *a  = *b;
    *b  = tmp;
}

/* 交换两个点的坐标 */
void swapPoint(point *p1, point *p2) {
    swapDouble(&(p1->x), &(p2->x));
    swapDouble(&(p1->y), &(p2->y));
}

/* 计算斜率 */
double slope(point s, point e) {
    return (e.y - s.y) / (e.x - s.x);
}

/* 根据两个点得到直线的方程 */
line getLine(point p1, point p2) {
    line l;

    l.k = (p2.y - p1.y) / (p2.x - p1.x);
    l.b = p1.y - l.k * p1.x;
    return l;
}

/* 求两直线交点 */
point crossPoint(line l1, line l2) {
    point res;  //用于存放计算结果

    res.x = (l2.b - l1.b) / (l1.k - l2.k);
    res.y = (l1.k * l2.b - l2.k * l1.b) / (l1.k - l2.k);
    return res;
}

/* 在某个点的基础上进行移动, 并返回移动结果 */
point movePoint(point s, double x, double y) {
    s.x += x;
    s.y += y;
    return s;
}

/* 计算四边形的四个顶点, 先只算直线情况 */
quadrangle getQuadPoints(point s, point e, double line_width) {
    double k;                  //直线的斜率
    double deltaX, deltaY;
    quadrangle res;

    if (s.x > e.x) swapPoint(&s, &e);

    k = slope(s, e);
    if (k > 0) {
        deltaY = line_width / sqrt(1 + k * k) / 2.0;
        deltaX = deltaY * k;

        res.p1 = movePoint(s, -1.0 * deltaX, deltaY);
        res.p2 = movePoint(s, deltaX, -1.0 * deltaY);
        res.p3 = movePoint(e, -1.0 * deltaX, deltaY);
        res.p4 = movePoint(e, deltaX, -1.0 * deltaY);
    } else {
        deltaY = line_width / sqrt(1 + k * k) / 2.0;
        deltaX = -1.0 * deltaY * k;

        res.p1 = movePoint(s, deltaX, deltaY);
        res.p2 = movePoint(s, -1.0 * deltaX, -1.0 * deltaY);
        res.p3 = movePoint(e, deltaX, deltaY);
        res.p4 = movePoint(e, -1.0 * deltaX, -1.0 * deltaY);
    }
    return res;
}

/* 处理线段边缘部分, 将计算得到的面积放入pixel_area数组 */
void lineEdge(point s, point e, char pos) {
    double leftH, rightH;
    double k, b;
    double area;
    double lc, rc;
    line l;
    int i;

    /* 计算要画的边缘的直线方程 */
    l = getLine(s, e);

    /* 此直线的斜率 */
    k = slope(s, e);
    b = l.b;

    if ((k > 0 && k < 1) || (k < 0 && k > -1)) {
        if (s.x > e.x) swapPoint(&s, &e);
        for (i = (int)s.x + 1; i < (int)e.x; ++i) {
            lc = k * i + b;
            rc = k * (i + 1) + b;
        }
    }
}

/* 画折线函数, 先实现两段折线, 多段折线实现在后面 */
void polyLine(point p[], color cl) {
    int i, j;              //循环变量
    line u1, d1, u2, di2;  //两段折线的上下边缘
    quadrangle q1, q2;     //两段线段的四边形
    double k1, k2;         //两段线段的斜率
    point intersection1;   //直线的交点
    point intersection2;

    /* 计算两段线段的斜率 */
    k1 = slope(p[0], p[1]);
    k1 = slope(p[1], p[2]);

    /* 分别计算两段线段的顶点 */
    q1 = getQuadPoints(p[0], p[1], line_width);
    q2 = getQuadPoints(p[1], p[2], line_width);

    /* 求出两段线段上下边缘的直线方程 */
    u1 = getLine(q1.p1, q1.p3);
    u2 = getLine(q2.p1, q2.p3);
    d1 = getLine(q1.p2, q1.p4);
    d2 = getLine(q2.p2, q2.p4);
    
    /* 计算交点坐标, 替换原有坐标 */
    if ((p[1].x - p[0].x) > 0) {
        if (p[2].x > p[1].x) {
            intersection1 = crossPoint(u1, u2);
            intersection2 = crossPoint(d1, d2);
            q1.p3 = intersection1;
            q1.p4 = intersection2;
            q2.p1 = intersection1;
            q2.p2 = intersection2;
        } else {
            intersection1 = crossPoint(u1, d2);
            intersection2 = crossPoint(d1, u2);
            q1.p3 = intersection1;
            q1.p4 = intersection2;
            q2.p3 = intersection2;
            q2.p4 = intersection1;
        }
    } else {
        if (p[2].x > p[1].x) {
            intersection1 = crossPoint(u1, d2);
            intersection2 = crossPoint(d1, u2);
            q1.p1 = intersection1;
            q1.p2 = intersection2;
            q2.p1 = intersection2;
            q2.p2 = intersection1;
        } else {
            intersection1 = crossPoint(u1, u2);
            intersection2 = crossPoint(d1, d2);
            q1.p1 = intersection1;
            q1.p2 = intersection2;
            q2.p3 = intersection1;
            q2.p4 = intersection2;
        }
    }
}

/* 将内存中的数据写入文件 */
void dump() {
    int i;

    fwrite(bmpHead, 54, 1, out);  //将文件头部分写入输出图片

    for (i = 0; i < height; i++) {       //将图像部分信息写入文件
        fwrite(buf[i], sizeof(struct color), width, out);
    }
}

/* 将当前图形信息写入缓存数据区 */
void dumpGraph(color c) {
    int i, j;

    for (i = 0; i < height; i++) {       //将pixel_area中的信息写入到buf中
        for (j = 0; j < width; j++) {
            buf[i][j].R = (unsigned char)(c.R * pixel_area[i][j] + (1.0 - pixel_area[i][j]) * 255);
            buf[i][j].G = (unsigned char)(c.G * pixel_area[i][j] + (1.0 - pixel_area[i][j]) * 255);
            buf[i][j].B = (unsigned char)(c.B * pixel_area[i][j] + (1.0 - pixel_area[i][j]) * 255);
        }
    }
}

/****************************各种函数定义结束**************************************/

int main()
{
    int count_of_points;  //顶点的数量
    FILE *readin;         //用于读入文件
    int i, j;             //循环变量
    point *p;             //用于存放顶点的数组
    int x_min, x_max;     //读入的顶点x坐标的最小最大值
    int y_min, y_max;     //读入的顶点y坐标的最小最大值

    int bfSize, biWidth, biHeight, biSizeImage;  //位图信息头部分需要计算的量


    out    = fopen("out.bmp", "w");    //打开要生成的位图文件
    readin = fopen("readin.txt", "r"); //打开要读入数据的文件

    /* 读入数据 */
    fscanf(readin, "线宽     :  %lf\n", &line_width);        //读入线宽
    fscanf(readin, "点的数量 :  %d\n",  &count_of_points);   //读入点的数量
    fscanf(readin, "顶点     :\n");                          //准备读入顶点坐标

    /* 为各顶点分配内存 */
    p = (point *)malloc(sizeof(struct point) * count_of_points);

    /* 读入顶点坐标 */
    for (i = 0; i < count_of_points; i++) {
        fscanf(readin, "(%lf, %lf)\n", &(p[i].x), &(p[i].y));
    }

    /* 初始化坐标最大最小值 */
    x_min = (int)p[0].x;
    x_max = (int)p[0].x;
    y_min = (int)p[0].y;
    y_max = (int)p[0].y;

    /* 遍历一下所有顶点，找出所有顶点中x, y坐标的最大最小值 */
    for (i = 1; i < count_of_points; i++) {
        if (p[i].x > x_max) x_max = p[i].x;
        if (p[i].x < x_min) x_min = p[i].x;
        if (p[i].y > y_max) y_max = p[i].y;
        if (p[i].y < y_min) y_min = p[i].y;
    }

    /* 设置画布的大小 */
    height = (y_max - y_min) + line_width * 2;  //设置画布的高度
    width  = (x_max - x_min) + line_width * 2;  //设置画布的宽度
    width  = (width / 4 + 1) * 4;      //当画布的宽度不是4的倍数时,适当调整画布的宽度,使它是4的倍数

    /* 为存放像素被图形覆盖部分面积的数组分配空间, 并将其初始化 */
    pixel_area = (double **)malloc(sizeof(double *) * height);    //先给每行分配一个指针,指向每行
    for (i = 0; i < height; i++) {                                //为没一列分配空间
        pixel_area[i] = (double *)malloc(sizeof(double) * width);
    }

    /* 初始化buf, 分配空间并初始化 */
    buf = (color **)malloc(sizeof(color *) * height);
    for (i = 0; i < height; i++) {
        buf[i] = (color *)malloc(sizeof(color) * width);
    }

    for (i = 0; i < height; i++) {           //将画布初始化为空白画布
        for (j = 0; j < width; j++) {
            pixel_area[i][j] = 0.0;
        }
    }

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

    /* 测试部分 */
    color tmp_color;
    tmp_color.R = (unsigned char)255;
    tmp_color.G = (unsigned char)255;
    tmp_color.B = (unsigned char)255;
    dumpGraph(tmp_color);
    /* 测试部分 */
    
    dump();
    return 0;
}
