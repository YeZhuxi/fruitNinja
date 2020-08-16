#pragma once
#ifndef GAME_H
#define GAME_H
#include <Windows.h>
#include "pictureClass.h"
#include <time.h>
#pragma comment(lib,"Winmm.lib")

class Game
{
public:
	void start();//开始游戏
	void startEnter();//进入界面，logo向下平移
	void startMenu();//产生菜单选项：继续游戏、新游戏、退出
	void newGame(int initScore, int initLoseNum);//新游戏
	void resumeGame();//继续游戏
	void exitGame();//退出
	void loadImg();//初始化所有IMAGE对象，并且初始化后不再改变
	void setPic();//初始化所有picture的src和srcMask成员，并且不再改变
	void putMouse(MOUSEMSG* m);//鼠标轨迹
	int PIrandom();//利用π生成0-1000随机数
	picture* randFruit();//随机生成水果
	void getmaxScore();

private:
	MOUSEMSG mouse;
	int score = 0;//分数
	int loseNum = 0;
	int hitBoom = 0;
	int maxScore;//最高分数

	//定义所有要用的IMAGE对象作为数据成员
	IMAGE apple, apple1, apple2;
	IMAGE appleMask, apple1Mask, apple2Mask;

	IMAGE basaha, basaha1, basaha2;
	IMAGE basahaMask, basaha1Mask, basaha2Mask;

	IMAGE peach, peach1, peach2;
	IMAGE peachMask, peach1Mask, peach2Mask;

	IMAGE sandia, sandia1, sandia2;
	IMAGE sandiaMask, sandia1Mask, sandia2Mask;

	IMAGE boom, boomMask;

	IMAGE background, backgroundMask;
	IMAGE developing, developingMask;
	IMAGE dojo, dojoMask;
	IMAGE gameover, gameoverMask;
	IMAGE homedesc, homedescMask;
	IMAGE logo, logoMask;
	IMAGE lose, loseMask;
	IMAGE new1, new1Mask;
	IMAGE newgame, newgameMask;
	IMAGE ninja, ninjaMask;
	IMAGE quit, quitMask;
	IMAGE drop, dropMask;

	//定义所有要用的picture对象作为数据成员
	picture applePic, apple1Pic, apple2Pic;
	picture basahaPic, basaha1Pic, basaha2Pic;
	picture peachPic, peach1Pic, peach2Pic;
	picture sandiaPic, sandia1Pic, sandia2Pic;
	picture boomPic;
	
	picture backgroundPic, developingPic, gameoverPic, losePic, dropPic;
	picture dojoPic, logoPic, newgamePic, ninjaPic, homedescPic, new1Pic, quitPic;
};
#endif // !GAME_H
