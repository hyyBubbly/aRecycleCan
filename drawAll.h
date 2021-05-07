#pragma once
class Object;
class Can;
HDC DrawBmp(HDC hDC, HDC dcMEM, HBITMAP hBitmap, Object& object, int bmpLenth, int bmpWidth);
HDC DrawBmp(HDC hDC, HDC dcMEM, HBITMAP hBitmap, Can& can, int bmpLenth, int bmpWidth, float interpolation);