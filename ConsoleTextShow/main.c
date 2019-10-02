#include <stdio.h>
#include <windows.h>

//第一个参数：要绘制的字符串
//第二个参数：字体大小
//请适当调整字体大小，以免字体太大显示不完
void ShowText(const TCHAR* str, int fontSize)
{
	//创建内存DC
	HDC hdc = GetDC(NULL);
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, 200, 200);
	SelectObject(hdcMem, hBitmap);
	DeleteObject(hBitmap);


	//设置背景颜色和字体颜色
	SetBkColor(hdcMem, RGB(0, 0, 0));
	SetTextColor(hdcMem, RGB(255, 255, 255));

	//设置字体
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
		TEXT("微软雅黑"));
	SelectObject(hdcMem, hFont);

	//在内存DC上绘制文字
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 0;
	int height = DrawText(hdcMem, str, -1, &rect, DT_CALCRECT);
	rect.bottom = height;
	DrawText(hdcMem, str, -1, &rect, DT_LEFT);

	//销毁字体
	DeleteObject(hFont);

	//读取文字位图，并根据文字轮廓输出到控制台
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

	//释放DC
	DeleteDC(hdcMem);
	ReleaseDC(NULL, hdc);
}

int main()
{
	ShowText(TEXT("你好\n世界\nHello\nworld"), 20);

	return 0;
}