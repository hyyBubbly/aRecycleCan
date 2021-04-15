#pragma once
#include<time.h>//srand（）和rand（）
#include<Windows.h>


extern int windowsLenth;
extern int windowsWidth;

extern const int vx;
extern const int gravity;
extern const int radius;

class Column
{
public:
	Column();
	//~Column();

	const int widthOfColumn = 20;//the width of column
	int heightOfBottomColumn;//the height of the column on the bottom
	int gapOfTwoColumn;//the lenth between topColumn and bottomColumn 
	int xCol, yCol;//the position of top left corner of the column


	void moveColumn();//move position of Bird according to speed(vY) over time
	void drawColumn();
	void changeColumn();
	Column& operator=(Column right);


};

//void drawCol(int LTX, int LTY, int RBX, int RBY)
//{
//	HWND hwnd = GetForegroundWindow(); //找到程序运行窗口的句柄
//	HDC hDC = GetDC((HWND)hwnd);//通过窗口句柄得到该窗口的设备场境句柄
//	HPEN hPen; //画笔
//	HBRUSH hBrush;
//
//	hPen = CreatePen(PS_SOLID, 0, 0xff0000);
//	hBrush = CreateSolidBrush(RGB(0, 255, 0));
//	HPEN oldPen = (HPEN)SelectObject(hDC, hPen);
//	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
//
//
//	Rectangle(hDC, LTX, LTY, RBX, RBY);
//
//
//	hPen = (HPEN)SelectObject(hDC, oldPen);
//	hBrush = (HBRUSH)SelectObject(hDC, oldBrush);
//
//
//	DeleteObject(hPen);
//	DeleteObject(hBrush);
//	DeleteObject(oldPen);
//	DeleteObject(oldBrush);
//	ReleaseDC(hwnd, hDC);
//}
//void drawColumn(Column column[], int Num)
//{
//	for (int i = 0;i < Num;i++)
//	{
//		drawCol(column[i].xCol, column[i].yCol, column[i].xCol + column[i].widthOfColumn, windowsWidth);//draw bottom rec
//		drawCol(column[i].xCol, 0, column[i].xCol + column[i].widthOfColumn, column[i].yCol - column[i].gapOfTwoColumn);//draw top rec
//	}
//}
//void moveColumn(Column column[], int Num)//move position of Column over time
//{
//	for (int i = 0;i < Num;i++)
//	{
//		column[i].xCol += vx;
//	}
//}
//void changeColumn(Column column[], int Num)
//{
//	srand((unsigned int)time(NULL));
//	for (int i = 0;i < Num;i++)
//	{
//		if (column[i].xCol <= -20)
//		{
//			column[i].xCol = windowsLenth - column[i].widthOfColumn;
//			column[i].heightOfBottomColumn = rand() % 100 + 50;//随机50-149
//			column[i].gapOfTwoColumn = rand() % 50 + 100;//
//			column[i].yCol = windowsWidth - column[i].heightOfBottomColumn;
//		}
//	}
//}