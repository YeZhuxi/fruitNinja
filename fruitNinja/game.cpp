#include "game.h"

void Game::getmaxScore()
{
	fstream file("file/score.txt", ios::in);
	file >> maxScore;
	file.close();
}

void Game::start()
{
	loadImg(); //加载图像
	setPic(); //初始化图像及其掩膜图像
	initgraph(640, 480); //初始化窗口640*480
	startEnter(); //开始动画界面
	startMenu(); //开始菜单界面
}

void Game::startEnter()
{
	IMAGE temp;
	logoPic.setData(5, -1 * logo.getheight(), 0, 0, 0); //设置logo位置

	//播放背景音乐
	mciSendString(_T("open sound\\menu.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("play bgm from 0 repeat"), NULL, 0, NULL);
	while (true)
	{
		BeginBatchDraw();
		putimage(0, 0, &background); //用背景覆盖界面，实现界面刷新功能
		logoPic.y++; //向下移动
		logoPic.putRotPic(); //显示logo
		EndBatchDraw();
		if (logoPic.y == 5)
		{
			break; //到达预定位置
		}
		Sleep(1); //防止过快
	}

	getimage(&temp, 0, 0, 640, 480); //截图保存至temp
	ninjaPic.setData(logoPic.width + logoPic.x + 5, -1 * logoPic.width, 0, 0, 0); //设置ninja位置
	while (true)
	{
		BeginBatchDraw();
		putimage(0, 0, &temp);
		ninjaPic.y++;
		ninjaPic.putRotPic();
		EndBatchDraw();
		if (ninjaPic.y == 55)
		{
			break;
		}
	}
}

void Game::startMenu()
{
	double x, y;
	const int x0 = 5, y0 = 5;
	IMAGE temp1, temp2;
	putimage(0, 0, &background); //背景覆盖

	logoPic.setData(x0, y0, 0, 0, 0);
	logoPic.putRotPic();

	ninjaPic.setData(logoPic.width + logoPic.x + 5, 55, 0, 0, 0);
	ninjaPic.putRotPic();

	homedescPic.setData(x0, y0 + logoPic.height, 0, 0, 0);
	homedescPic.putRotPic();

	getimage(&temp1, 0, 0, 640, 480);

	dojoPic.setData(25, homedescPic.height + homedescPic.y + 20, 0, 0, 0);
	dojoPic.putRotPic();

	x = dojoPic.x + dojoPic.width / 2 - peach.getwidth() / 2;
	y = dojoPic.y + dojoPic.height / 2 - peach.getheight() / 2;
	peachPic.setData(x, y, 0, 0, 0);
	peachPic.putRotPic();

	newgamePic.setData(dojoPic.x + dojoPic.width + 60, dojoPic.y - 50, 0, 0, 0);
	newgamePic.putRotPic();

	new1Pic.setData(newgamePic.x + newgamePic.width - 30, newgamePic.y - 10, 0, 0, 0);
	new1Pic.putRotPic();

	x = newgamePic.x + newgamePic.width / 2 - sandia.getwidth() / 2;
	y = newgamePic.y + newgamePic.height / 2 - sandia.getheight() / 2;
	sandiaPic.setData(x, y, 0, 0, 0);
	sandiaPic.putRotPic();

	x = newgamePic.x + newgamePic.width + 25;
	y = newgamePic.y + 120;
	quitPic.setData(x, y, 0, 0, 0);
	quitPic.putRotPic();

	x = quitPic.x + quitPic.width / 2 - boom.getwidth() / 2;
	y = quitPic.y + quitPic.height / 2 - boom.getheight() / 2;
	boomPic.setData(x, y, 0, 0, 0);
	boomPic.putRotPic();

	getimage(&temp2, 0, 0, 640, 480);

	while (true)
	{
		//旋转
		quitPic.theta += PI / 500;
		newgamePic.theta += PI / 1500;
		dojoPic.theta += PI / 1500;
		BeginBatchDraw();
		quitPic.putRotPic();
		newgamePic.putRotPic();
		dojoPic.putRotPic();
		EndBatchDraw();

		if (MouseHit())
		{
			mouse = GetMouseMsg();
			if (mouse.mkLButton&&mouse.uMsg == WM_MOUSEMOVE)
			{
				//putMouse(mouse);
				//退出游戏
				if (mouse.x >= boomPic.x &&
					mouse.x <= boomPic.x + boomPic.width &&
					mouse.y >= boomPic.y &&
					mouse.y <= boomPic.y + boomPic.height)
				{
					mciSendString(_T("play sound\\boom.mp3"), NULL, 0, NULL);
					Sleep(1000);
					BeginBatchDraw();
					putimage(0, 0, &temp1);
					putMouse(&mouse);
					boomPic.putRotPic();
					EndBatchDraw();
					mciSendString(_T("stop bgm"), NULL, 0, NULL);
					mciSendString(_T("close bgm"), NULL, 0, NULL);
					mciSendString(_T("play sound/over.mp3"), NULL, 0, NULL);
					Sleep(2500);
					exitGame();
				}

				//继续游戏
				if (mouse.x >= peachPic.x &&
					mouse.x <= peachPic.x + peachPic.width &&
					mouse.y >= peachPic.y &&
					mouse.y <= peachPic.y + peachPic.height)
				{
					mciSendString(_T("play sound\\splatter.mp3"), NULL, 0, NULL);
					Sleep(500);
					peach1Pic.setData(peachPic.x - 10, peachPic.y, 0, 0, 0);
					peach2Pic.setData(peachPic.x + 10, peachPic.y, 0, 0, 0);
					BeginBatchDraw();
					putimage(0, 0, &temp1);
					putMouse(&mouse);
					peach1Pic.putRotPic();
					peach2Pic.putRotPic();
					EndBatchDraw();
					Sleep(100);
					mciSendString(_T("stop bgm"), NULL, 0, NULL);
					mciSendString(_T("play sound\\start.mp3"), NULL, 0, NULL);
					resumeGame();
				}

				//新游戏
				if (mouse.x >= sandiaPic.x &&
					mouse.x <= sandiaPic.x + sandiaPic.width &&
					mouse.y >= sandiaPic.y &&
					mouse.y <= sandiaPic.y + sandiaPic.height)
				{
					mciSendString(_T("play sound\\splatter.mp3"), NULL, 0, NULL);
					Sleep(500);
					sandia1Pic.setData(sandiaPic.x - 10, sandiaPic.y, 0, 0, 0);
					sandia2Pic.setData(sandiaPic.x + 10, sandiaPic.y, 0, 0, 0);
					BeginBatchDraw();
					putimage(0, 0, &temp1);
					putMouse(&mouse);
					sandia1Pic.putRotPic();
					sandia2Pic.putRotPic();
					EndBatchDraw();
					Sleep(100);
					mciSendString(_T("stop bgm"), NULL, 0, NULL);
					mciSendString(_T("play sound\\start.mp3"), NULL, 0, NULL);
					newGame(0, 0);
				}
			}
		}

		if (dojoPic.theta >= 2 * PI)
		{
			quitPic.theta -= 2 * PI;
			newgamePic.theta -= 2 * PI;
			dojoPic.theta -= 2 * PI;
		}

		Sleep(1);
	}
}

void Game::newGame(int initScore, int initLoseNum)
{
	int n;
	loseNum = initLoseNum;
	int j, flag;
	string sco, maxSco, ls;
	double t;
	score = initScore;
	getmaxScore();
	hitBoom = 0;
	while (true)
	{
		t = 0.0;
		n = PIrandom() % 3 + 1 + int(log10(score + 1)); //水果批次个数
		if (n > 5)
		{
			n = 5;
		}
		picture *fruit[5];
		for (j = 0; j < n; j++)
		{
			fruit[j] = randFruit();
		}

		while (true)
		{
			flag = 0;
			for (j = 0; j < n; j++)
			{
				t += 0.001;
				if (fruit[j]->x < 640 && fruit[j]->y <= 480)
					fruit[j]->movePic(t);
			}
			BeginBatchDraw();
			putimage(0, 0, &background);
			outtextxy(5, 5, "Max Score: ");
			maxSco = to_string(maxScore);
			outtextxy(100, 5, &maxSco[0]);
			outtextxy(5, 25, "Score: ");
			sco = to_string(score);
			outtextxy(100, 25, &sco[0]);
			outtextxy(5, 45, "lose: ");
			ls = to_string(loseNum);
			outtextxy(100, 45, &ls[0]);
			for (j = 0; j < n; j++)
			{
				if (fruit[j]->x < 640 && fruit[j]->y >(-1)*fruit[j]->height && fruit[j]->y <= 480)
				{
					if (fruit[j]->ishalf == 0)
					{
						fruit[j]->putRotPic();
					}
					else
					{
						fruit[j]->pic[0]->setData(fruit[j]->x - 20, fruit[j]->y, 0, 0, 0);
						fruit[j]->pic[1]->setData(fruit[j]->x + 20, fruit[j]->y, 0, 0, 0);
						fruit[j]->pic[0]->putRotPic();
						fruit[j]->pic[1]->putRotPic();
					}
				}
			}
			EndBatchDraw();
			if (MouseHit())
			{
				mouse = GetMouseMsg();
				putMouse(&mouse);
				if (mouse.mkRButton == true) //右键暂停
				{
					outtextxy(mouse.x, mouse.y, "Pause");
					Sleep(1000);
					startMenu();
				}
				for (j = 0; j < n; j++)
				{
					if (mouse.x >= fruit[j]->x + fruit[j]->width*0.25 && 
						mouse.x <= fruit[j]->x + fruit[j]->width*0.75 && 
						mouse.y >= fruit[j]->y + fruit[j]->height*0.25 && 
						mouse.y <= fruit[j]->y + fruit[j]->width*0.75 && 
						mouse.mkLButton && mouse.uMsg == WM_MOUSEMOVE)
					{
						putMouse(&mouse);
						if (fruit[j]->isboom == 1)
						{
							if (score >= maxScore)
							{
								fstream file("file/score.txt", ios::out);
								file << score;
								file.close();
							}
							hitBoom = 1;
							//播放结束音乐
							mciSendString(_T("play sound\\boom.mp3"), NULL, 0, NULL);
							Sleep(4000);
							gameoverPic.setData(320 - gameoverPic.width / 2, 240 - gameoverPic.height / 2, 0, 0, 0);
							gameoverPic.putRotPic();
							mciSendString(_T("play sound\\over.mp3"), NULL, 0, NULL);
							Sleep(5000);
							FlushMouseMsgBuffer();
							mciSendString(_T("play bgm from 0 repeat"), NULL, 0, NULL);
							startMenu();
						}
						else if (fruit[j]->ishalf == 0)
						{
							mciSendString(_T("play sound\\splatter.mp3"), NULL, 0, NULL);
							score++;
							fruit[j]->v = 0;
							fruit[j]->ishalf = 1;
						}
					}
				}
			}
			if (maxScore < score)
			{
				maxScore = score;
			}
			for (j = 0; j < n; ++j)
			{
				if (fruit[j]->x < 640 && fruit[j]->y <= 480)
				{
					flag = 1;
					break;
				}
			}
			Sleep(1);
			if (flag == 0) //此轮结束
			{
				Sleep(200);
				break;
			}
		}

		for (j = 0; j < n; ++j)
		{
			if (fruit[j]->isboom == 0 && fruit[j]->ishalf == 0)
			{
				++loseNum;
				ls = to_string(loseNum);
				outtextxy(100, 45, &ls[0]);
			}
		}

		if (loseNum >= 3)
		{
			if (score >= maxScore)
			{
				fstream file("file/score.txt", ios::out);
				file << score;
				file.close();
			}
			Sleep(1000);
			gameoverPic.setData(320 - gameoverPic.width / 2, 240 - gameoverPic.height / 2, 0, 0, 0);
			gameoverPic.putRotPic();
			mciSendString(_T("play sound\\over.mp3"), NULL, 0, NULL);
			Sleep(5000);
			FlushMouseMsgBuffer();
			mciSendString(_T("play bgm from 0 repeat"), NULL, 0, NULL);
			startMenu();
		}
	} 
}

void Game::resumeGame()
{
	if (loseNum < 3 && hitBoom == 0)
	{
		newGame(score, loseNum);
	}
	else
	{
		newGame(0, 0);
	}
}

void Game::exitGame()
{
	mciSendString(_T("close bgm"), NULL, 0, NULL);
	Sleep(2000);
	closegraph();
	exit(0);
}

void Game::putMouse(MOUSEMSG* m)
{
	solidcircle(m->x, m->y, 5);
}

int Game::PIrandom()
{
	int random;
	static double sum = 1;
	double term = 2, tmp = 0;
	for (int i = 0; fabs(term - 1) >= 1e-8; i++)
	{
		sum *= term;
		tmp = sqrt(2 + tmp);
		term = 2 / tmp;
	}
	random = ((int)sum) % 1000;
	sum *= 1000;
	sum -= ((int)sum) / 1000 * 1000;
	return random;
}

picture* Game::randFruit()
{
	int i = PIrandom() % 5;
	double v = double((PIrandom() % 2) + 11);//随机产生初速度
	double alpha = 0.1*PI*(double(PIrandom() % 100)) / 100.0 + PI * 0.38;//随机产生初速度方向
	int x = PIrandom() % 120 + 60;//随机产生初始x坐标,位于界面左侧
	int y = 480;//初始y坐标均为480，在界面以下
	switch (i)
	{
	case 0:
		peachPic.setData(x, y, 0, v, alpha, &peach1Pic, &peach2Pic, 0);
		
		return &peachPic;
	case 1:
		sandiaPic.setData(x, y, 0, v, alpha, &sandia1Pic, &sandia2Pic, 0);
		
		return &sandiaPic;
	case 2:
		basahaPic.setData(x, y, 0, v, alpha, &basaha1Pic, &basaha2Pic, 0);
		
		return &basahaPic;
	case 3:
		applePic.setData(x, y, 0, v, alpha, &apple1Pic, &apple2Pic, 0);
		
		return &applePic;
	case 4:
		boomPic.isboom = 1;
		boomPic.setData(x, y, 0, v, alpha);
		
		return &boomPic;
	default:
		return NULL;
	}
}

void Game::loadImg()
{
	loadimage(&background, _T("images\\background.jpg"));
	loadimage(&backgroundMask, _T("images\\backgroundMask.jpg"));

	loadimage(&developing, _T("images\\developing.jpg"));
	loadimage(&developingMask, _T("images\\developingMask.jpg"));

	loadimage(&dojo, _T("images\\dojo.jpg"));
	loadimage(&dojoMask, _T("images\\dojoMask.jpg"));

	loadimage(&gameover, _T("images\\game-over.jpg"));
	loadimage(&gameoverMask, _T("images\\game-overMask.jpg"));

	loadimage(&homedesc, _T("images\\home-desc.jpg"));
	loadimage(&homedescMask, _T("images\\home-descMask.jpg"));

	loadimage(&logo, _T("images\\logo.jpg"));
	loadimage(&logoMask, _T("images\\logoMask.jpg"));

	loadimage(&lose, _T("images\\lose.jpg"));
	loadimage(&loseMask, _T("images\\loseMask.jpg"));

	loadimage(&new1, _T("images\\new1.jpg"));
	loadimage(&new1Mask, _T("images\\new1Mask.jpg"));

	loadimage(&newgame, _T("images\\new-game.jpg"));
	loadimage(&newgameMask, _T("images\\new-gameMask.jpg"));

	loadimage(&ninja, _T("images\\ninja.jpg"));
	loadimage(&ninjaMask, _T("images\\ninjaMask.jpg"));

	loadimage(&quit, _T("images\\quit.jpg"));
	loadimage(&quitMask, _T("images\\quitMask.jpg"));

	loadimage(&drop, _T("images\\drop.jpg"));
	loadimage(&dropMask, _T("images\\dropMask.jpg"));

	loadimage(&boom, _T("images\\fruit\\boom.jpg"));
	loadimage(&boomMask, _T("images\\fruit\\boomMask.jpg"));

	loadimage(&apple, _T("images\\fruit\\apple.jpg"));
	loadimage(&appleMask, _T("images\\fruit\\appleMask.jpg"));
	loadimage(&apple1, _T("images\\fruit\\apple-1.jpg"));
	loadimage(&apple1Mask, _T("images\\fruit\\apple-1Mask.jpg"));
	loadimage(&apple2, _T("images\\fruit\\apple-2.jpg"));
	loadimage(&apple2Mask, _T("images\\fruit\\apple-2Mask.jpg"));

	loadimage(&basaha, _T("images\\fruit\\basaha.jpg"));
	loadimage(&basahaMask, _T("images\\fruit\\basahaMask.jpg"));
	loadimage(&basaha1, _T("images\\fruit\\basaha-1.jpg"));
	loadimage(&basaha1Mask, _T("images\\fruit\\basaha-1Mask.jpg"));
	loadimage(&basaha2, _T("images\\fruit\\basaha-2.jpg"));
	loadimage(&basaha2Mask, _T("images\\fruit\\basaha-2Mask.jpg"));

	loadimage(&peach, _T("images\\fruit\\peach.jpg"));
	loadimage(&peachMask, _T("images\\fruit\\peachMask.jpg"));
	loadimage(&peach1, _T("images\\fruit\\peach-1.jpg"));
	loadimage(&peach1Mask, _T("images\\fruit\\peach-1Mask.jpg"));
	loadimage(&peach2, _T("images\\fruit\\peach-2.jpg"));
	loadimage(&peach2Mask, _T("images\\fruit\\peach-2Mask.jpg"));

	loadimage(&sandia, _T("images\\fruit\\sandia.jpg"));
	loadimage(&sandiaMask, _T("images\\fruit\\sandiaMask.jpg"));
	loadimage(&sandia1, _T("images\\fruit\\sandia-1.jpg"));
	loadimage(&sandia1Mask, _T("images\\fruit\\sandia-1Mask.jpg"));
	loadimage(&sandia2, _T("images\\fruit\\sandia-2.jpg"));
	loadimage(&sandia2Mask, _T("images\\fruit\\sandia-2Mask.jpg"));
}

void Game::setPic()
{
	applePic.setImg(appleMask, apple);
	apple1Pic.setImg(apple1Mask, apple1);
	apple2Pic.setImg(apple2Mask, apple2);

	basahaPic.setImg(basahaMask, basaha);
	basaha1Pic.setImg(basaha1Mask, basaha1);
	basaha2Pic.setImg(basaha2Mask, basaha2);

	peachPic.setImg(peachMask, peach);
	peach1Pic.setImg(peach1Mask, peach1);
	peach2Pic.setImg(peach2Mask, peach2);

	sandiaPic.setImg(sandiaMask, sandia);
	sandia1Pic.setImg(sandia1Mask, sandia1);
	sandia2Pic.setImg(sandia2Mask, sandia2);

	boomPic.setImg(boomMask, boom);

	backgroundPic.setImg(backgroundMask, background);
	developingPic.setImg(developingMask, developing);
	dojoPic.setImg(dojoMask, dojo);
	gameoverPic.setImg(gameoverMask, gameover);
	homedescPic.setImg(homedescMask, homedesc);
	logoPic.setImg(logoMask, logo);
	losePic.setImg(loseMask, lose);
	new1Pic.setImg(new1Mask, new1);
	newgamePic.setImg(newgameMask, newgame);
	ninjaPic.setImg(ninjaMask, ninja);
	quitPic.setImg(quitMask, quit);
}

