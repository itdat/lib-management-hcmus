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

bool ReaderInUse(int Date, int Month, int Year)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	//Năm hiện tại nhỏ hơn
	if (ltm->tm_year + 1900 < Year)
	{
		return true;
	}
	else
		//Năm hiện tại lớn hơn
		if (ltm->tm_year +1900 > Year)
		{
			return false;
		}
		else
			//Năm hiện tại bằng
		{
			//Tháng hiện tại nhỏ hơn
			if (ltm->tm_mon + 1 < Month)
			{
				return true;
			}
			else
				//Tháng hiện tại lớn hơn
				if (ltm->tm_mon + 1 > Month)
				{
					return false;
				}
				else
					//Tháng hiện tại bằng
				{
					if (ltm->tm_mday <= Date)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
		}
}

//Trả về số lượng sách còn có thể mượn
int BookCanBorrowed(long code)
{
	FILE *f;
	char textcode[10];
	strcpy(textcode, toStr(code));
	char link[128];
	strcpy(link, Path("borrowedbook/", textcode, ".bin"));
	errno_t err_o = fopen_s(&f, link, "rb");
	if (err_o != 0)
	{
		return MaximumBooks();
	}
	else
	{
		int count = 0;
		BorrowBook BB;
		while (fread(&BB, sizeof(BorrowBook), 1, f) != 0)
		{
			count++;
		}
		if (MaximumBooks() - count > 0)
		{
			return MaximumBooks() - count;
		}
		return 0;
	}
}

void ViewBorrowedBook(long code)
{
	drawRectangle(20, 19, 80, 11, 7);
	gotoxy(21, 19);
	printf("MA DOC GIA: %09d", code);
	gotoxy(52, 20);
	printf("PHIEU MUON SACH");
	HorizontalLine(20, 21, 80, 15, 7);
	VerticalLine(34, 22, 7, 15, 7);
	VerticalLine(84, 22, 7, 15, 7);
	gotoxy(34, 21);
	printf("%c", char(194));
	gotoxy(84, 21);
	printf("%c", char(194));
	HorizontalLine(20, 23, 80, 15, 7);
	gotoxy(34, 23);
	printf("%c", char(197));
	gotoxy(84, 23);
	printf("%c", char(197));
	textBgColor(0, 7);
	gotoxy(25, 22);
	printf("ISBN");
	gotoxy(55, 22);
	printf("TEN SACH");
	gotoxy(88, 22);
	printf("NGAY MUON");
	
	int CurrentLine = 24; //<29
	FILE *f;
	char textcode[10];
	strcpy(textcode, toStr(code));
	char link[128];
	strcpy(link, Path("borrowedbook/", textcode, ".bin"));
	errno_t err_o = fopen_s(&f, link, "rb");
	if (err_o == 0)
	{
		BorrowBook BB;
		while (fread(&BB, sizeof(BorrowBook), 1, f) != 0)
		{
			if (CurrentLine >= 29)
			{
				drawRectangle(20, CurrentLine, 80, 2, 7);
				VerticalLine(34, CurrentLine, 1, 15, 7);
				VerticalLine(84, CurrentLine, 1, 15, 7);
				textBgColor(0, 7);
			}
			gotoxy(21, CurrentLine);
			printf("%s", BB.ISBN);

			gotoxy(87, CurrentLine);
			printf("%02d/%02d/%04d", BB.BorrowedDay.Date, BB.BorrowedDay.Month, BB.BorrowedDay.Year);

			Books tmp_book;
			FILE *g;
			char link[128];
			strcpy(link, Path("books/", BB.ISBN, ".bin"));
			errno_t error = fopen_s(&g, link, "rb");
			if (error == 0)
			{
				fread(&tmp_book, sizeof(Books), 1, g);
				fclose(g);
				gotoxy(35, CurrentLine);

				if (strlen(tmp_book.name) <= 49)
				{
					gotoxy(35, CurrentLine);
					printf("%s", tmp_book.name);
				}
				else
				{
					gotoxy(35, CurrentLine);
					char name[47];
					name[46] = '\0';
					strncpy(name,tmp_book.name, 56);
					printf("%s", name);
					printf("...");
				}
			}
			CurrentLine++;

		}
		fclose(f);
	}
}

Day BorrDayTimeoutEx(int Date, int Month, int Year)
{
	tm created;
	created.tm_mday = Date + BorrowedTimeoutExpired();
	created.tm_mon = Month - 1;
	created.tm_year = Year - 1900;
	created.tm_hour = 0;
	created.tm_isdst = 0;
	created.tm_min = 0;
	created.tm_sec = 0;
	created.tm_wday = 0;
	created.tm_yday = 0;
	time_t endtime = mktime(&created);
	tm *ended = localtime(&endtime);
	Day Timeout;
	Timeout.Date = ended->tm_mday;
	Timeout.Month = ended->tm_mon + 1;
	Timeout.Year = ended->tm_year + 1900;
	return Timeout;
}

