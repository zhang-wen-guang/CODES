#include <stdio.h>
#include <stdlib.h>
#include <math.h>


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
    point s, e;        //s表示起点(start), e表示终点(end)
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

/* 设置一个像素点被图形覆盖的面积 */
void setPixelArea(int x, int y, double area) {
	pixel_area[x][y] = area;
}

/* 从面积数组中取出一个像素点被覆盖的面积 */
double getPixelArea(int x, int y) {
	return pixel_area[x][y];
}

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

/* 求两直线交点, 直接通过解析几何求解出交点的坐标 */
point crossPoint(line l1, line l2) {
    point res;  //用于存放计算结果

    res.x = (l1.e.y * l1.s.x * l2.e.x - l1.e.x * l1.s.y * l2.e.x -  \
             l1.e.y * l1.s.x * l2.s.x + l1.e.x * l1.s.y * l2.s.x -  \
             l1.e.x * l2.e.y * l2.s.x + l1.s.x * l2.e.y * l2.s.x +  \
             l1.e.x * l2.e.x * l2.s.y - l1.s.x * l2.e.x * l2.s.y) / \
             (l1.e.y * l2.e.x - l1.s.y * l2.e.x - l1.e.x * l2.e.y + \
             l1.s.x * l2.e.y - l1.e.y * l2.s.x + l1.s.y * l2.s.x +  \
             l1.e.x * l2.s.y - l1.s.x * l2.s.y);
    res.y = (l1.e.x * l1.s.y * l2.e.y - l1.e.y * l1.s.x * l2.e.y +  \
             l1.e.y * l2.e.y * l2.s.x - l1.s.y * l2.e.y * l2.s.x +  \
             l1.e.y * l1.s.x * l2.s.y - l1.e.x * l1.s.y * l2.s.y -  \
             l1.e.y * l2.e.x * l2.s.y + l1.s.y * l2.e.x * l2.s.y) / \
            (l1.s.y * l2.e.x - l1.e.y * l2.e.x + l1.e.x * l2.e.y -  \
             l1.s.x * l2.e.y + l1.e.y * l2.s.x - l1.s.y * l2.s.x -  \
             l1.e.x * l2.s.y + l1.s.x * l2.s.y);
    return res;
}

/* 在某个点的基础上进行移动, 并返回移动结果 */
point movePoint(point s, double x, double y) {
    s.x += x;
    s.y += y;
    return s;
}

/* 计算四边形的四个顶点, 先只算直线情况 */
/* 对函数进行了修改, 不再使用斜率k      */
quadrangle getQuadPoints(point s, point e, double line_width) {
    quadrangle res;
    double deltaX, deltaY;

    /* 通过解析几何计算出各个顶点相对原来两个点的偏移位置 */
    deltaY = line_width / ((e.y - s.y) * (e.y - s.y) + (e.x - s.x) * (e.x - s.x)) * (e.x - s.x);
    deltaX = line_width / ((e.y - s.y) * (e.y - s.y) + (e.x - s.x) * (e.x - s.x)) * (s.y - e.y);

    res.p1 = movePoint(s, deltaX, deltaY);
    res.p2 = movePoint(s, -1.0 * deltaX, -1.0 * deltaY);
    res.p3 = movePoint(e, deltaX, deltaY);
    res.p4 = movePoint(e, -1.0 * deltaX, -1.0 * deltaY);
    return res;
}

/* 用两个点初始化一条线 */
line getLine(point a, point b) {
    line res;   //结果变量

    res.s.x = a.x;  //将直线的起点赋值为a
    res.s.y = a.y;

    res.e.x = b.x;  //将直线的终点赋值为b
    res.e.y = b.y;
    return res;
}

/* 计算四边形真正的四个顶点, 并替换四边形中原有的顶点 */
void getRealQuadpoints(quadrangle *a, quadrangle *b) {
    line a1, a2;      //a四边形的两条边缘线
    line b1, b2;      //b四边形的两条边缘线
    point cross1, cross2;  //求出来的两个交点

    a1 = getLine(a->p1, a->p3);  //得到第一个四边行的两条线
    a2 = getLine(a->p2, a->p4);

    b1 = getLine(b->p1, b->p3);  //得到第一个四边行的两条线
    b2 = getLine(b->p2, b->p4);

    /* 求出两个交点, 并替换原有的点 */
    cross1 = crossPoint(a1, b1);   //求两个交点
    cross2 = crossPoint(a2, b2);

    /* 替换原有点 */
    a->p3.x = cross1.x;  //替换第一个四边形中的顶点
    a->p3.y = cross1.y;
    
    a->p4.x = cross2.x;
    a->p4.y = cross2.y;

    b->p1.x = cross1.x;  //替换第二个四边形中的顶点
    b->p1.y = cross1.y;
    
    b->p2.x = cross2.x;
	b->p2.y = cross2.y;
}


/* 求绝对值的函数 */
int abs(int a) {
    return (a > 0 ? a : -1 * a);
}

/* 将起点到终点的线段经过的所有点都画出来 */
void paintLine(line l) {
	int x1, y1, x2, y2; //(x1, y1)为起点, (x2, y2)为终点
	int x, y;           //(x, y)标记画线时要画的点
	int p;              //p用来决定要画点的位置
	int temp;           //用于交换的临时变量
	int i;              //循环变量
	int interchange;    //用于记录横纵坐标是否交换过
    int dx, dy;         //横向与纵向跨度的绝对值
    int s1, s2;         //用于标记线段的状态

    x1 = (int)l.s.x;    //为起点与重点赋值
    y1 = (int)l.s.y;
    x2 = (int)l.e.x;
    y2 = (int)l.e.y;

	x = x1;    //设置要画的起始点
	y = y1;

	dx = abs(x2 - x1);  //求出横向跨度的绝对值
	dy = abs(y2 - y1);  //求出纵向跨度的绝对值

	/* 若x2在x1右边, 则向右走, 否则向左走 */
	if(x2 > x1)
		s1 = 1;
	else
		s1 = -1;

	/* 若y2在y1上面, 则向上走, 否则向下走 */
	if(y2 > y1)
		s2 = 1;
	else
		s2 = -1;

	/* 若纵向跨度大于横向跨度, 则沿着纵向走, 否则沿着横向走 */
	if(dy > dx) {
		temp = dx;
		dx = dy;
		dy = temp;
		interchange = 1;
	} else {
		interchange = 0;
    }

	p = 2 * dy - dx;  //p用来标记下一个要画的点的位置

	/* 从起点开始向终点移动                            */
	/* 以起点在左下, 终点在右上, 且斜率小于1的情况举例 */
	/* 若p大于0, 则下一个要画的点在上方                */
	/* 若p小于0, 则下一个要画的点在右方                */
	for(i = 1; i <= dx; i++) {
		setPixelArea(x, y, 1.0);
		if(p >= 0) {
			if(interchange == 0)
				y = y + s2;
			else
				x = x + s1;
			p = p - 2 * dx;
		}
		if(interchange == 0)
			x = x + s1; 
		else
			y = y + s2;
		p = p + 2 * dy;
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
    fscanf(readin, "颜色     :  (%hc, %hc, %hc)\n", &(line_color.R), &line_color.G, &line_color.B); //读入颜色
    fscanf(readin, "点的数量 :  %d\n",  &count_of_points);   //读入点的数量
    fscanf(readin, "顶点     :\n");                          //准备读入顶点坐标

    printf("count_of_points : %d\n", count_of_points);
    printf("颜色: (%d, %d, %d)\n", line_color.R, line_color.G, line_color.B);

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