#pragma once
#include "ctime"
#include "library-management.h"
// Khởi tạo thư mục
void initSystemFolder();

//Tạo đường dẫn bằng cách ghép 3 chuỗi s1+s2+s3
char *Path(char s1[], char s2[], char s3[]);

//Tạo chuỗi mã độc giả
char *toStr(long n);
int ReadNumMonth();
tm *MakeEndDay(int Date, int Month, int Year, int NumMonth);

//Trả về số lượng sách tối đa được mượn
int MaximumBooks();

//Trả về thời hạn mượn tối đa một quyển sách không tính phí
int BorrowedTimeoutExpired();

Day GetToday();