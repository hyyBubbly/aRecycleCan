#include<Windows.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>

#include"Column.h"
#include"Bird.h"


const int BEFORE_START = 0;
const int BEFORE_INIT = 1;
const int PLAYING_GAME = 2;

const int vx = -8;//column speed
const int gravity = 3;
const int radius = 10;

int windowsLenth = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
int windowsWidth = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */

Bird bird;
const int Num = 4;
Column cArr[4];

static int flag = 0;

SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &info);
    return info.srWindow;
}
void showMenu(HANDLE screen);
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);
HDC DrawBmp(HDC hDCtemp, HBITMAP hBitmap,int LTX, int LTY,int RBX, int RBY)
{
    HDC hdcMEM; 
    hdcMEM = CreateCompatibleDC(hDCtemp);

    SelectObject(hdcMEM, hBitmap);//注意此处，将要画的位图选入hdcImage

    StretchBlt(hdcMEM, LTX, LTY, RBX, RBY, hdcMEM, LTX, LTY, RBX, RBY, SRCCOPY); //这里才能正常画图，将hdcImage中的位图直接复制到内存缓冲区
    StretchBlt(hDCtemp, LTX, LTY, RBX, RBY, hdcMEM, LTX, LTY, RBX, RBY, SRCCOPY); //再将内存缓冲区中的数据绘制到屏幕上.

    DeleteObject(hdcMEM);
    return hDCtemp;

}
int main()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;         //定义窗口缓冲区信息结构体  

    HANDLE	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获得标准输入设备句柄
    HANDLE	hIn = GetStdHandle(STD_INPUT_HANDLE);//获得标准输出设备句柄
    INPUT_RECORD mouserec;       //定义输入事件结构体  

    DWORD mode;
    GetConsoleMode(hIn, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;  //移除快速编辑模式
    mode &= ~ENABLE_INSERT_MODE;      //移除插入模式
    //mode &= ~ENABLE_MOUSE_INPUT;??
    SetConsoleMode(hIn, mode);

    HWND hwnd = GetForegroundWindow();

    int windowsLenth = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
    int windowsWidth = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */
    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);   /* 获取窗口信息 */

    //std::cout << "x" << cx << std::endl;
   // std::cout << "y" << cy << std::endl;
    //锁定窗口全屏
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_THICKFRAME);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, windowsLenth, windowsWidth, 0);
    // & ~WS_BORDER & ~WS_CAPTION
    //取消滚动条
    GetConsoleScreenBufferInfo(hOut, &csbi);
    SMALL_RECT rect = SizeOfWindow(hOut);
    COORD size = { rect.Right + 1,rect.Bottom + 1 }; //定义缓冲区大小 
    SetConsoleScreenBufferSize(hOut, size);//point
    /*std::cout << "right" << rect.Right << std::endl;
    std::cout << "Bottom" << rect.Bottom << std::endl;
    std::cout << "Left" << rect.Left << std::endl;
    std::cout << "Top" << rect.Top << std::endl;*/
    DWORD res;       //用于存储读取记录  
    COORD pos;       //用于存储鼠标当前位置  



    MSG msg;
    UINT_PTR MyIDMenu = SetTimer(NULL, 1, 1, &TimerProc);
    DWORD InNum = 0;
    DWORD judge = 1;
    LPDWORD InputNum = &InNum;

    POINT p;//鼠标坐标
    showMenu(hOut);
    ReadConsoleInput(hIn, &mouserec, 1, &res);       //读取输入事件
    for (;;)
    {
        GetNumberOfConsoleInputEvents(hIn, InputNum);
        if (*InputNum >= judge)
        {
            ReadConsoleInput(hIn, &mouserec, 1, &res);       //读取输入事件
        }
        pos = mouserec.Event.MouseEvent.dwMousePosition;     //获得当前鼠标位置  
        GetCursorPos(&p);

        

        if (mouserec.EventType == MOUSE_EVENT)     //如果当前为鼠标事件  
        {
            if (mouserec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                //std::cout << p.x << std::endl << p.y << std::endl;
                switch (flag)
                {
                case 0:
                {
                    //SetConsoleCursorPosition(hOut, pos);//把光标移动到pos位置
                    //std::cout << "x: " << p.x << "y: " << p.y << std::endl;
                    if (p.x > 600 && p.x < 867 && p.y >344 && p.y < 411)
                    {
                        system("cls");
                        //KillTimer(NULL, MyIDMenu);
                        flag = BEFORE_INIT;
                    }
                    break;
                }
                default:
                    break;
                }
            }
        }
        switch (flag)
        {
        case 0:
            break;
        case 1:
        {
            //showMenu(hOut);
            flag = PLAYING_GAME;
            break;
        }
        case 2:
        {
            //system("cls");
            bird.drawBird();
            bird.moveBird();
            for (int i = 0; i < Num; i++)
            {
                cArr[i].moveColumn();
                cArr[i].changeColumn();
            }
            Sleep(50);
            break;
        }
        }
        PeekMessage(&msg, NULL, 0, 0,PM_NOREMOVE);
            if(msg.message == WM_TIMER)
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        
    }

    CloseHandle(hOut);
    CloseHandle(hIn);

    return 0;

}
void showMenu(HANDLE screen)
{

    int cx = GetSystemMetrics(SM_CXSCREEN);            /* 屏幕宽度 像素 */
    int cy = GetSystemMetrics(SM_CYSCREEN);            /* 屏幕高度 像素 */

    HMODULE hKernel32 = GetModuleHandle("kernel32");
    HWND cmd = GetConsoleWindow();//控制台窗口句柄

    HDC dc = GetDC(cmd);
    HBITMAP hBitmap;
    HDC cmdmem = CreateCompatibleDC(dc);
    hBitmap = (HBITMAP)LoadImage(NULL, "continue320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);



    SelectObject(cmdmem, hBitmap);

    int buttonStartWidth = 320;
    int buttonStartHeight = 180;

    BitBlt(dc, (cx / 2), (3*cy / 5), buttonStartWidth, buttonStartHeight, cmdmem, 0, 0, SRCCOPY);

    return;
}
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
    HANDLE	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获得标准输入设备句柄
//WM_TIMER
    if (flag == BEFORE_START)
    {
        showMenu(hOut);
    }
    //else
    //{
    //    bird.drawBird();
    //    bird.moveBird();
    //    for (int i = 0; i < Num; i++)
    //    {
    //        cArr[i].moveColumn();
    //        cArr[i].changeColumn();
    //    }
    //    /* for (int i = 0; i < Num; i++)
    //     {
    //         cArr[i].drawColumn();
    //     }*/

    //}

}