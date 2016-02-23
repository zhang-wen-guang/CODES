#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

/* 颜色结构体 */
typedef struct color {
    int R, G, B;
}color;

int fd;               //bitmap file 要处理的bitmap文件
int width, height;    //image width & height 图像的宽度与高度
int RowSize;          //图像每行像素所占的字节数
color buf[1000][1000];  //用来暂存图像信息的数组
char FillorNot[1000][1000];   //填充时用的数组, 暂时还没使用

/* 浮点数坐标 */
typedef struct vertex {
    double x, y;
}vertex;

/* 定义平面内的直线 */
/* y = k * x + b    */
typedef struct line {
    double k, b;  //k为斜率, b为截距
}line;

/* Set the bfType */
/* 设置bitmap文件头中的bfType变量 */
int SetbfType(char *buf)
{
    lseek(fd, 0, SEEK_SET);
    write(fd, buf, 2);
    return 0;
}

/* Get the bfType */
/* 获取bitmap文件头中的bfType变量 */
int GetbfType(char *buf)
{
    lseek(fd, 0, SEEK_SET);
    read(fd, buf, 2);
    return 0;
}

/* Set the size of the file */
/* 设置bitmap文件的大小 */
int SetbfSize(int size)
{
    lseek(fd, 2, SEEK_SET);
    write(fd, &size, 4);
    return 0;
}

/* Get the size of the file */
/* 得到bitmap文件的大小 */
int GetbfSize()
{
    int size;
    lseek(fd, 2, SEEK_SET);
    read(fd, &size, 4);
    return size;
}

/* Set the bfReserved1 & bfReserved2 */
/* 设置bfReserved1 和 bfReserved2 两个变量的值 */
int SetbfReserved()
{
    int a = 0;
    lseek(fd, 6, SEEK_SET);
    write(fd, &a, 4);
    return 0;
}

/* Set the offset from the beginning to the image info */
/* 设置文件图像信息距离文件开始的偏移量 */
int SetbfOffBits(int bfoffBits)
{
    lseek(fd, 10, SEEK_SET);
    write(fd, &bfoffBits, 4);
    return 0;
}

/* Get the offset from the beginning to the image info */
/* 得到文件图像信息距离文件开始的偏移量 */
int GetbfOffBits()
{
    int bfOffBits;
    lseek(fd, 10, SEEK_SET);
    read(fd, &bfOffBits, 4);
    return bfOffBits;
}

/* Set the size of BITMAPINFOHEADER (biSize) */
/* 设置文件头部分的大小， 也就是biSize变量 */
int SetbiSize(int biSize)
{
    lseek(fd, 14, SEEK_SET);
    write(fd, &biSize, 4);
    return 0;
}

/* Get the size of BITMAPINFOHEADER (biSize) */
/* 得到文件头部分的大小， 也就是biSize变量 */
int GetbiSize()
{
    int biSize;
    lseek(fd, 14, SEEK_SET);
    read(fd, &biSize, 4);
    return biSize;
}

/* Set the size of width & hight (biWidth, biHeight) */
/* 设置图像的宽度和高度， 也就是设置biWidth变量和biHeight变量 */
int SetbiWiHe(int biWidth, int biHeight)
{
    lseek(fd, 18, SEEK_SET);
    write(fd, &biWidth, 4);
    write(fd, &biHeight, 4);
    return 0;
}

/* Get the width of the image */
/* 得到图像的宽度 */
int GetbiWidth()
{
    int biWidth;
    lseek(fd, 18, SEEK_SET);
    read(fd, &biWidth, 4);
    return biWidth;
}

/* Get the Height of the image */
/* 得到图像的高度 */
int GetbiHeight()
{
    int biHeight;
    lseek(fd, 18, SEEK_SET);
    read(fd, &biHeight, 4);
    return biHeight;
}

/* Set the biPlanes, always set to 1 */
/* 设置biPlanes变量， 默认为1 */
int SetbiPlanes()
{
    short a = 1;
    lseek(fd, 26, SEEK_SET);
    write(fd, &a, 2);
    return 0;
}

/* Set bits per pixel (biBitCount) */
/* 设置变量biBitCount */
int SetbiBitCount(short biBitCount)
{
    lseek(fd, 28, SEEK_SET);
    write(fd, &biBitCount, 2);
    return 0;
}

/* Get bits per pixel (biBitCount) */
/* 得到变量biBitCount */
int GetbiBitCount()
{
    int biBitCount;
    lseek(fd, 28, SEEK_SET);
    read(fd, &biBitCount, 2);
    return biBitCount;
}

