#include"Object.h"
const int vx = -8;//�����ƶ��ٶ�
const int gravity = 3;//ģ������
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
    //�������ΪW����������������̣������䵽�����ˣ��������ΪD
    if (direction == 'W' && v_y > 0 && y == 4 * windowsWidth / 5)
    {
        this->direction = 'D';
    }
}