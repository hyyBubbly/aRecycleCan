#pragma once
#include"Bird.h"
#include"Column.h"


void drawAll(Bird bird,Column cArr[])
{
	bird.drawBird();
	drawColumn(cArr, 4);
}