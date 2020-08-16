#include "pictureClass.h"

picture::picture()
{
	IMAGE black, white;
	loadimage(&white, _T("images\\white.jpg"));
	loadimage(&black, _T("images\\black.jpg"));
	srcMask = black;
	src = white;
	x = 0.0;
	y = 0.0;
	height = black.getheight();
	width = black.getwidth();
	theta = 0.0;
	v = 0.0;
	alpha = 0.0;
	pic[0] = NULL;
	pic[1] = NULL;
	ishalf = 0;
	isboom = 0;
}

void picture::setImg(IMAGE &sM, IMAGE &s)
{
	srcMask = sM;
	src = s;
	height = sM.getheight();
	width = sM.getwidth();
}

void picture::setData(double x0, double y0, double th, double u, double al)
{
	x = x0;
	y = y0;
	theta = th;
	v = u;
	alpha = al;
}

void picture::setData(double x0, double y0, double th, double u, double al, 
	picture *leftSide, picture *rightSide, int half)
{
	x = x0;
	y = y0;
	theta = th;
	v = u;
	alpha = al;
	pic[0] = leftSide;
	pic[1] = rightSide;
	ishalf = half;
}

void picture::movePic(double t)
{
	x += v * cos(alpha)*0.1;
	y += v * sin(alpha)*(-0.1) + g0 * t*0.1;
}

void picture::putRotPic()
{
	IMAGE srcMaskRot, srcRot;
	rotateimage(&srcMaskRot, &srcMask, theta);
	rotateimage(&srcRot, &src, theta, WHITE);
	putimage(int(x), int(y), &srcMaskRot, NOTSRCERASE);
	putimage(int(x), int(y), &srcRot, SRCINVERT);
}