void BorrowedFormInput()
{
	//SetBG();
	DrawAppNameTab(15, 2);
	Title(">>LAP PHIEU MUON SACH");
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

	//Nhập mã độc giả
	do
	{

		drawRectangle(36, 9, 48, 3, 3);
		drawRectangle(38, 8, 44, 1, 15);
		textBgColor(0, 3);
		gotoxy(38, 10);
		printf("So luong sach duoc muon: ");
		HorizontalLine(38, 9, 44, 15, 3);
		HorizontalLine(38, 11, 44, 15, 3);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(60, 15);
		printf("ENTER to Borrow a book");
		gotoxy(60, 16);
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
			strcpy(textcode,toStr(A.code));
			char link[128];
			strcpy(link,Path("readers/", textcode, ".bin"));

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
				//Nếu tài khoản còn hạn sử dụng
				if (ReaderInUse(A.expirationDay.Date, A.expirationDay.Month, A.expirationDay.Year))
				{
					textBgColor(0, 3);
					gotoxy(38, 10);
					printf("So luong sach duoc muon: %d", BookCanBorrowed(A.code));
					HorizontalLine(38, 9, 44, 15, 3);
					HorizontalLine(38, 11, 44, 15, 3);
					Books aBook;
					//Nhập ISBN
					do
					{
						ViewBorrowedBook(A.code);

						drawRectangle(36, 9, 48, 3, 3);
						drawRectangle(38, 13, 44, 1, 15);
						textBgColor(0, 3);
						gotoxy(38, 10);
						printf("So luong sach duoc muon: %d", BookCanBorrowed(A.code));
						HorizontalLine(38, 9, 44, 15, 3);
						HorizontalLine(38, 11, 44, 15, 3);
						textBgColor(0, 15);

						gotoxy(38, 13);
						int status = InputISBN(aBook.ISBN);
						if (status == -1)
						{
							BACK = true;
						}
						//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
						if (!BACK)
						{
							char link[128];
							strcpy(link, Path("books/", aBook.ISBN, ".bin"));
							FILE *f;
							err = fopen_s(&f, link, "rb");
							//Nếu sách tồn tại trước đó
							if (err == 0)
							{
								fread(&aBook, sizeof(Books), 1, f);
								fclose(f);
								fcloseall();
								//Nếu sách chưa bị xóa
								if (aBook.exist)
								{
									//Nếu số lượng sách còn lớn hơn 0
									if (aBook.number > 0)
									{
										if (BookCanBorrowed(A.code) > 0)
										{
											aBook.number--;
											errno_t err_x = fopen_s(&f, link, "wb");
											if (err_x == 0)
											{
												fwrite(&aBook, sizeof(Books), 1, f);
												fclose(f);
											}

											BorrowBook BB;
											strcpy(BB.ISBN, aBook.ISBN);
											BB.BorrowedDay = GetToday();
											BB.EndDay = BorrDayTimeoutEx(BB.BorrowedDay.Date, BB.BorrowedDay.Month, BB.BorrowedDay.Year);
											fcloseall();
											char textcode[10];
											strcpy(textcode, toStr(A.code));
											char linkBB[128];
											strcpy(linkBB, Path("borrowedbook/", textcode, ".bin"));
											err_x = fopen_s(&f, linkBB, "ab");
											if (err_x == 0)
											{
												fwrite(&BB, sizeof(BorrowBook), 1, f);
												fclose(f);
											}

											//In thông báo
											drawRectangle(36, 9, 48, 3, 2);
											gotoxy(52, 10);
											printf("MUON THANH CONG");
											Sleep(1000);
										}
										else
										{
											//In thông báo
											drawRectangle(36, 9, 48, 3, 12);
											gotoxy(47, 10);
											printf("SO SACH CO THE MUON DA HET");
											Sleep(1000);
										}
									}
									else
									{
										//In thông báo
										drawRectangle(36, 9, 48, 3, 12);
										gotoxy(54, 10);
										printf("SACH DA HET");
										Sleep(1000);
									}
								}
								//Nếu sách đã bị xóa
								else
								{
									//In thông báo
									drawRectangle(36, 9, 48, 3, 12);
									gotoxy(51, 10);
									printf("SACH KHONG TON TAI");
									Sleep(1000);
								}
							}
							//Nếu sách chưa tồn tại trước đó
							else
							{
								//In thông báo
								drawRectangle(36, 9, 48, 3, 12);
								gotoxy(51, 10);
								printf("SACH KHONG TON TAI");
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
				//Tài khoản hết hạn sử dụng
				else
				{
					//In thông báo
					drawRectangle(36, 9, 48, 3, 12);
					gotoxy(52, 10);
					printf("DOC GIA HET HAN SU DUNG");
					Sleep(1000);
				}
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