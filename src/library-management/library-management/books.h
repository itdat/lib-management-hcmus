#pragma once
//Vẽ vùng [BOOKMENU]
void MakeFieldBooksMenu(int n);

//Hàm nhận vào loại người dùng để đưa vào [BOOKSMENU] với tính năng tương ứng
void CaseBooksMenu();
//Tạo [BOOKSMENU] di chuyển lên xuống
void MoveBooksSelect(int n, char f[10][50], char list[]);
//Bảng nhập thông tin Thêm sách mới
void InputBooksData();
//Gọi tính năng thứ <I>
void BooksAction(int i);

void ViewListBooks();

//Bảng nhập thông tin Chỉnh sửa thông tin sách
void ModifyBooksData();

void DeleteBook();

void SearchBookISBN();

void SearchBookName();