/* Set the compression type (biCompression) */
/* 设置压缩类型biCompression */
int SetbiCompression(int biCompression)
{
    lseek(fd, 30, SEEK_SET);
    write(fd, &biCompression, 4);
    return 0;
}

/* Set the sizeof the image in bytes  */
/* 设置图像的大小， 以字节为单位 */
int SetbiSizeImage()
{
    int biSize;
    biSize = GetbiBitCount() / 8 * GetbiWidth() * GetbiHeight();
    lseek(fd, 34, SEEK_SET);
    write(fd, &biSize, 4);
    return 0;
}

/* Set pixels per meter, X direction and Y direction */
/* 设置横纵方向上每米的像素数 */
int SetPelsPerMeter(int X, int Y)
{
    lseek(fd, 38, SEEK_SET);
    write(fd, &X, 4);
    write(fd, &Y, 4);
    return 0;
}

/* Set the number of colors used */
/* 设置使用的颜色数 */
int SetbiClrUsed(int biClrUsed)
{
    lseek(fd, 46, SEEK_SET);
    write(fd, &biClrUsed, 4);
    return 0;
}

/* Set the number of important colors */
/* 设置重要颜色的数量 */
int SetbiClrImportant(int biClrImportant)
{
    lseek(fd, 50, SEEK_SET);
    write(fd, &biClrImportant, 4);
    return 0;
}

/* 取一个小数的整数部分 */
int ipart(double x)
{
    return (int)x;
}

/* 将一个小数向上取整    */
/* 例如 myround(3.4) = 4 */
int myround(double x)
{
    return ipart(x + 0.5);
}

/* 返回一个小数的小数部分  */
/* 例如 fpart(4.23) = 0.23 */
double fpart(double x)
{
    return (x - (int)x);
}

/* 返回一个小数距离下一个整数的距离   */
/* 例如 rfpart(4.6) = 5.0 - 4.6 = 0.4 */
double rfpart(double x)
{
    return (int)x + 1.0 - x;
}

/* 将(x, y)这一点的颜色设置为(R, G, B) */
void plot(int x, int y, char R, char G, char B)
{
    buf[x][y].R = (unsigned char)R;
    buf[x][y].G = (unsigned char)G;
    buf[x][y].B = (unsigned char)B;
}

/* 将内存中的数据写入文件                        */
/* 参数说明:                                     */
/* offset 为图像信息部分距离文件开始部分的偏移量 */
/* width  为图像的宽度                           */
/* height 为图像的高度                           */
void dump(int offset, int width, int height) {
    int i, j;
    for (i = 0; i < height; ++i) {
        lseek(fd, offset + i * RowSize, SEEK_SET);
        for (j = 0; j < width; ++j) {
            write(fd, &(buf[j][i].B), 1);
            write(fd, &(buf[j][i].G), 1);
            write(fd, &(buf[j][i].R), 1);
        }
    }
}

/* 获取(x, y)这一点的颜色 */
color getcolor(int x, int y)
{
    color cl;

    cl.R = buf[x][y].R;
    cl.G = buf[x][y].G;
    cl.B = buf[x][y].B;
    return cl;
}

