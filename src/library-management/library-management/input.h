#pragma once
//Kiểm tra <USERNAME> có đúng quy ước hay không?
bool TrueCharUser(char x);

//Kiểm tra <PASSWORD> có đúng quy ước hay không?
bool TrueCharPass(char x);

//Kiểm tra <FULLNAME> có đúng quy ước hay không?
bool TrueCharFullname(char x);

//Kiểm tra <CHAR> có phải kí tự số hay không?
bool TrueCharNum(char x);

//Hàm nhập <USERNAME>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputUsername(char username[]);

//Hàm nhập <PASSWORD>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputPassword(char password[]);

//Hàm nhập <FULLNAME>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputFullname(char fullname[]);

//Hàm nhập 1 số 1 hoặc 2, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int Input1Num();

//Hàm nhập 2 số, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int Input2Num();

//Hàm nhập 4 số, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int Input4Num();

//Hàm nhập 9 số, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
long Input9Num();

//Hàm nhập <ID>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputIndentity(char ID[]);

//Hàm nhập <ADDRESS>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputAddress(char address[]);

//Hàm nhập <STRING[44]>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputMoney(char string44[]);

//Hàm nhập <ISBN>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputISBN(char ISBN[]);

//Hàm nhập <STRING[100]>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputString100(char string100[]);