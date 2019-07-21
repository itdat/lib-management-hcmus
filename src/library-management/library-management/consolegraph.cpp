#include "windows.h"
#include "stdio.h"
#include "library-management.h"
#include "conio.h"
struct IMG
{
	int a[30][120];
	int width;
	int height;
};
/*
	XX --->BackgroundText
	0 black
	1 blue
	2 green
	3 aqua
	4 red
	5 purple
	6 yellow
	7 white
	8 gray
	9 light blue
	10 light green
	11 light aqua
	12 light red
	13 light purple
	14 light yellow
	15 bright white
*/


//Chỉnh kích thước màn hình console theo đơn vị pixel
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

//Đưa con trỏ đến tọa độ (x,y) trên màn hình console
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

//Chỉnh màu chữ (màu nền mặc định đen)
void textColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//Chỉnh màu chữ và màu nền
void textBgColor(int colorText, int colorBG)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (colorBG << 4) | colorText);
}

//Vẽ khung hình chữ nhật
void drawRectangleBorder(int positionX, int positionY, int width, int height, int color)
{
	textBgColor(0, color);
	for (int x = 0; x < width; x++)
	{
		gotoxy(positionX + x, positionY);
		printf("%c", ' ');
		gotoxy(positionX + x, positionY + height - 1);
		printf("%c", ' ');
	}
	for (int y = 0; y < height; y++)
	{
		gotoxy(positionX, positionY + y);
		printf("%c", ' ');
		gotoxy(positionX + width - 1, positionY + y);
		printf("%c", ' ');
	}
	gotoxy(44, 0);
	textBgColor(0, color);
}

//Vẽ hình chữ nhật
void drawRectangle(int positionX, int positionY, int width, int height, int color)
{
	textBgColor(0, color);
	gotoxy(positionX, positionY);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			gotoxy(positionX + x, positionY + y);
			printf("%c", ' ');
		}
	}
	gotoxy(44, 0);
}

//Vẽ kệ sách
void drawBookshelf(int positionX, int positionY)
{
	drawRectangle(positionX, positionY, 16, 16, 6);
	drawRectangle(positionX + 1, positionY + 1, 14, 14, 0);
	drawRectangle(positionX + 1, positionY + 2, 1, 5, 12);
	drawRectangle(positionX + 2, positionY + 2, 1, 5, 4);
	drawRectangle(positionX + 3, positionY + 3, 1, 4, 11);
	drawRectangle(positionX + 4, positionY + 2, 1, 5, 9);
	drawRectangle(positionX + 5, positionY + 2, 1, 5, 1);
	drawRectangle(positionX + 6, positionY + 1, 1, 6, 10);
	drawRectangle(positionX + 7, positionY + 1, 1, 6, 2);
	drawRectangle(positionX + 8, positionY + 3, 1, 4, 12);
	drawRectangle(positionX + 9, positionY + 3, 1, 4, 4);
	drawRectangle(positionX + 10, positionY + 5, 1, 2, 4);
	drawRectangle(positionX + 11, positionY + 2, 1, 5, 10);
	drawRectangle(positionX + 12, positionY + 2, 1, 5, 2);
	drawRectangle(positionX + 13, positionY + 3, 1, 4, 11);
	drawRectangle(positionX + 14, positionY + 3, 1, 4, 3);

	drawRectangle(positionX, positionY + 7, 16, 2, 6);

	drawRectangle(positionX + 1, positionY + 3 + 8, 1, 4, 12);
	drawRectangle(positionX + 2, positionY + 3 + 8, 1, 4, 4);
	drawRectangle(positionX + 3, positionY + 3 + 8, 1, 4, 5);
	drawRectangle(positionX + 4, positionY + 2 + 8, 1, 5, 12);
	drawRectangle(positionX + 5, positionY + 2 + 8, 1, 5, 4);
	drawRectangle(positionX + 6, positionY + 4 + 8, 1, 3, 9);
	drawRectangle(positionX + 7, positionY + 5 + 8, 1, 2, 10);
	drawRectangle(positionX + 8, positionY + 3 + 8, 1, 4, 2);
	drawRectangle(positionX + 9, positionY + 2 + 8, 1, 5, 6);
	drawRectangle(positionX + 10, positionY + 2 + 8, 1, 5, 14);
	drawRectangle(positionX + 11, positionY + 3 + 8, 1, 4, 4);
	drawRectangle(positionX + 12, positionY + 1 + 8, 1, 6, 9);
	drawRectangle(positionX + 13, positionY + 1 + 8, 1, 6, 1);
	drawRectangle(positionX + 14, positionY + 3 + 8, 1, 4, 11);
}

//Trả về tọa độ x của con trỏ vị trí hiện tại
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}

//Trả về tọa độ y của con trỏ vị trí hiện tại
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}

//Hàm vẽ nền
void SetBG()
{
	//drawRectangle(0, 0, MAXWIDTH, MAXHEIGHT, 15);
	textBgColor(0, 15);
	system("cls");
	drawBookshelf(0, 0);
	drawBookshelf(16, 0);
	drawBookshelf(88, 0);
	drawBookshelf(104, 0);
}

//Hàm vẽ [KHUNG TÊN PHẦN MỀM]
void DrawAppNameTab(int TextColor, int BgColor)
{
	drawRectangle(47, 2, 27, 3, BgColor);
	gotoxy(48, 3);
	textBgColor(TextColor, BgColor);
	printf("PHAN MEM QUAN LY THU VIEN");
}

//Hàm chào user
void GreetingUser()
{
	drawRectangle(48, 5, 29, 1, 15);
	gotoxy(48, 5);
	textBgColor(0, 15);
	FILE *f = fopen("cache/currentAccount.txt", "r");
	char username[21];
	fscanf(f, "%s", &username);
	printf("Xin chao %s", username);
}

//In tiêu đề tính năng
void Title(char title[45])
{
	drawRectangle(48, 5, 36, 1, 15);
	gotoxy(47, 5);
	textBgColor(0, 15);
	printf("%s", title);
}

void VerticalLine(int PosX, int PosY, int Length, int TextColor, int BgColor)
{
	textBgColor(TextColor, BgColor);
	for (int i = PosY; i < PosY + Length; i++)
	{
		gotoxy(PosX, i);
		printf("%c",char(179));
	}
}

void HorizontalLine(int PosX, int PosY, int Length, int TextColor, int BgColor)
{
	textBgColor(TextColor, BgColor);
	for (int i = PosX; i < PosX + Length; i++)
	{
		gotoxy(i, PosY);
		printf("%c", char(196));
	}
}

//Ẩn dấu nháy
void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize=20;
	SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &Info);
}

//Hiện dấu nháy
void Yescursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize=20;
	SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &Info);
}