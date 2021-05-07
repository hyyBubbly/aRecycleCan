#include<Windows.h>
#include<stdio.h>
#include<conio.h>
#include<iostream>

#include"Object.h"
#include"drawAll.h"
#include"upDateData.h"

using namespace std;

const int BEFORE_START = 0;
const int BEFORE_INIT = 1;
const int PLAYING_GAME = 2;

const int vx = -8;//�����ƶ��ٶ�
const int gravity = 3;//ģ������

const int TICKS_PER_SECOND = 50;//50֡ÿ��ĸ����ٶ�
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;//1000֡�����ʱ�䣿
const int MAX_FRAMESKIP = 5;//֡��������С����͵ı���

int windowsLenth = GetSystemMetrics(SM_CXSCREEN);            /* ��Ļ��� ���� */
int windowsWidth = GetSystemMetrics(SM_CYSCREEN);            /* ��Ļ�߶� ���� */

Can hh;//��������������

static int flag = BEFORE_START;//������Ϸ״̬Ϊ��������Ϸǰ



SMALL_RECT SizeOfWindow(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &info);
    return info.srWindow;
}
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime);//�ص�����
int main()
{         
    //���崰�ڻ�������Ϣ�ṹ��  
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    //����ͼƬ��Դ���������һ��resource.cpp�ļ�ר�ż��ظ���ͼƬ��Դ
    HBITMAP continue320180 = (HBITMAP)LoadImage(NULL, "continue320180.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
    //��ñ�׼����豸���
    HANDLE	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //��ñ�׼�����豸���
    HANDLE	hIn = GetStdHandle(STD_INPUT_HANDLE);
    //���������¼��ṹ��  
    INPUT_RECORD inputRecord;
    //������ṹ��
    CONSOLE_CURSOR_INFO CursorInfo;
   
    DWORD mode;
    GetConsoleMode(hIn, &mode);
    mode &= ~ENABLE_QUICK_EDIT_MODE;  //�Ƴ����ٱ༭ģʽ
    mode &= ~ENABLE_INSERT_MODE;      //�Ƴ�����ģʽ
    //mode &= ~ENABLE_MOUSE_INPUT;//����֪��ʲôģʽ
    SetConsoleMode(hIn, mode);
    //�õ�ǰ̨���ڣ��û���ǰ�����Ĵ��ڣ����
    HWND hwnd = GetForegroundWindow();
    /* ��ȡ������Ϣ */
    LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);
    //��������ȫ��
    SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_THICKFRAME);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, windowsLenth, windowsWidth, 0);
    // & ~WS_BORDER & ~WS_CAPTION
    //ȡ������������֪����������һ�䣩
    GetConsoleScreenBufferInfo(hOut, &csbi);
    SMALL_RECT rect = SizeOfWindow(hOut);
    //���建������С 
    COORD size = { rect.Right + 1,rect.Bottom + 1 };
    SetConsoleScreenBufferSize(hOut, size);//point
    // ���ؿ���̨���
    GetConsoleCursorInfo(hOut, &CursorInfo);//��ȡ����̨�����Ϣ
    CursorInfo.bVisible = false; //���ؿ���̨���
    SetConsoleCursorInfo(hOut, &CursorInfo);//���ÿ���̨���״̬

    DWORD res;       //���ڴ洢��ȡ��¼
    COORD pos;       //���ڴ洢��굱ǰλ��  
    
    DWORD next_game_tick=(DWORD)0;
    int loops;//
    float interpolation;//����ȼ۵�֡��//��Ⱦ֡����Ԥ�����ֵʵ�ֵ�

    HWND cmd = GetConsoleWindow();//����̨���ھ��
    //�õ��豸�������豸���������������DC
    HDC hDC = GetDC(cmd);//��Ļ��ʾDC
    //������Ļ��ʾDC�����ڴ�DC�豸��������
    HDC dcMEM = CreateCompatibleDC(hDC);//�ڴ����DC
    MSG msg;
    int timerID = 1;//TimerID
    int period = 40;//40ms����һ��timer
    UINT_PTR MyID1 = SetTimer(NULL, timerID, period, (TIMERPROC)&TimerProc);
    DWORD InNum = 0;//�������滺���������¼�������
    DWORD judge = 1;//������InNum�Ƚϴ�С
    //ת�����ͣ��Ժ��InputNum���ݸ�GetNumberOfConsoleInputEvents
    LPDWORD InputNum = &InNum;

    POINT p;//�������
    //��ʼ��inputRecord
    ReadConsoleInput(hIn, &inputRecord, 1, &res);       //��ȡ�����¼�
    for (;;)
    {   
        //���������¼���ʱ��ŵ���ReadConsoleInput
        //��ֹ����ͣ�����ȴ�������Ϣ�������ѭ������
        GetNumberOfConsoleInputEvents(hIn, InputNum);
        if (*InputNum >= judge)
        {
            ReadConsoleInput(hIn, &inputRecord, 1, &res);       //��ȡ�����¼�
        }
        pos = inputRecord.Event.MouseEvent.dwMousePosition;     //��õ�ǰ���λ��  
        GetCursorPos(&p);
        if (inputRecord.EventType == MOUSE_EVENT)     //�����ǰΪ����¼�  
        {
            if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//������
            {
                switch (flag)
                {
                case BEFORE_START://�������İ�ť�У���ʼ���������ɾͣ��˳������ã�����
                {
                    //SetConsoleCursorPosition(hOut, pos);//�ѹ���ƶ���posλ��
                    //������ð�װ��һ���ж�λ���ڲ��ھ�������ĺ���
                    if (p.x > (windowsLenth / 2) - 160&& p.x < (windowsLenth / 2) + 160 && p.y > (3 * windowsWidth / 5) - 90 && p.y < (3 * windowsWidth / 5) + 90)
                    {
                        system("cls");
                        //KillTimer(NULL, MyID1);
                        flag = BEFORE_INIT;
                    }
                    break;
                }
                default:
                    break;
                }
            }
        }
        //�����ǰ�¼��Ǽ����¼�
        else if (inputRecord.EventType == KEY_EVENT)
        {
            switch (flag)
            {
            case PLAYING_GAME:
            {
                if (inputRecord.Event.KeyEvent.wVirtualKeyCode == 0x57 && inputRecord.Event.KeyEvent.bKeyDown && hh.direction != 'W')
                {

                    //�û�������W
                    hh.jump();
                    inputRecord.Event.KeyEvent.wVirtualKeyCode = '0';//Ϊ��֪����ʱû�а�W���Ұ������ó������ڰ�0

                }
                break;
            }
            }
        }
        switch (flag)
        {
        case BEFORE_START:
        {
            //��continue�ƶ������ô��ŵ�λ��
            hh.setX(windowsLenth / 2);
            hh.setY(3 * windowsWidth / 5);
            DrawBmp(hDC,dcMEM, continue320180, hh, 320, 180);//�����ڴ�dc��
            break;
        }
        case BEFORE_INIT:
        {
            next_game_tick = GetTickCount64();//���شӳ���ʼ���е����ڵ�ʱ��/ms

            //�ı�������λ�ã���Ȼ������ʹ��continue��ͼ���ݴ�����������
            hh.setX(windowsLenth / 8);
            hh.setY(4*windowsWidth / 5);
            flag = PLAYING_GAME;
            break;
        }
        case PLAYING_GAME:
        {
            //system("cls");
            //update���������ݣ������ѧϰ��Ϸ��ѭ�������Ƹ������ݺ���Ⱦ��Ƶ�ʣ�Ŀǰ��û��

            //������벻��Ҫ����ô�ߵ�֡�ʸ��£�ǰ������Ϊÿ��50֡
            loops = 0;
            while (GetTickCount64() > next_game_tick && loops < MAX_FRAMESKIP)
            {
                //hh�Ĳ�������upDate_Data ÿ�벻�಻�ٵر�����50��
                upDate_data(hh);
                next_game_tick += SKIP_TICKS;
                loops++;
            }
            interpolation = float(GetTickCount64() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
            //draw
            DrawBmp(hDC,dcMEM, continue320180, hh, 320, 180,interpolation);
            break;
        }

        }
        //�������ò��˽⣬��getmessage����peekmessage��ֹ������ѭ��
        PeekMessage(&msg, NULL, 0, 0,PM_NOREMOVE);
        if(msg.message == WM_TIMER)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        //���ڴ�dc�ϵĶ���һ���Ի�����ʾdc��
        BitBlt(hDC, 0, 0, windowsLenth, windowsWidth, dcMEM, 0, 0, SRCCOPY); //�˴���һ��������ΪhDC,�����ھ��
    }
    CloseHandle(hOut);
    CloseHandle(hIn);
    DestroyWindow(hwnd);
    DeleteDC(hDC);
    DeleteDC(dcMEM);
    DestroyWindow(cmd);
    return 0;

}
void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{

    if (flag == BEFORE_START)
    {
    }
    else
    {

    }


}