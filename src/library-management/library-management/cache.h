#pragma once
//Ghi vào cache Tài khoản và mật khẩu đăng nhập hiện hành
void WriteCacheAccount(char username[], char password[]);

//Đọc từ cache Tài khoản và mật khẩu đăng nhập hiện hành
int ReadCacheAccount(char username[], char password[]);

//Hàm trả về phân quyền của tài khoản hiện tại
int ReadClassification();

//Đọc từ cache định dạng [MENU]
void ReadMenuData(int &n, char list[]);

//Đọc từ cache định dạng [BOOKSMENU]
void ReadBooksMenuData(int &n, char list[]);

//Đọc từ cache định dạng [READERSMENU]
void ReadReadersMenuData(int &n, char list[]);