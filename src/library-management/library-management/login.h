#pragma once
//Hàm tạo giao diện đăng nhập cho người dùng
void LayoutLogin(char username[], char password[]);

//Hàm trả về loại người dùng, -1 nếu <USERNAME> hoặc <PASSWORD> không chính xác
int Login(char username[], char password[]);

//Hàm nhận vào loại người dùng để đưa vào [MENU] với tính năng tương ứng
void CaseLogin(int n);

//Lặp lại bước nhập <USERNAME> và <PASSWORD> đến khi nào đăng nhập thành công hoặc ấn phím [ESC]
void RepeatInput(char username[], char password[]);

//Đăng xuất
void LogOut();