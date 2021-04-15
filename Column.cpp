
#include"Column.h"




Column::Column()
{

	this->heightOfBottomColumn = rand() % 100 + 50;//随机50-149
	this->gapOfTwoColumn = rand() % 50 + 100;//
	this->xCol = windowsLenth - widthOfColumn;
	this->yCol = windowsWidth - this->heightOfBottomColumn;



}



void drawCol(int LTX, int LTY, int RBX, int RBY)
{
	HWND hwnd = GetForegroundWindow(); //找到程序运行窗口的句柄
	HDC hDC = GetDC((HWND)hwnd);//通过窗口句柄得到该窗口的设备场境句柄
	HPEN hPen; //画笔
	HBRUSH hBrush;

	hPen = CreatePen(PS_SOLID, 0, 0xff0000);
	hBrush = CreateSolidBrush(RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(hDC, hPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, hBrush);


	Rectangle(hDC, LTX, LTY, RBX, RBY);


	hPen = (HPEN)SelectObject(hDC, oldPen);
	hBrush = (HBRUSH)SelectObject(hDC, oldBrush);


	DeleteObject(hPen);
	DeleteObject(hBrush);
	DeleteObject(oldPen);
	DeleteObject(oldBrush);
	ReleaseDC(hwnd, hDC);
}

Column& Column::operator=(Column right)
{
	this->xCol = right.xCol;

	return *this;
}

void Column::drawColumn()
{
		drawCol(this->xCol, this->yCol, this->xCol + this->widthOfColumn, windowsWidth);//draw bottom rec
		drawCol(this->xCol, 0, this->xCol + this->widthOfColumn, this->yCol - this->gapOfTwoColumn);//draw top rec
}
void Column::moveColumn()//move position of Column over time
{
		this->xCol += vx;
}
void Column::changeColumn()
{
	srand((unsigned int)time(NULL));
	
		if (this->xCol <= -20)
		{
			this->xCol = windowsLenth - this->widthOfColumn;
			this->heightOfBottomColumn = rand() % 100 + 50;//随机50-149
			this->gapOfTwoColumn = rand() % 50 + 100;//
			this->yCol = windowsWidth - this->heightOfBottomColumn;
		}
	
}