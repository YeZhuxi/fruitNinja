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
	IMAGE srcMask, src; //ԭͼ����Ĥͼ��
	double x, y; //λ��
	int height, width; //ͼ��ߡ���
	string srcPath, srcMaskPath; //ԭͼ����Ĥͼ��·��
	double theta;//���ýǶ�
	double v;//���ٶ�
	double alpha;//���ٶȷ���
	picture *pic[2]; //ԭͼ���п����ͼ��
	int ishalf; //ͼ���Ƿ��п�
	int isboom; //�Ƿ���ը��

public:
	picture();
	void setImg(IMAGE &sM, IMAGE &s);//����picture�����srcImage��maskImage
	void setData(double x0, double y0, double th, double u, double al);//����picture����Ĳ���
	void setData(double x0, double y0, double th, double u, double al, 
		picture *leftSide, picture *rightSide, int half);//����picture����Ĳ���
	void movePic(double t);//ͼƬ�ƶ��������ƶ��켣��������
	void putRotPic();//ͼƬ���ƣ��ѽ���͸��������������˸����ת
};
#endif // !PICTURECLASS_H