#include "stdafx.h"
#include "consolegraph.h"
#include "input.h"
#include "conio.h"
#include "books.h"
#include "function-standard.h"
#include "windows.h"
#include "cache.h"
#include "menu.h"
#include "readers.h"
#include "library-management.h"
#include "books.h"
#include "borrowed-bill.h"

int NumBookBorrowed(long code)
{
	fcloseall();
	FILE *f;
	char textcode[10];
	strcpy(textcode, toStr(code));
	char link[128];
	strcpy(link, Path("borrowedbook/", textcode, ".bin"));
	errno_t err_o = fopen_s(&f, link, "rb");
	if (err_o != 0)
	{
		return 0;
	}
	else
	{
		int count = 0;
		BorrowBook BB;
		while (fread(&BB, sizeof(BorrowBook), 1, f) != 0)
		{
			count++;
		}
		return count;
	}
}

bool CorrectBook(int numCount, char List[][14], char ISBN[])
{
	for (int i = 0; i < numCount; i++)
	{
		if (strcmp(List[i], ISBN) == 0)
			return true;
	}
	return false;
}

int numDay(int d1, int m1, int y1, int d2, int m2, int y2)
{
	tm p1;
	p1.tm_mday = d1;
	p1.tm_mon = m1 - 1;
	p1.tm_year = y1 - 1900;
	p1.tm_hour = 0;
	p1.tm_isdst = 0;
	p1.tm_min = 0;
	p1.tm_sec = 0;
	p1.tm_wday = 0;
	p1.tm_yday = 0;
	tm p2;
	p2.tm_mday = d2;
	p2.tm_mon = m2 - 1;
	p2.tm_year = y2 - 1900;
	p2.tm_hour = 0;
	p2.tm_isdst = 0;
	p2.tm_min = 0;
	p2.tm_sec = 0;
	p2.tm_wday = 0;
	p2.tm_yday = 0;

	time_t tp1 = mktime(&p1);
	time_t tp2 = mktime(&p2);
	int L = (tp1 - tp2) / 86400;
	return L;
}


void ViewRepayBill(long code)
{
	drawRectangle(20, 19, 80, 11, 7);
	gotoxy(21, 19);
	printf("MA DOC GIA: %09d", code);
	gotoxy(52, 20);
	printf("PHIEU TRA SACH");
	HorizontalLine(20, 21, 80, 15, 7);
	VerticalLine(34, 22, 7, 15, 7);
	VerticalLine(45, 22, 7, 15, 7);
	VerticalLine(77, 22, 7, 15, 7);
	VerticalLine(88, 22, 7, 15, 7);
	HorizontalLine(20, 23, 80, 15, 7);
	HorizontalLine(20, 23, 80, 15, 7);
	HorizontalLine(20, 23, 80, 15, 7);
	HorizontalLine(20, 23, 80, 15, 7);

	gotoxy(34, 21);
	printf("%c", char(194));
	gotoxy(34, 23);
	printf("%c", char(197));
	gotoxy(45, 21);
	printf("%c", char(194));
	gotoxy(45, 23);
	printf("%c", char(197));
	gotoxy(77, 21);
	printf("%c", char(194));
	gotoxy(77, 23);
	printf("%c", char(197));
	gotoxy(88, 21);
	printf("%c", char(194));
	gotoxy(88, 23);
	printf("%c", char(197));


	textBgColor(0, 7);
	gotoxy(25, 22);
	printf("ISBN");
	gotoxy(36, 22);
	printf("NGAY TRA");
	gotoxy(56, 22);
	printf("TINH TRANG");
	gotoxy(79, 22);
	printf("GIA SACH");
	gotoxy(89, 22);
	printf("THANH TOAN");
}

