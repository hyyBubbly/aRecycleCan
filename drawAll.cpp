#include<Windows.h>
#include"drawAll.h"
#include"Object.h"
extern int windowsLenth;
extern int windowsWidth;
//����֪����û�и��õĴ���������DrawBmp���أ���Ϊ��ͨ��ͼ����Ϸ�е���Ⱦ��ͼ
//��ͨ��ͼ
HDC DrawBmp(HDC hDC, HDC dcMEM, HBITMAP hBitmap, Object& object, int bmpLenth, int bmpWidth)
{
    //dcMEM�Ǻ���Ļ��ʾDC���ݵ��ڴ�DC
    HDC dcTemp;
    dcTemp = CreateCompatibleDC(hDC);//����һ���ڴ�DC
    //������hDC������ص��豸���ݵ�λͼ
    //�˴�ʹ��hDC(����DC)Createλͼ������ͼƬֻ�кڰ���ɫ
    HBITMAP bmpBackground = CreateCompatibleBitmap(hDC, windowsLenth, windowsWidth);//�����ֱ�Ϊ��hDC��λͼ����λͼ��
    //�ڴ�dcһ��(dcMEM)select����ͼƬ
    SelectObject(dcMEM, bmpBackground);
    //����delete dcTemp������������滻��hBitmap�Ļ���deleteʱ���hBitmapһ��ɾ��
    //����ֵ�Ǳ�ȡ������ľ��//����ɵľ��������ָ�ԭ״
    //�ڴ�dc����(dcTemp)selectҪ����ͼƬ
    
    HBITMAP hOldMap = (HBITMAP)SelectObject(dcTemp, hBitmap);//λͼѡ����ڴ�DC
    
    //��dcTemp���ͼ����dcMEM��
    BitBlt(dcMEM, object.getX(), object.getY(), bmpLenth, bmpWidth, dcTemp, 0, 0, SRCCOPY);
    //�ָ�ԭ״
    SelectObject(dcTemp, hOldMap);
    DeleteObject(hOldMap);
    //ɾ��dc
    DeleteDC(dcTemp);
    return dcMEM;
}

//��Ϸ�е���Ⱦ��ͼ
HDC DrawBmp(HDC hDC,HDC dcMEM, HBITMAP hBitmap, Can & can,int bmpLenth ,int bmpWidth,float interpolation)
{
    //ʵ�ֲ�ֵ(interpolation)��Ԥ��(view_Y)����
    //��ʵ�ֵ�ԭ��ʵ�����ǲ�֡���Ƚ��ܼ��̲����и��ߵ�֡�ʣ�����Ԥ��ʱ�����λͼ�����ĸ�λ��

    //���������ϵ�ʱ������move()��y�����˼�v_y��Ҫ��á����y����Ҫ��getY()���ص���ֵ��ȥv_y
    //����view_Y�Ĺ�ʽ�ǡ����y��+ �ٶȡ�ʱ���ֵ
    int view_Y;//��Ⱦ��Ԥ��y����
    if(can.direction=='W')
        view_Y = can.getY() + can.getv_y() * (interpolation - 1);
    else
        view_Y = can.getY();
    //�����������ҵ�ʱ�򣬾Ͳ�Ҫ�����в�ֵ�Ĺ�ʽ����Ϊ�����ɵ�ʱ��������ʱ�����þͻᵼ�����岻��������


    //dcMEM�Ǻ���Ļ��ʾDC���ݵ��ڴ�DC
    HDC dcTemp;
    dcTemp = CreateCompatibleDC(hDC);//����һ���ڴ�DC
    //������hDC������ص��豸���ݵ�λͼ
    //�˴�ʹ��hDC(����DC)Createλͼ������ͼƬֻ�кڰ���ɫ
    HBITMAP bmpBackground = CreateCompatibleBitmap(hDC, windowsLenth, windowsWidth);//�����ֱ�Ϊ��hDC��λͼ����λͼ��
    //�ڴ�dcһ��(dcMEM)select����ͼƬ
    SelectObject(dcMEM, bmpBackground);
    //����delete dcTemp������������滻��hBitmap�Ļ���deleteʱ���hBitmapһ��ɾ��
    //����ֵ�Ǳ�ȡ������ľ��//����ɵľ��������ָ�ԭ״
    //�ڴ�dc����(dcTemp)selectҪ����ͼƬ
    HBITMAP hOldMap=(HBITMAP)SelectObject(dcTemp, hBitmap);//λͼѡ����ڴ�DC
    //��dcTemp���ͼ����dcMEM��
    BitBlt(dcMEM, can.getX(), view_Y, bmpLenth, bmpWidth, dcTemp, 0, 0, SRCCOPY);
    //�ָ�ԭ״
    SelectObject(dcTemp, hOldMap);
    DeleteObject(hOldMap);
    //ɾ��dc
    DeleteDC(dcTemp);
    return dcMEM;
}