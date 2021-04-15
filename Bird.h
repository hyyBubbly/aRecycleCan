#pragma once
class Bird
{
public:
	Bird();
	//~Bird();
	const int xBird = 40;//x coordinates of bird
	int yBird;//y corrdinates of bird
	int vY;//the vertical velocity of the bird;
	const int vAfterJump = -15;//speed when press space

	void jump();//when player press the space,turn vY to vAfterJump
	void moveBird();//move position of Bird according to speed(vY) over time
	void drawBird();

};