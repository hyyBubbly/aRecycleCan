#include"Object.h"
const int vx = -8;//背景移动速度
const int gravity = 3;//模拟重力
Can::Can()
{
    level = LEVEL_0;
    v_y = 0;
    direction = 'D';
}
void Can::jump()
{
    direction = 'W';
    v_y = vAfterJump;
}
void Can::move()
{
    if (direction == 'W')
    {
        y = y + v_y;
        v_y = v_y + gravity;
    }
}
void Can::draw()
{
    
}

void Can::changeState()
{
    //如果方向为W，并且是在下落过程，并且落到地面了，则方向更改为D
    if (direction == 'W' && v_y > 0 && y == 4 * windowsWidth / 5)
    {
        this->direction = 'D';
    }
}