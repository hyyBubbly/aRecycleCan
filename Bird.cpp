
#include<time.h>//srand（）和rand（）
#include<Windows.h>
#include"Bird.h"
extern const int vx;
extern const int gravity;
extern const int radius;


extern int windowsLenth;
extern int windowsWidth;

void drawBir(int LTX, int LTY, int RBX, int RBY)
{
	HWND hwnd = GetForegroundWindow(); //找到程序运行窗口的句柄
	HDC hDC = GetDC((HWND)hwnd);//通过窗口句柄得到该窗口的设备场境句柄
	HPEN hPen; //画笔
	HBRUSH hBrush;

	hPen = CreatePen(PS_SOLID, 0, 0xff0000);
	hBrush = CreateSolidBrush(RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);


	Ellipse(hDC, LTX, LTY, RBX, RBY);


	hPen = (HPEN)SelectObject(hDC, oldPen);
	hBrush = (HBRUSH)SelectObject(hDC, oldBrush);


	DeleteObject(hPen);
	DeleteObject(hBrush);
	DeleteObject(oldPen);
	DeleteObject(oldBrush);
	ReleaseDC(hwnd, hDC);
}

Bird::Bird()
{
	this->vY = vAfterJump;
	this->yBird = windowsWidth / 2;
}
void Bird::jump()
{
	this->vY = vAfterJump;
}
void Bird::moveBird()
{
	this->vY = vY + gravity;
	this->yBird = yBird + vY;
}
void Bird::drawBird()
{
	drawBir(this->xBird-radius, this->yBird - radius, this->xBird + radius, this->yBird + radius);
}