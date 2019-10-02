#include <stdio.h>
#include <windows.h>

//��һ��������Ҫ���Ƶ��ַ���
//�ڶ��������������С
//���ʵ����������С����������̫����ʾ����
void ShowText(const TCHAR* str, int fontSize)
{
	//�����ڴ�DC
	HDC hdc = GetDC(NULL);
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, 200, 200);
	SelectObject(hdcMem, hBitmap);
	DeleteObject(hBitmap);


	//���ñ�����ɫ��������ɫ
	SetBkColor(hdcMem, RGB(0, 0, 0));
	SetTextColor(hdcMem, RGB(255, 255, 255));

	//��������
	HFONT hFont = CreateFont(
		-fontSize,
		0,
		0,
		0,
		FW_SEMIBOLD,
		FALSE,
		FALSE,
		0,
		GB2312_CHARSET,
		OUT_DEFAULT_PRECIS,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		TEXT("΢���ź�"));
	SelectObject(hdcMem, hFont);

	//���ڴ�DC�ϻ�������
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 0;
	int height = DrawText(hdcMem, str, -1, &rect, DT_CALCRECT);
	rect.bottom = height;
	DrawText(hdcMem, str, -1, &rect, DT_LEFT);

	//��������
	DeleteObject(hFont);

	//��ȡ����λͼ�������������������������̨
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < rect.right; ++x)
		{
			COLORREF color = GetPixel(hdcMem, x, y);
			if ((int)GetRValue(color) == 255)
			{
				printf("* ");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}

	//�ͷ�DC
	DeleteDC(hdcMem);
	ReleaseDC(NULL, hdc);
}

int main()
{
	ShowText(TEXT("���\n����\nHello\nworld"), 20);

	return 0;
}