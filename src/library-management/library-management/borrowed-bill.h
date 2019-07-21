#pragma once
bool ReaderInUse(int Date, int Month, int Year);

//Trả về số lượng sách còn có thể mượn
int BookCanBorrowed(long code);

Day BorrDayTimeoutEx(int Date, int Month, int Year);

void BorrowedFormInput();

void ViewBorrowedBook(long code);