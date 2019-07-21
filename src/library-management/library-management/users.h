#pragma once
//Cho biết <USERNAME> có khả dụng cho việc tạo mới hay không?
bool AcceptUser(char username[]);

//Thêm Account
void AddAccount(Accounts A);

//Bảng nhập thông tin Tạo người dùng mới
void InputUserData();

//Hàm trả về dữ liệu tài khoản theo đường dẫn <LINK>
Accounts ReadAccount(char link[]);

//Viết dữ liệu <USER> vào file với đường dẫn <LINK>
int WriteAccount(char link[], Accounts user);

//Thay đổi mật khẩu
void ChangePassword();

//Chỉnh sửa thông tin
void ModifyInfo();