void RepayFormInput()
{
	//SetBG();
	DrawAppNameTab(15, 2);
	Title(">>LAP PHIEU TRA SACH");
	drawRectangle(36, 6, 48, 12, 3);

	bool BACK = false;
	drawRectangle(36, 6, 48, 7, 3);
	gotoxy(38, 7);
	printf("Nhap ma doc gia: ");

	gotoxy(38, 10);
	printf("So luong sach duoc muon: ");
	gotoxy(38, 12);
	printf("Nhap ISBN: ");
	drawRectangle(38, 8, 44, 1, 15);
	drawRectangle(38, 13, 44, 1, 15);

	HorizontalLine(38, 9, 44, 15, 3);
	HorizontalLine(38, 11, 44, 15, 3);
	Readers A;
	errno_t err;
	long cost = 0;
	//Nhập mã độc giả
	do
	{

		drawRectangle(36, 9, 48, 3, 3);
		drawRectangle(38, 8, 44, 1, 15);
		textBgColor(0, 3);
		gotoxy(38, 10);
		printf("So sach dang muon: ");
		HorizontalLine(38, 9, 44, 15, 3);
		HorizontalLine(38, 11, 44, 15, 3);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(61, 15);
		printf("ENTER to Repay a book");
		gotoxy(61, 16);
		printf("F12 to Back");
		textBgColor(0, 15);

		gotoxy(38, 8);
		A.code = Input9Num();
		if (A.code == -1)
		{
			BACK = true;
		}

		//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
		if (!BACK)
		{
			char textcode[10];
			strcpy(textcode, toStr(A.code));
			char link[128];
			strcpy(link, Path("readers/", textcode, ".bin"));

			FILE *f;
			err = fopen_s(&f, link, "rb");
			//Nếu độc giả không tồn tại trước đó
			if (err != 0)
			{
				//In thông báo
				drawRectangle(36, 9, 48, 3, 12);
				gotoxy(51, 10);
				printf("DOC GIA KHONG TON TAI");
				Sleep(1000);
			}
			//Nếu độc giả tồn tại
			else
			{
				fread(&A, sizeof(Readers), 1, f);
				fclose(f);
				fcloseall();
				textBgColor(0, 3);
				gotoxy(38, 10);
				printf("So sach dang muon: %d", NumBookBorrowed(A.code));
				HorizontalLine(38, 9, 44, 15, 3);
				HorizontalLine(38, 11, 44, 15, 3);

				ViewRepayBill(A.code);
				Books aBook;
				int CurrentLine = 24;
				//Nhập ISBN
				do
				{
					//ViewBorrowedBook(A.code);
					drawRectangle(36, 9, 48, 3, 3);
					drawRectangle(38, 13, 44, 1, 15);
					textBgColor(0, 3);
					gotoxy(38, 10);
					printf("So sach dang muon: %d", NumBookBorrowed(A.code));
					HorizontalLine(38, 9, 44, 15, 3);
					HorizontalLine(38, 11, 44, 15, 3);
					textBgColor(0, 15);

					//NHẬP ISBN
					gotoxy(38, 13);
					int status = InputISBN(aBook.ISBN);
					if (status == -1)
					{
						BACK = true;
					}
					
					//Đọc dữ liệu từ thư mục mượn sách ra 3 mảng ListBook, EndDay, StartDay
					//Số sách mượn tối đa tùy chỉnh không được vượt quá 100
					char ListBook[100][14];
					Day EndDay[100];
					Day StartDay[100];
					char textcodeA[10];
					strcpy(textcodeA, toStr(A.code));
					char linkA[128];
					strcpy(linkA, Path("borrowedbook/", textcodeA, ".bin"));
					err = fopen_s(&f, linkA, "rb");
					if (err == 0)
					{
						int i = 0;
						BorrowBook BB_2;
						while (fread(&BB_2, sizeof(BorrowBook), 1, f) != 0)
						{
							strcpy(ListBook[i], BB_2.ISBN);
							EndDay[i] = BB_2.EndDay;
							StartDay[i] = BB_2.BorrowedDay;
							i++;
						}
						fclose(f);
					}


					//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
					if (!BACK)
					{
						//Nếu ISBN đúng với ISBN đã mượn
						if (CorrectBook(NumBookBorrowed(A.code), ListBook, aBook.ISBN))
						{
							//In thông báo
							drawRectangle(36, 9, 48, 3, 2);
							gotoxy(46, 10);
							textBgColor(0, 7);
							printf("1 TRA SACH");
							gotoxy(65, 10);
							printf("2 BAO MAT");
							char ch = getch();
							
							//Xóa sách mượn trong thư mục mượn sách
							char textcode[10];
							int n = NumBookBorrowed(A.code);
							strcpy(textcode, toStr(A.code));
							fcloseall();
							int posList = -1;
							strcpy(link, Path("borrowedbook/", textcode, ".bin"));
							err = fopen_s(&f, link, "wb");
							if (err == 0)
							{
								bool Found = false;
								BorrowBook ASD;
								for (int i = 0; i < n; i++)
								{
									if (strcmp(aBook.ISBN, ListBook[i]) != 0 || Found)
									{
										strcpy(ASD.ISBN, ListBook[i]);
										ASD.BorrowedDay = StartDay[i];
										ASD.EndDay = EndDay[i];
										fwrite(&ASD, sizeof(BorrowBook), 1, f);
									}

									if (strcmp(aBook.ISBN, ListBook[i]) == 0)
									{
										Found = true;
										if (posList == -1) posList = i;
									}
								}
								fclose(f);
							}

							//Vẽ giao diện
							if (CurrentLine >= 29)
							{
								drawRectangle(20, CurrentLine, 80, 2, 7);
								VerticalLine(34, 22, 7, 15, 7);
								VerticalLine(45, 22, 7, 15, 7);
								VerticalLine(77, 22, 7, 15, 7);
								VerticalLine(88, 22, 7, 15, 7);
								textBgColor(0, 7);
							}

							//Đọc dữ liệu số lượng sách trong thư viện
							char link[128];
							strcpy(link, Path("books/", aBook.ISBN, ".bin"));
							FILE *f;
							err = fopen_s(&f, link, "rb");
							if (err == 0)
							{
								fread(&aBook, sizeof(Books), 1, f);
								fclose(f);
							}
							//In thông tin
							gotoxy(21, CurrentLine);
							printf("%s", aBook.ISBN);
							gotoxy(35, CurrentLine);
							Day NOW = GetToday();
							printf("%02d/%02d/%04d", NOW.Date, NOW.Month, NOW.Year);
							gotoxy(78, CurrentLine);
							printf("%s", aBook.prices);

							//Chức năng trả sách
							if (ch == '1')
							{
								//Tính khoảng thời gian giữa ngày trả dự kiến và thời gian hiện tại
								int LengthDay = numDay(NOW.Date, NOW.Month, NOW.Year, EndDay[posList].Date, EndDay[posList].Month, EndDay[posList].Year);
								if (LengthDay <= 0)
								{
									gotoxy(46, CurrentLine);
									printf("Tra dung thoi gian du kien");
								}
								else
								{
									gotoxy(46, CurrentLine);
									printf("Tre %d ngay so voi du kien", LengthDay);
								}
	
								//In số tiền thanh toán
								if (LengthDay > 0)
								{
									gotoxy(89, CurrentLine);
									printf("%ld", 5000 * LengthDay >= 2 * atoi(aBook.prices) ? 2 * atoi(aBook.prices) : 5000 * LengthDay);
									5000 * LengthDay >= 2 * atoi(aBook.prices) ? cost += 2 * atoi(aBook.prices) : cost += 5000 * LengthDay;
								}
								else
								{
									gotoxy(89, CurrentLine);
									printf("0");
								}

								//Tăng số lượng sách trong thư viện nếu số tiền nộp phạt chưa quá 200% hoặc trả đúng hạn
								if ((LengthDay > 0 && (5000 * LengthDay < 2 * atoi(aBook.prices))) || LengthDay <= 0)
								{
									//Cập nhật số lượng
									aBook.number++;
									//Ghi dữ liệu sách
									err = fopen_s(&f, link, "wb");
									if (err == 0)
									{
										fwrite(&aBook, sizeof(Books), 1, f);
										fclose(f);
									}
								}
								CurrentLine++;
							}
							//Chức năng mất sách
							else if (ch == '2')
							{
								gotoxy(46, CurrentLine);
								printf("Mat sach");
								gotoxy(89, CurrentLine);
								printf("%ld", 2 * atoi(aBook.prices));
								cost += 2 * atoi(aBook.prices);
								CurrentLine++;
							}
							//In tổng tiền
							if (CurrentLine <= 29)
							{
								gotoxy(21, 29);
								printf("TONG CONG: %d VND", cost);
							}
							else
							{
								gotoxy(21, CurrentLine);
								printf("TONG CONG: %d VND", cost);
							}
						}
						else
						{
							//In thông báo
							drawRectangle(36, 9, 48, 3, 12);
							gotoxy(50, 10);
							printf("ISBN KHONG CHINH XAC");
							Sleep(1000);
						}
					}
					//Nếu bấm 'Trở về'
					else
					{
						//Trở về Menu
						int n;
						char list[10];
						SetBG();
						ReadMenuData(n, list);
						Menu(n, list);
						break;
					}

				} while (!BACK);
			}
		}
		//Nếu bấm 'Trở về'
		else
		{
			//Trở về BooksMenu
			int n;
			char list[10];
			drawRectangle(36, 10, 48, 21, 15);
			ReadMenuData(n, list);
			Menu(n, list);
			break;
		}
	} while (!BACK);
}