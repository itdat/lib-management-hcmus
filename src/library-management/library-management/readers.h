#pragma once
#include "library-management.h"
//Vẽ vùng [BOOKMENU]
void MakeFieldReadersMenu(int n);
//Hàm nhận vào loại người dùng để đưa vào [BOOKSMENU] với tính năng tương ứng
void CaseReadersMenu();
//Tạo [BOOKSMENU] di chuyển lên xuống
void MoveReadersSelect(int n, char f[10][50], char list[]);
//Bảng nhập thông tin Thêm sách mới
void InputReadersData();
//Gọi tính năng thứ <I>
void ReadersAction(int i);

//Bảng nhập thông tin Chỉnh sửa thông tin độc giả
void ModifyReadersData();

//Thao tác Xóa thông tin một độc giả theo mã độc giả
void DeleteReader();

void ViewListReaders(List_Reader L, int CurrentLine, int fullHeight);

void FullReadersInfoID(int posX, int posY, int TextColor, int BgColor, Readers reader);

void SearchReaderID();

void SearchReaderName();