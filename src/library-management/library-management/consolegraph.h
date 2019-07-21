//Chỉnh kích thước màn hình console theo đơn vị pixel
void resizeConsole(int width, int height);

//Đưa con trỏ đến tọa độ (x,y) trên màn hình console
void gotoxy(int x, int y);

//Chỉnh màu chữ (màu nền mặc định đen)
void textColor(int color);

//Chỉnh màu chữ và màu nền
void textBgColor(int colorText, int colorBG);

//Vẽ khung hình chữ nhật
void drawRectangleBorder(int positionX, int positionY, int width, int height, int color);

#pragma once
//Vẽ hình chữ nhật
void drawRectangle(int positionX, int positionY, int width, int height, int color);

//Vẽ kệ sách
void drawBookshelf(int positionX, int positionY);

//Trả về tọa độ x của con trỏ vị trí hiện tại
int whereX();

//Trả về tọa độ y của con trỏ vị trí hiện tại
int whereY();

//Hàm vẽ nền
void SetBG();

//Hàm vẽ [KHUNG TÊN PHẦN MỀM]
void DrawAppNameTab(int TextColor, int BgColor);

//In tiêu đề tính năng
void Title(char title[45]);

void VerticalLine(int PosX, int PosY, int Length, int TextColor, int BgColor);

void HorizontalLine(int PosX, int PosY, int Length, int TextColor, int BgColor);

//Ẩn dấu nháy
void Nocursortype();

//Hiện dấu nháy
void Yescursortype();