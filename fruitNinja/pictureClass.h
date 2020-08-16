#pragma once
#ifndef PICTURECLASS_H
#define PICTURECLASS_H

#define PI 3.14159265
#define g0 10.0
#include <string>
#include <easyx.h>
#include <graphics.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#pragma comment(lib,"Winmm.lib")

using namespace std;

class picture
{
public:
	IMAGE srcMask, src; //原图和掩膜图像
	double x, y; //位置
	int height, width; //图像高、宽
	string srcPath, srcMaskPath; //原图像、掩膜图像路径
	double theta;//放置角度
	double v;//初速度
	double alpha;//初速度方向
	picture *pic[2]; //原图像被切开后的图像
	int ishalf; //图像是否被切开
	int isboom; //是否是炸弹

public:
	picture();
	void setImg(IMAGE &sM, IMAGE &s);//设置picture对象的srcImage和maskImage
	void setData(double x0, double y0, double th, double u, double al);//设置picture对象的参数
	void setData(double x0, double y0, double th, double u, double al, 
		picture *leftSide, picture *rightSide, int half);//设置picture对象的参数
	void movePic(double t);//图片移动函数，移动轨迹是抛物线
	void putRotPic();//图片绘制，已进行透明处理、消除闪烁、旋转
};
#endif // !PICTURECLASS_H
