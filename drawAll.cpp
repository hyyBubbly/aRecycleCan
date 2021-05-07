#include<Windows.h>
#include"drawAll.h"
#include"Object.h"
extern int windowsLenth;
extern int windowsWidth;
//（不知道有没有更好的处理方法）把DrawBmp重载，分为普通画图和游戏中的渲染画图
//普通画图
HDC DrawBmp(HDC hDC, HDC dcMEM, HBITMAP hBitmap, Object& object, int bmpLenth, int bmpWidth)
{
    //dcMEM是和屏幕显示DC兼容的内存DC
    HDC dcTemp;
    dcTemp = CreateCompatibleDC(hDC);//创建一个内存DC
    //创建与hDC环境相关的设备兼容的位图
    //此处使用hDC(窗口DC)Create位图，否则图片只有黑白两色
    HBITMAP bmpBackground = CreateCompatibleBitmap(hDC, windowsLenth, windowsWidth);//参数分别为：hDC，位图长，位图宽
    //内存dc一号(dcMEM)select背景图片
    SelectObject(dcMEM, bmpBackground);
    //便于delete dcTemp，如果不用他替换掉hBitmap的话，delete时会把hBitmap一起删掉
    //返回值是被取代对象的句柄//保存旧的句柄，方便恢复原状
    //内存dc二号(dcTemp)select要画的图片
    
    HBITMAP hOldMap = (HBITMAP)SelectObject(dcTemp, hBitmap);//位图选择进内存DC
    
    //把dcTemp里的图画到dcMEM上
    BitBlt(dcMEM, object.getX(), object.getY(), bmpLenth, bmpWidth, dcTemp, 0, 0, SRCCOPY);
    //恢复原状
    SelectObject(dcTemp, hOldMap);
    DeleteObject(hOldMap);
    //删除dc
    DeleteDC(dcTemp);
    return dcMEM;
}

//游戏中的渲染画图
HDC DrawBmp(HDC hDC,HDC dcMEM, HBITMAP hBitmap, Can & can,int bmpLenth ,int bmpWidth,float interpolation)
{
    //实现插值(interpolation)和预言(view_Y)函数
    //其实现的原理实际上是补帧，比接受键盘操作有更高的帧率，根据预算时间计算位图画在哪个位置

    //当方向向上的时候，由于move()对y进行了加v_y，要获得【起点y】先要将getY()返回的数值减去v_y
    //计算view_Y的公式是【起点y】+ 速度×时间插值
    int view_Y;//渲染的预测y坐标
    if(can.direction=='W')
        view_Y = can.getY() + can.getv_y() * (interpolation - 1);
    else
        view_Y = can.getY();
    //当方向是向右的时候，就不要引用有插值的公式，因为它生成的时候有误差，这时候再用就会导致物体不正常抖动


    //dcMEM是和屏幕显示DC兼容的内存DC
    HDC dcTemp;
    dcTemp = CreateCompatibleDC(hDC);//创建一个内存DC
    //创建与hDC环境相关的设备兼容的位图
    //此处使用hDC(窗口DC)Create位图，否则图片只有黑白两色
    HBITMAP bmpBackground = CreateCompatibleBitmap(hDC, windowsLenth, windowsWidth);//参数分别为：hDC，位图长，位图宽
    //内存dc一号(dcMEM)select背景图片
    SelectObject(dcMEM, bmpBackground);
    //便于delete dcTemp，如果不用他替换掉hBitmap的话，delete时会把hBitmap一起删掉
    //返回值是被取代对象的句柄//保存旧的句柄，方便恢复原状
    //内存dc二号(dcTemp)select要画的图片
    HBITMAP hOldMap=(HBITMAP)SelectObject(dcTemp, hBitmap);//位图选择进内存DC
    //把dcTemp里的图画到dcMEM上
    BitBlt(dcMEM, can.getX(), view_Y, bmpLenth, bmpWidth, dcTemp, 0, 0, SRCCOPY);
    //恢复原状
    SelectObject(dcTemp, hOldMap);
    DeleteObject(hOldMap);
    //删除dc
    DeleteDC(dcTemp);
    return dcMEM;
}