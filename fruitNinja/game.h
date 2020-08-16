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
	void start();//��ʼ��Ϸ
	void startEnter();//������棬logo����ƽ��
	void startMenu();//�����˵�ѡ�������Ϸ������Ϸ���˳�
	void newGame(int initScore, int initLoseNum);//����Ϸ
	void resumeGame();//������Ϸ
	void exitGame();//�˳�
	void loadImg();//��ʼ������IMAGE���󣬲��ҳ�ʼ�����ٸı�
	void setPic();//��ʼ������picture��src��srcMask��Ա�����Ҳ��ٸı�
	void putMouse(MOUSEMSG* m);//���켣
	int PIrandom();//���æ�����0-1000�����
	picture* randFruit();//�������ˮ��
	void getmaxScore();

private:
	MOUSEMSG mouse;
	int score = 0;//����
	int loseNum = 0;
	int hitBoom = 0;
	int maxScore;//��߷���

	//��������Ҫ�õ�IMAGE������Ϊ���ݳ�Ա
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

	//��������Ҫ�õ�picture������Ϊ���ݳ�Ա
	picture applePic, apple1Pic, apple2Pic;
	picture basahaPic, basaha1Pic, basaha2Pic;
	picture peachPic, peach1Pic, peach2Pic;
	picture sandiaPic, sandia1Pic, sandia2Pic;
	picture boomPic;
	
	picture backgroundPic, developingPic, gameoverPic, losePic, dropPic;
	picture dojoPic, logoPic, newgamePic, ninjaPic, homedescPic, new1Pic, quitPic;
};
#endif // !GAME_H