/* 交换两个double型变量的值  */
/* 例如 a = 1.2, b = 3.4     */
/* 执行 swapdouble(&a, &b)后 */
/* a = 3.4, b = 1.2          */
void swapdouble(double *a, double *b)
{
    double tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

/* 交换两个int型变量的值    */
void swapint(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

/* 此函数用于画直线边缘时, 根据直线边缘与像素相交的部分的面积来画这个像素点*/
/* 根据像素内的面积画某个像素                                              */
/* 同时更新边界信息                                                        */
/* 参数说明:                                                               */
/* (x, y)为要画点的坐标                                                    */
/* area 为这一像素点被覆盖的面积                                           */
/* cl 为要画直线的颜色                                                     */
/* pos 用于制定画上边缘还是下边缘 pos == 1 时为下边缘, pos == -1 时为上边缘*/
/* uplow 数组用来保存直线的上下边界信息, 在后面对直线填充时使用            */
void plot_area(int x, int y, double area, color cl, int pos, int uplow[])
{
    int r, g, b;          //这里的r, g, b是通过面积计算的结果的颜色;
    color cl2, cur;       //cl2
    double area2;

    cur = getcolor(x, y);

    if (pos == 1) area = 1.0 - area;

    /* 更新边界信息 */
    if (pos == -1 && y < uplow[x]) uplow[x] = y;
    if (pos == 1 && y > uplow[x]) uplow[x] = y;

    /* 处理线宽小于一个像素的情况 */
    if (pos == 1) {
        cl2 = getcolor(x, y);
        if (cl2.R != 255) {
            area2 = (cl2.R - 255.0) / (cl.R - 255.0);
            area = area + area2 - 1.0;
        } else if (cl2.G != 255) {
            area2 = (cl2.G - 255.0) / (cl.G - 255.0);
            area = area + area2 - 1.0;
        } else if (cl2.B != 255) {
            area2 = (cl2.B - 255.0) / (cl.B - 255.0);
            area = area + area2 - 1.0;
        }
    }

    r = area * cl.R + (1.0 - area) * 255;
    g = area * cl.G + (1.0 - area) * 255;
    b = area * cl.B + (1.0 - area) * 255;
    if (255 == cur.R && 255 == cur.G && 255 == cur.B) {
        plot(x, y, r, g, b);
    }
}

/* 交换两个坐标 */
void swapvertex(vertex *v1, vertex *v2)
{
    swapdouble(&(v1->x), &(v2->x));
    swapdouble(&(v1->y), &(v2->y));
}

/* 计算两点间的斜率 */
double slope(vertex s, vertex e)
{
    return (e.y - s.y) / (e.x - s.x);
}

/* 根据一个点周围的8个点的颜色的均值画这个点 */
void plotaround(int x, int y)
{

    int i, j;
    int tmp;
    int r, g, b;
    color cl;

    r = 0;
    g = 0;
    b = 0;

    /* 取出周围8个点的颜色 */
    for (i = -1; i < 2; ++i) {
        for (j = -1; j < 2; ++j) {
            if ((i != 0) || (j != 0)) {
                cl = getcolor(x + i, y + j);
                r += cl.R;
                g += cl.G;
                b += cl.B;
            }
        }
    }

    /* 计算出这个点的颜色 */
    r = r / 8;
    g = g / 8;
    b = b / 8;

    plot(x, y, r, g, b);
}

void soft(int width, int height) {
	int i, j;
    for (i = 1; i < width - 1; ++i) {
        for (j = 1; j < height - 1; ++j) {
            plotaround(i, j);
        }
    }
}

/* initialize the palette          */
/* 初始化画板， 将画板初始化为白色 */
int init(int width, int height)
{
    int a = 0;
    int i, j;

    for (i = 0; i < width; ++i) {
        for (j = 0; j < height; ++j) {
            plot(i, j, 255, 255, 255);
        }
    }
    return 0;
}

/* draw a line using Bresenham         */
/* 利用Bresenham算法画线               */
/* 只支持线宽为1的直线, 且无抗锯齿效果 */
void Bresenham(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int p = (2 * dy) - dx;
    int dobDy = 2 * dy;
    int dobD = 2 * (dy - dx);
    int PointX, PointY;

    if (x1 > x2) {
        PointX = x2;
        PointY = y2;
        x2 = x1;
    } else {
        PointX = x1;
        PointY = y1;
    }

    plot(PointX, PointY, 0, 0, 0);

    while(PointX < x2) {
        PointX++;
        if (p < 0) {
            p += dobDy;
        } else {
            PointY++;
            p += dobD;
        }
        plot(PointX, PointY, 0, 0, 0);
    }
}

/* draw multiple points, use by drawCircle */
/* 一次性画多个点, 画圆的函数会调用此函数  */
void putdot(x0, y0, x, y)
{
    plot(x0 + x, y0 + y, 255, 0, 0);
    plot(x0 + x, y0 - y, 255, 0, 0);
    plot(x0 - x, y0 + y, 255, 0, 0);
    plot(x0 - x, y0 - y, 255, 0, 0);
    plot(x0 + y, y0 + x, 255, 0, 0);
    plot(x0 - y, y0 + x, 255, 0, 0);
    plot(x0 + y, y0 - x, 255, 0, 0);
    plot(x0 - y, y0 - x, 255, 0, 0);
}

/* draw a circle using Bresenham */
/* 利用Bresenham算法画圆         */
void BresenhamCircle(int x0, int y0, int r)
{
    int x, y;
    float d;

    x = 0;
    y = r;
    d = 5.0 / 4 - r;
    while (x <= y) {
        putdot(x0, y0, x, y);
        if (d < 0)
            d += x * 2.0 + 3;
        else {
            d += 2.0 * (x - y) + 5;
            --y;
        }
        ++x;
    }
}

/* 根据两个顶点计算直线方程 */
line line_formula(vertex v1, vertex v2)
{
    line l;

    l.k = (v2.y - v1.y) / (v2.x - v1.x);
    l.b = v1.y - l.k * v1.x;
    return l;
}

/* 画直线的边缘 */
void draw_range(vertex s, vertex e, int uplow[], int pos, color cl)
{
    double leftH, rightH;
    double k;
    double area;
    double lc, rc;
    line l;
    int i;

    /* 计算直线方程 */
    l = line_formula(s, e);

    uplow[(int)s.x] = (int)s.y;
    uplow[(int)e.x] = (int)e.y;

    k = slope(s, e);

    if ((k > 0 && k < 1) || (k < 0 && k > -1)) {
        if (s.x > e.x) swapvertex(&s, &e);
        for (i = (int)s.x + 1; i < (int)e.x; ++i) {
            lc = l.k * i + l.b;
            rc = l.k * (i + 1) + l.b;
            leftH = fpart(lc);
            rightH = fpart(rc);
            if (ipart(lc) == ipart(rc)) {
                area = 0.5 * (leftH + rightH);
                plot_area(i, (int)lc, area, cl, pos, uplow);
            } else {
                if (k > 0) {
                    area = 1 - 0.5 * (1 - leftH) * (1 - leftH) / k;
                    plot_area(i, (int)lc, area, cl, pos, uplow);
                    area = 0.5 * rightH * rightH / k;
                    plot_area(i, (int)lc + 1, area, cl, pos, uplow);
                } else {
                    area = -0.5 * leftH * leftH / k;
                    plot_area(i, (int)lc, area, cl, pos, uplow);
                    area = 1.0 + 0.5 * (1 - rightH) * (1 - rightH) / k;
                    plot_area(i, (int)lc - 1, area, cl, pos, uplow);
                }
            }
        }
    } else {
        if (s.y > e.y) swapvertex(&s, &e);
        for (i = (int)s.y + 1; i < (int)e.y; ++i) {
            lc = (i - l.b) / l.k;
            rc = (i + 1 - l.b) / l.k;
            leftH = fpart(lc);
            rightH = fpart(rc);
            if (ipart(lc) == ipart(rc)) {
                if (k > 0) {
                    area = 1.0 - 0.5 * (leftH + rightH);
                } else {
                    area = 0.5 * (leftH + rightH);
                }
                plot_area((int)lc, i, area, cl, pos, uplow);
            } else {
                if (k > 0) {
                    area = 0.5 * l.k * (1 - leftH) * (1 - leftH);
                    plot_area((int)lc, i, area, cl, pos, uplow);
                    area = 1 - 0.5 * l.k * rightH * rightH;
                    plot_area((int)lc + 1, i, area, cl, pos, uplow);
                } else {
                    area = -0.5 * l.k * leftH * leftH;
                    plot_area((int)lc, i, area, cl, pos, uplow);
                    area = 1.0 + 0.5 * l.k * (1 - rightH) * (1 - rightH);
                    plot_area((int)lc - 1, i, area, cl, pos, uplow);
                }
            }
        }
    }
}

/* 在某个点的基础上根据偏移量进行移动 */
vertex vertex_move(vertex s, double mx, double my)
{
    s.x += mx;
    s.y += my;
    return s;
}

/* 输入一条直线的两个顶点, 计算它的四个顶点坐标 */
void line_vertexes(vertex s, vertex e, double lwidth, vertex vt[])
{
    double k;
    double deltaX, deltaY;

    if (s.x > e.x) {
        swapvertex(&s, &e);
    }

    k = slope(s, e);
    if (k > 0) {
        deltaY = lwidth / sqrt(1 + k * k) / 2.0;
        deltaX = deltaY * k;

        vt[0] = vertex_move(s, -1.0 * deltaX, deltaY);
        vt[1] = vertex_move(s, deltaX, -1.0 * deltaY);
        vt[2] = vertex_move(e, -1.0 * deltaX, deltaY);
        vt[3] = vertex_move(e, deltaX, -1.0 * deltaY);
    } else {
        deltaY = lwidth / sqrt(1 + k * k) / 2.0;
        deltaX = -1.0 * deltaY * k;

        vt[0] = vertex_move(s, deltaX, deltaY);
        vt[1] = vertex_move(s, -1.0 * deltaX, -1.0 * deltaY);
        vt[2] = vertex_move(e, deltaX, deltaY);
        vt[3] = vertex_move(e, -1.0 * deltaX, -1.0 * deltaY);
    }
}

/* 初始化边界数组 */
void init_boundary(int size, int up[], int down[], int height)
{
    int i;

    for (i = 0; i < size; ++i) {
        up[i] = height;
        down[i] = 0;
    }
}

/* 填充直线内部区域函数 */
void fill(int s, int e, int up[], int down[], color cl)
{
    int i, j;

    for (i = s; i <= e; ++i) {
        for (j = down[i] + 1; j < up[i]; ++j) {
            plot(i, j, cl.R, cl.G, cl.B);
        }
    }
}

/* 经过改良后的画线算法, 对代码进行了优化精简 */
void draw_line(vertex s, vertex e, color cl, double lwidth, int height)
{
    double k;
    vertex vt[4];
    int up[1000], down[1000];
    int i, j;

    /* 初始化边界数组 */
    init_boundary(1000, up, down, height);

    if (s.x > e.x) {
        swapvertex(&s, &e);
    }

    k = slope(s, e);

    line_vertexes(s, e, lwidth, vt);
    if (k < 0) {
        swapvertex(vt + 0, vt + 1);
        swapvertex(vt + 3, vt + 1);
        swapvertex(vt + 3, vt + 2);
    }

    draw_range(vt[0], vt[2], up, -1, cl);
    draw_range(vt[2], vt[3], up, -1, cl);
    draw_range(vt[0], vt[1], down, 1, cl);
    draw_range(vt[1], vt[3], down, 1, cl);

    fill((int)vt[0].x, (int)vt[3].x, up, down, cl);
}

/* 求两直线的交点 */
vertex cross_point(line l1, line l2)
{
    vertex vt;

    vt.x = (l2.b - l1.b) / (l1.k - l2.k);
    vt.y = (l1.k * l2.b - l2.k * l1.b) / (l1.k - l2.k);
    return vt;
}

/* 返回4个点中最小横坐标的值 */
int find_min_x(vertex vt[])
{
    int i;
    double tmp;

    tmp = vt[0].x;
    for (i = 1; i < 4; ++i) {
        if (vt[i].x < tmp) {
            tmp = vt[i].x;
        }
    }
    return (int)tmp;
}

/* 返回4个点中最大横坐标的值 */
int find_max_x(vertex vt[])
{
    int i;
    double tmp;

    tmp = vt[0].x;
    for (i = 1; i < 4; ++i) {
        if (vt[i].x > tmp) {
            tmp = vt[i].x;
        }
    }
    return (int)tmp;
}

/* 给定两点的坐标, 画两点连线经过点 */
/* 所画点均为实点                   */
void draw_real_line(vertex s, vertex e, color cl)
{
    double k;
    double lc, rc;
    line l;
    int i;

    /* 计算直线方程 */
    l = line_formula(s, e);

    k = slope(s, e);

    if ((k > 0 && k < 1) || (k < 0 && k > -1)) {
        if (s.x > e.x) swapvertex(&s, &e);
        for (i = (int)s.x + 1; i < (int)e.x; ++i) {
            lc = l.k * i + l.b;
            rc = l.k * (i + 1) + l.b;
            if (ipart(lc) == ipart(rc)) {
                plot(i, (int)lc, cl.R, cl.G, cl.B);
            } else {
                if (k > 0) {
                    plot(i, (int)lc, cl.R, cl.G, cl.B);
                    plot(i, (int)lc + 1, cl.R, cl.G, cl.B);
                } else {
                    plot(i, (int)lc, cl.R, cl.G, cl.B);
                    plot(i, (int)lc - 1, cl.R, cl.G, cl.B);
                }
            }
        }
    } else {
        if (s.y > e.y) swapvertex(&s, &e);
        for (i = (int)s.y + 1; i < (int)e.y; ++i) {
            lc = (i - l.b) / l.k;
            rc = (i + 1 - l.b) / l.k;
            if (ipart(lc) == ipart(rc)) {
                plot((int)lc, i, cl.R, cl.G, cl.B);
            } else {
                if (k > 0) {
                    plot((int)lc, i, cl.R, cl.G, cl.B);
                    plot((int)lc + 1, i, cl.R, cl.G, cl.B);
                } else {
                    plot((int)lc, i, cl.R, cl.G, cl.B);
                    plot((int)lc - 1, i, cl.R, cl.G, cl.B);
                }
            }
        }
    }
}

/* 折线算法                        */
/* 先实现三个点，两段线的情况      */
/* 数组p[]为顶点序列, p[0]为起始点 */
/* p[1]为中间点, p[2]为终点        */
void broken_line(vertex p[], color cl, double lwidth)
{
    int i, j;
    line u1, d1;               //u1, d1为第一条线上边缘直线的方程
    line u2, d2;
    vertex vt1[4];
    vertex vt2[4];
    vertex cs[2];
    int up[1000], down[1000];
    double k1, k2;

    k1 = slope(p[0], p[1]);
    k2 = slope(p[1], p[2]);

    /* 初始化边界数组 */
    init_boundary(1000, up, down, height);

    /* 求出两条直线的四个顶点 */
    line_vertexes(p[0], p[1], lwidth, vt1);
    line_vertexes(p[1], p[2], lwidth, vt2);

    /* 分别求出两条直线的上下边缘的直线方程 */
    u1 = line_formula(vt1[0], vt1[2]);
    u2 = line_formula(vt2[0], vt2[2]);
    d1 = line_formula(vt1[1], vt1[3]);
    d2 = line_formula(vt2[1], vt2[3]);

    /* 求出两个交点的坐标, 并替换原直线中的点 */
    if ((p[1].x - p[0].x) > 0) {
        if (p[2].x > p[1].x) {
            cs[0] = cross_point(u1, u2);
            cs[1] = cross_point(d1, d2);
            vt1[2] = cs[0];
            vt1[3] = cs[1];
            vt2[0] = cs[0];
            vt2[1] = cs[1];
        } else {
            cs[0] = cross_point(u1, d2);
            cs[1] = cross_point(d1, u2);
            vt1[2] = cs[0];
            vt1[3] = cs[1];
            vt2[2] = cs[1];
            vt2[3] = cs[0];
        }
    } else {
        if (p[2].x > p[1].x) {
            cs[0] = cross_point(u1, d2);
            cs[1] = cross_point(d1, u2);
            vt1[0] = cs[0];
            vt1[1] = cs[1];
            vt2[0] = cs[1];
            vt2[1] = cs[0];
        } else {
            cs[0] = cross_point(u1, u2);
            cs[1] = cross_point(d1, d2);
            vt1[0] = cs[0];
            vt1[1] = cs[1];
            vt2[2] = cs[0];
            vt2[3] = cs[1];
        }
    }

    draw_range(vt1[0], vt1[2], up, -1, cl);
    draw_range(vt1[1], vt1[3], down, 1, cl);
    if (k1 > 0) {
        if (p[1].x > p[0].x) {
            draw_range(vt1[0], vt1[1], down, 1, cl);
            if (vt1[2].x > vt1[3].x) {
                draw_range(vt1[2], vt1[3], down, 1, cl);
            } else {
                draw_range(vt1[2], vt1[3], up, -1, cl);
            }
        } else {
            draw_range(vt1[2], vt1[3], up, -1, cl);
            if (vt1[0].x < vt1[1].x) {
                draw_range(vt1[0], vt1[1], down, 1, cl);
            } else {
                draw_range(vt1[0], vt1[1], up, -1, cl);
            }
        }
    } else {
        if (p[1].x > p[0].x) {
            draw_range(vt1[1], vt1[0], up, -1, cl);
            if (vt1[2].x > vt1[3].x) {
                draw_range(vt1[2], vt1[3], down, 1, cl);
            } else {
                draw_range(vt1[2], vt1[3], up, -1, cl);
            }
        } else {
            draw_range(vt1[2], vt1[3], down, 1, cl);
            if (vt1[0].x < vt1[1].x) {
                draw_range(vt1[0], vt1[1], down, 1, cl);
            } else {
                draw_range(vt1[0], vt1[1], up, -1, cl);
            }
        }
    }

    for (i = find_min_x(vt1); i < find_max_x(vt1); ++i) {
        for (j = down[i] + 1; j < up[i]; ++j) {
            plot(i, j, cl.R, cl.G, cl.B);
        }
    }

    init_boundary(1000, up, down, height);

    draw_range(vt2[0], vt2[2], up, -1, cl);
    draw_range(vt2[1], vt2[3], down, 1, cl);
    if (k2 > 0) {
        if (p[2].x > p[1].x) {
            draw_range(vt2[2], vt2[3], up, -1, cl);
            if (vt2[1].x > vt2[0].x) {
                draw_range(vt2[0], vt2[1], down, 1, cl);
            } else {
                draw_range(vt2[0], vt2[1], up, -1, cl);
            }
        } else {
            draw_range(vt2[0], vt2[1], down, 1, cl);
            if (vt2[3].x > vt2[2].x) {
                draw_range(vt2[2], vt2[3], up, -1, cl);
            } else {
                draw_range(vt2[2], vt2[3], down, 1, cl);
            }
        }
    } else {
        if (p[2].x > p[1].x) {
            draw_range(vt2[2], vt2[3], down, 1, cl);
            if (vt2[1].x > vt2[0].x) {
                draw_range(vt2[0], vt2[1], down, 1, cl);
            } else {
                draw_range(vt2[0], vt2[1], up, -1, cl);
            }
        } else {
            draw_range(vt2[0], vt2[1], up, -1, cl);
            if (vt2[3].x > vt2[2].x) {
                draw_range(vt2[2], vt2[3], up, -1, cl);
            } else {
                draw_range(vt2[2], vt2[3], down, 1, cl);
            }
        }
    }

    for (i = find_min_x(vt2); i < find_max_x(vt2); ++i) {
        for (j = down[i] + 1; j < up[i]; ++j) {
            plot(i, j, cl.R, cl.G, cl.B);
        }
    }

    draw_real_line(cs[0], cs[1], cl);
}

/* 画多段折线 */
void zigzag(vertex p[], int n, color cl, double lwidth) {
    /* p[]为顶点序列, n为顶点个数, cl为颜色, lwidth为线宽 */
    vertex arg[3];
    vertex mid[20];
    int i;
    double k;
    double deltaX, deltaY;

    /* 首先求出各段线段的中点 */
    for (i = 0; i < n - 1; ++i) {
        mid[i].x = (p[i].x + p[i + 1].x) / 2;
        mid[i].y = (p[i].y + p[i + 1].y) / 2;
    }

    /* 利用broken_line函数画出多段折线 */
    arg[0] = p[0];
    arg[1] = p[1];
    arg[2] = mid[1];
    for (i = 1; i < n - 2; ++i) {
        broken_line(arg, cl, lwidth);
        arg[0] = mid[i];
        arg[1] = p[i + 1];
        arg[2] = mid[i + 1];
    }
    arg[0] = mid[n - 3];
    arg[1] = p[n - 2];
    arg[2] = p[n - 1];
    broken_line(arg, cl, lwidth);

    /* 处理结合处 */
    for (i = 1; i < n - 2; ++i) {
        k = slope(p[i], p[i + 1]);
        deltaY = lwidth / sqrt(1 + k * k) / 2.0;
        deltaX = deltaY * k;
        arg[0].x = mid[i].x - deltaX;
        arg[1].x = mid[i].x + deltaX;
        arg[0].y = mid[i].y + deltaY;
        arg[1].y = mid[i].y - deltaY;
        draw_real_line(arg[0], arg[1], cl);
    }
    if (p[n - 1].x == p[0].x && p[n - 1].y == p[0].y) {
        arg[0] = mid[0];
        arg[1] = p[0];
        arg[2] = mid[n - 2];
        broken_line(arg, cl, lwidth);
    }
}

/* qsort()函数用到的cmp函数 */
int cmp(const void *a, const void *b) {
    return ((vertex *)a)->x - ((vertex *)b)->x;
}

/* 任给n个点, 画出以这n个点为顶点的n边形 */
void draw_random(vertex p[], color cl, int n) {
    int i;
    int count_of_up;
    int count_of_down;
    int up[1000], down[1000];
    line l;
    vertex vtup[10], vtdown[10];

    for (i = 0; i < n; ++i) {
        printf("#%d is (%lf, %lf)\n", i, p[i].x, p[i].y);
    }

    qsort(p, n, sizeof(p[0]), cmp);

    printf("\n");
    for (i = 0; i < n; ++i) {
        printf("#%d is (%lf, %lf)\n", i, p[i].x, p[i].y);
    }

    l = line_formula(p[0], p[n - 1]);
    count_of_up = 0;
    count_of_down = 0;
    for (i = 1;i < n - 1; ++i) {
        if (p[i].y > l.k * p[i].x + l.b) {
            vtup[count_of_up++] = p[i];
        } else {
            vtdown[count_of_down++] = p[i];
        }
    }

    for (i = 0; i < count_of_up; ++i) {
        printf("up#%d is (%lf, %lf)\n", i, vtup[i].x, vtup[i].y);
    }

    for (i = 0; i < count_of_down; ++i) {
        printf("down#%d is (%lf, %lf)\n", i, vtdown[i].x, vtdown[i].y);
    }

    init_boundary(1000, up, down, height);

    if (count_of_up > 0) {
        draw_range(p[0], vtup[0], up, -1, cl);
        for (i = 0; i < count_of_up - 1; ++i) {
            draw_range(vtup[i], vtup[i + 1], up, -1, cl);
        }
        draw_range(vtup[count_of_up - 1], p[n - 1], up, -1, cl);
    } else {
        draw_range(p[0], p[n - 1], up, -1, cl);
    }

    if (count_of_down > 0) {
        draw_range(p[0], vtdown[0], down, 1, cl);
        for (i = 0; i < count_of_down - 1; ++i) {
            draw_range(vtdown[i], vtdown[i + 1], down, 1, cl);
        }
        draw_range(vtdown[count_of_down - 1], p[n - 1], down, 1, cl);
    } else {
        draw_range(p[0], p[n - 1], down, 1, cl);
    }
    fill((int)p[0].x, (int)p[n - 1].x, up, down, cl);
}

/* 判断一个点的颜色是不是白色 */
int isWhite(int x, int y) {
    color cl = getcolor(x, y);
    
    if (cl.R == 255 && cl.G == 255 && cl.B == 255) return 1;
    return 0;
}

/* 填充算法 */
void fillInside(color cl, int width) {
    int l, r, flag;
    int c1, c2, lflag, rflag;
    int i, j, k;

    for (j = 0; j < height; ++j) {
        flag = 0;
        lflag = rflag = 0;
        for (i = 1; i < width; ++i) {
            c1 = isWhite(i, j);
            c2 = isWhite(i - 1, j);
            if (c1 != c2) {
                if (c1 > c2) {
                    l = i;
                    lflag = 1;
                } else {
                    r = i;
                    rflag = 1;
                }
                if (lflag == 1 && rflag == 1) {
                    if (r > l) {
                        for (k = l; k < r; ++k) {
                            plot;
                        }
                    } else {

                    }
                }
            }
        }
    }
}

int main()
{
    int i, j, flag;
    int a, b;
    int n;
    int offset;
    vertex start, end;
    vertex vt[100];
    double weight;
    color cl, cl2;
    int up[1000];
    FILE *readin;
    char file_name[1024];

    if ((readin = fopen("readin.txt", "r")) == NULL) {
        printf("Open file 'readin.txt' failed\n");
        exit(1);
    }
    fscanf(readin, "%s\n", file_name);
    printf("Please input the width and height\n");
    fscanf(readin, "(%d %d)", &width, &height);
    printf("%d %d\n", width, height);

    /* 初始化文件 */
    RowSize = (width % 4 == 0) ? width * 3 : 4 * ((int)(3 * width / 4) + 1);
    fd = open((const char *)file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
    SetbiWiHe(width, height);
    SetbfSize(RowSize * height + 54);
    SetbfType("BM");
    SetbfReserved();
    SetbfOffBits(54);
    SetbiSize(40);
    SetbiPlanes();
    SetbiBitCount(24);
    SetbiCompression(0);
    SetbiSizeImage();
    SetPelsPerMeter(0, 0);
    SetbiClrUsed(0);
    SetbiClrImportant(0);
    offset = GetbfOffBits();
    init(width, height);
    /* 初始化文件结束 */

    /* 数据读入 */
    printf("Please input the points\n");
    fscanf(readin, "%d", &n);
    for (i = 0; i < n; ++i) {
        fscanf(readin, " (%lf, %lf)", &(vt[i].x), &(vt[i].y));
    }

    //scanf(" (%lf %lf)", &start.x, &start.y);
    //scanf(" (%lf, %lf)", &end.x, &end.y);
    printf("Please input the width of the line\n");
    fscanf(readin, "%lf", &weight);
    fscanf(readin, " (%d, %d, %d)", &(cl.R), &(cl.G), &(cl.B));
    fscanf(readin, " (%d, %d, %d)", &(cl2.R), &(cl2.G), &(cl2.B));
    fscanf(readin, "%d", &flag);
    /* 数据读入结束 */

    //broken_line(vt, cl, weight);
    zigzag(vt, n, cl, weight);
    //draw_line(vt[0], vt[1], cl, weight);
    //draw_random(vt, cl, n);
    if (1 == flag) soft(width, height);
    //fillInside(cl2, width);
    dump(offset, width, height);
    close(fd);
    return 0;
}
