#include "stdio.h"
#include "conio.h"
#include "windows.h"
#include "consolegraph.h"
#include "menu.h"
#include "stdlib.h"
#include "login.h"
#include "string.h"
#include "library-management.h"
#include "cache.h"
#include "users.h"
#include "readers.h"
#include "input.h"
#include "ctime"
#include "function-standard.h"
#include "linked-list-readers.h"

//Vẽ vùng [BOOKMENU]
void MakeFieldReadersMenu(int n)
{
	DrawAppNameTab(15, 2);

	Title(">>QUAN LI DOC GIA");

	//Xóa khung Main Menu
	drawRectangle(36, 6, 48, 9, 15);

	//Vẽ khung menu
	drawRectangle(36, 6, 48, n, 3);
}

//Gọi tính năng thứ <I>
void ReadersAction(int i)
{
	switch (i)
	{
	case 0:
		List_Reader L = GetReadersData();
		ViewListReaders(L, 6, 10);
		break;
	case 1:
		InputReadersData();
		break;
	case 2:
		ModifyReadersData();
		break;
	case 3:
		DeleteReader();
		break;
	case 4:
		SearchReaderID();
		break;
	case 5:
		SearchReaderName();
		break;
	default:
		break;
	}
}

//Tạo [READERSMENU] di chuyển lên xuống
void MoveReadersSelect(int n, char f[10][50], char list[])
{
	//Default
	int CurrentSelect = 0, CurrentLine = 6;
	drawRectangle(36, CurrentLine, 48, 1, 1);
	textBgColor(15, 1);
	gotoxy(47, 6);
	PrintFeature(f[0]);
	/*
	#UP: 72
	#DOWN: 80
	*/
	char ch = getch();
	while (ch != 27)	//ESC
	{
		//UP
		if ((ch == 72) && (CurrentSelect>0))
		{
			drawRectangle(36, CurrentLine, 48, 1, 3);
			textBgColor(0, 3);
			gotoxy(47, CurrentLine);
			PrintFeature(f[CurrentSelect]);

			CurrentSelect--;
			CurrentLine--;

			drawRectangle(36, CurrentLine, 48, 1, 1);
			textBgColor(15, 1);
			gotoxy(47, CurrentLine);
			PrintFeature(f[CurrentSelect]);
		}
		//DOWN
		if ((ch == 80) && (CurrentSelect<n - 1))
		{
			drawRectangle(36, CurrentLine, 48, 1, 3);
			textBgColor(0, 3);
			gotoxy(47, CurrentLine);
			PrintFeature(f[CurrentSelect]);

			CurrentSelect++;
			CurrentLine++;

			drawRectangle(36, CurrentLine, 48, 1, 1);
			textBgColor(15, 1);
			gotoxy(47, CurrentLine);
			PrintFeature(f[CurrentSelect]);
		}
		//ENTER
		if (ch == 13)
		{
			int count = -1;
			for (int i = 0; i < strlen(list); i++)
			{
				if (list[i] == '1')
					count++;
				if (count == CurrentSelect)
				{
					ReadersAction(i);
					break;
				}
			}
		}

		if (ch == -122) //F12
		{
			int n;
			char list[10];
			ReadMenuData(n, list);
			Menu(n, list);
			break;
		}
		if (ch == 13) break;
		ch = getch();
	}
}

//In ra [READERSMENU] với số lượng <countFeatures> tính năng và danh sách <list> các tính năng
void ReadersMenu(int countFeatures, char list[])
{
	/*
	countFeatures <= 10
	list = "xxxxxxxxxx'
	x = 1 : show feature
	x = 0 : hide feature
	*/
	Nocursortype();
	char f[10][50] =
	{
		"Xem danh sach cac doc gia",
		"Them doc gia",
		"Chinh sua thong tin doc gia",
		"Xoa thong tin doc gia",
		"Tim kiem doc gia theo CMND",
		"Tim kiem doc gia theo ten",
	};
	MakeFieldReadersMenu(countFeatures);
	int line = 6;
	char fUse[10][50];
	int i = 0;
	for (int fe = 0; fe < 10; fe++)
	{
		if (list[fe] == '1')
		{
			strcpy(fUse[i++], f[fe]);
			gotoxy(47, line);
			line++;
			PrintFeature(f[fe]);
		}
	}
	MoveReadersSelect(countFeatures, fUse, list);
	gotoxy(44, 0);
}

//Hàm nhận vào loại người dùng để đưa vào [READERSMENU] với tính năng tương ứng
void CaseReadersMenu()
{
	int n = ReadClassification();
	FILE *f = fopen("cache/currentReadersMenu.txt", "w");	//Viết vào cache trạng thái Readers menu
	switch (n)
	{
	case 1:	//admin
		fprintf(f, "%d %s", 6, "111111");
		fclose(f);
		ReadersMenu(6, "111111");
		break;
	case 2:	//manager
		fprintf(f, "%d %s", 6, "111111");
		fclose(f);
		ReadersMenu(6, "111111");
		break;
	case 3:	//expert
		fprintf(f, "%d %s", 5, "111011");
		fclose(f);
		ReadersMenu(5, "111011");
		break;
	default:
		break;
	};
}

//Bảng nhập thông tin Thêm độc giả mới
void InputReadersData()
{
	bool BACK = false;	//Biến kiểm tra có bấm 'Trở về' [F12] hay chưa?

	//SetBG();
	//Khung tên phần mềm nền xanh
	drawRectangle(47, 2, 27, 3, 2);
	gotoxy(48, 3);
	printf("PHAN MEM QUAN LY THU VIEN");
	Title(">>THEM DOC GIA MOI");

	do
	{
		//Vẽ khung đăng nhập
		drawRectangle(36, 6, 48, 23, 3);
		//Ghi các thuộc tính của trường nhập
		gotoxy(38, 7);
		printf("Ma doc gia: ");
		gotoxy(38, 9);
		printf("Ho va ten[44]: ");
		gotoxy(38, 11);
		printf("CMND[44]: ");
		gotoxy(38, 13);
		printf("Ngay sinh: dd/mm/yyyy");
		gotoxy(38, 15);
		printf("Gioi tinh: 1->Nam ; 2-> Nu");
		gotoxy(38, 17);
		printf("Email[44]: ");
		gotoxy(38, 19);
		printf("Dia chi[100]: ");
		gotoxy(38, 21);
		printf("Ngay lap the: ");
		gotoxy(38, 23);
		printf("Ngay het han: ");
		//Vẽ khung input
		FILE *f;
		long code;
		Readers A;
		errno_t err = fopen_s(&f, "readers/List.tdat", "rb");
		if (err != 0)
		{
			code = 1;
		}
		else
		{
			fread(&code, sizeof(long), 1, f);
			fclose(f);
			code++;
		}

		drawRectangle(38, 8, 44, 1, 15);
		gotoxy(38, 8);
		printf("%09ld", code);
		drawRectangle(38, 10, 44, 1, 15);
		drawRectangle(38, 12, 44, 1, 15);
		drawRectangle(38, 14, 44, 1, 15);
		gotoxy(40, 14);
		printf("/  /");
		drawRectangle(38, 16, 44, 1, 15);
		drawRectangle(38, 18, 44, 1, 15);
		drawRectangle(38, 20, 44, 1, 15);
		drawRectangle(38, 22, 44, 1, 15);
		drawRectangle(38, 24, 44, 1, 15);
		gotoxy(38, 22);
		time_t now = time(0);
		tm *ltm = localtime(&now);
		printf("%02d/%02d/%04d", ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
		A.createdDay.Date = ltm->tm_mday;
		A.createdDay.Month = ltm->tm_mon + 1;
		A.createdDay.Year = ltm->tm_year + 1900;

		int NumMonth = ReadNumMonth();
		tm *endDay = MakeEndDay(ltm->tm_mday, ltm->tm_mon, ltm->tm_year, NumMonth);
		gotoxy(38, 24);
		printf("%02d/%02d/%04d", endDay->tm_mday, 1 + endDay->tm_mon, 1900 + endDay->tm_year);
		A.expirationDay.Date = endDay->tm_mday;
		A.expirationDay.Month = endDay->tm_mon + 1;
		A.expirationDay.Year = endDay->tm_year + 1900;

		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(61, 26);
		printf("ENTER to Add a reader");
		gotoxy(61, 27);
		printf("F12 to Back");
		textBgColor(0, 15);

		//Nhập
		A.code = code;
		//Nhập Họ và tên
		if (!BACK)
		{
			do
			{
				gotoxy(38, 10);
				int status = InputFullname(A.fullname);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.fullname) == 0 && !BACK);
		}
		//Nhập CMND
		if (!BACK)
		{
			do
			{
				gotoxy(38, 12);
				int status = InputIndentity(A.ID);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.ID) == 0 && !BACK);
		}
		//Nhập Ngày sinh
		if (!BACK)
		{
			do {
				gotoxy(38, 14);
				A.DoB.Date = Input2Num();
				if (A.DoB.Date == -1)
				{
					BACK = true;
				}
			} while (A.DoB.Date == 0 && !BACK);
		}
		if (!BACK)
		{
			do
			{
				gotoxy(41, 14);
				A.DoB.Month = Input2Num();
				if (A.DoB.Month == -1)
				{
					BACK = true;
				}
			} while (A.DoB.Month == 0 && !BACK);
		}
		if (!BACK)
		{
			do
			{
				gotoxy(44, 14);
				A.DoB.Year = Input4Num();
				if (A.DoB.Year == -1)
				{
					BACK = true;
				}
			} while (A.DoB.Year == 0 && !BACK);
		}
		//Nhập Giới tính
		if (!BACK)
		{
			gotoxy(38, 16);
			A.sex = Input1Num();
			if (A.sex == -1)
			{
				BACK = true;
			}
		}
		//Nhập Email
		if (!BACK)
		{
			do
			{
				gotoxy(38, 18);
				int status = InputString100(A.email);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.email) == 0 && !BACK);
		}
		//Nhập Địa chỉ
		if (!BACK)
		{
			do
			{
				gotoxy(38, 20);
				int status = InputAddress(A.address);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.address) == 0 && !BACK);
		}

		int n;
		char list[11];
		ReadReadersMenuData(n, list);

		//Nếu chưa ấn 'Trở về' [F12]
		if (!BACK)
		{
			char textcode[10];
			strcpy(textcode, toStr(code));
			char link[128];
			strcpy(link, Path("readers/", textcode, ".bin"));
			errno_t err = fopen_s(&f, link, "wb");
			if (err == 0)
			{
				fwrite(&A, sizeof(Readers), 1, f);
				fclose(f);
			}
			err = fopen_s(&f, "readers/List.tdat", "wb");
			if (err == 0)
			{
				fwrite(&A.code, sizeof(long), 1, f);
				fclose(f);
			}

			drawRectangle(36, 12, 48, 3, 10);
			char Alert[100] = "THEM DOC GIA THANH CONG";
			gotoxy(36 + (48 - strlen(Alert)) / 2, 13);
			printf("%s", Alert);
			//Ngưng chương trình 1s để người dùng đọc thông báo
			Sleep(1000);
		}
		//Nếu đã ấn 'Trở về' [F12]
		else
		{
			SetBG();
			ReadersMenu(n, list);
			break;
		}
	} while (!BACK);
	gotoxy(44, 0);
}

//Bảng nhập thông tin Chỉnh sửa thông tin độc giả
void ModifyReadersData()
{
	Yescursortype();
	errno_t err = 1;
	bool BACK = false;	//Biến kiểm tra có bấm 'Trở về' [F12] hay chưa?
	Title(">>CHINH SUA THONG TIN DOC GIA");
	do
	{
		drawRectangle(36, 6, 48, 19, 3);
		//Ghi các thuộc tính của trường nhập
		gotoxy(38, 7);
		printf("Nhap ma doc gia: ");
		gotoxy(38, 9);
		printf("Ten doc gia[44]: ");
		gotoxy(38, 11);
		printf("CMND[44]: ");
		gotoxy(38, 13);
		printf("Ngay sinh: ");
		gotoxy(38, 15);
		printf("Gioi tinh: 1->Nam ; 2-> Nu");
		gotoxy(38, 17);
		printf("Email[100]: ");
		gotoxy(38, 19);
		printf("Dia chi[100]: ");
		//Vẽ khung input
		drawRectangle(38, 8, 44, 1, 15);
		drawRectangle(38, 10, 44, 1, 15);
		drawRectangle(38, 12, 44, 1, 15);
		drawRectangle(38, 14, 44, 1, 15);
		gotoxy(38, 14);
		printf("  /  /");
		drawRectangle(38, 16, 44, 1, 15);
		drawRectangle(38, 18, 44, 1, 15);
		drawRectangle(38, 20, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(58, 22);
		printf("ENTER to Modify a reader");
		gotoxy(58, 23);
		printf("F12 to Back");
		textBgColor(0, 15);

		//Nhập
		Readers A;
		
		//Nhập Mã độc giả
		do
		{
			drawRectangle(36, 9, 48, 3, 3);
			gotoxy(38, 9);
			printf("Ten doc gia[44]: ");
			gotoxy(38, 11);
			printf("CMND[44]: ");
			drawRectangle(38, 8, 44, 1, 15);
			drawRectangle(38, 10, 44, 1, 15);
			gotoxy(38, 8);
			A.code = Input9Num();
			if (A.code == -1)
			{
				BACK = true;
			}
			//In thông tin hiện hành nếu mã độc giả khả dụng hoặc thông báo nếu không khả dụng
			if (!BACK)
			{
				char textcode[10];
				strcpy(textcode, toStr(A.code));
				char link[128];
				strcpy(link, Path("readers/", textcode, ".bin"));

				FILE *f;
				err = fopen_s(&f, link, "rb");
				//Nếu nếu độc giả tồn tại
				if (err == 0)
				{
					Readers reader;
					fread(&reader, sizeof(Readers), 1, f);
					fclose(f);
					textBgColor(0, 3);

					//In họ tên hiện tại
					gotoxy(55, 9);
					if (strlen(reader.fullname) <= 27)
					{
						printf("%s", reader.fullname);
					}
					else
					{
						char fullname[25];
						fullname[24] = '\0';
						strncpy(fullname, reader.fullname, 24);
						printf("%s", fullname);
						printf("...");
					}
					//In CMND hiện tại
					gotoxy(48, 11);
					if (strlen(reader.ID) <= 34)
					{
						printf("%s", reader.ID);
					}
					else
					{
						char ID[32];
						ID[31] = '\0';
						strncpy(ID, reader.ID, 31);
						printf("%s", ID);
						printf("...");
					}
					//In Ngày sinh hiện tại
					gotoxy(49, 13);
					printf("%02d/%02d/%04d", reader.DoB.Date, reader.DoB.Month, reader.DoB.Year);
					//In Giới tính
					gotoxy(65, 15);
					if (reader.sex == 1)
					{
						printf("(Nam)");
					}
					else
						if (reader.sex == 2)
						{
							printf("(Nu)");
						}
						else
						{
							printf("(Khac)");
						}
					//In Email hiện tại
					gotoxy(50, 17);
					if (strlen(reader.email) <= 32)
					{
						printf("%s", reader.email);
					}
					else
					{
						char email[30];
						email[29] = '\0';
						strncpy(email, reader.email, 29);
						printf("%s", email);
						printf("...");
					}

					gotoxy(52, 19);
					if (strlen(reader.address) <= 30)
					{
						printf("%s", reader.address);
					}
					else
					{
						char address[28];
						address[27] = '\0';
						strncpy(address, reader.address, 27);
						printf("%s", address);
						printf("...");
					}

					textBgColor(0, 15);
				}
				//Nếu nếu độc giả không tồn tại
				else
				{
					drawRectangle(36, 9, 48, 3, 12);
					gotoxy(51, 10);
					printf("DOC GIA KHONG TON TAI");
					Sleep(1000);
				}
			}

		} while ((A.code == 0 || err != 0) && !BACK);
		//Nhập Họ và tên
		if (!BACK)
		{
			gotoxy(38, 10);
			int status = InputFullname(A.fullname);
			if (status == -1)
			{
				BACK = true;	//Đã bấm 'Trở về' [F12]
			}
		}
		//Nhập CMND
		if (!BACK)
		{
			gotoxy(38, 12);
			int status = InputIndentity(A.ID);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Ngày sinh
		if (!BACK)
		{
			gotoxy(38, 14);
			A.DoB.Date = Input2Num();
			if (A.DoB.Date == -1)
			{
				BACK = true;
			}
		}
		if (!BACK)
		{
			gotoxy(41, 14);
			A.DoB.Month = Input2Num();
			if (A.DoB.Month == -1)
			{
				BACK = true;
			}
		}
		if (!BACK)
		{
			gotoxy(44, 14);
			A.DoB.Year = Input4Num();
			if (A.DoB.Year == -1)
			{
				BACK = true;
			}
		}
		//Nhập Giới tính
		if (!BACK)
		{
			gotoxy(38, 16);
			A.sex = Input1Num();
			if (A.sex == -1)
			{
				BACK = true;
			}
		}
		//Nhập Email
		if (!BACK)
		{
			gotoxy(38, 18);
			int status = InputString100(A.email);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Địa chỉ
		if (!BACK)
		{
			gotoxy(38, 20);
			int status = InputAddress(A.address);
			if (status == -1)
			{
				BACK = true;
			}
		}

		int n;
		char list[11];
		ReadReadersMenuData(n, list);

		//Nếu chưa ấn 'Trở về' [F12]
		if (!BACK)
		{
			char textcode[10];
			strcpy(textcode, toStr(A.code));
			char link[128];
			strcpy(link, Path("readers/", textcode, ".bin"));
			FILE *f;
			Readers B;
			errno_t err_2 = fopen_s(&f, link, "rb");
			if (err_2 == 0)
			{
				fread(&B, sizeof(Readers), 1, f);
				fclose(f);
			}

			if (strlen(A.fullname) != 0)
				strcpy(B.fullname, A.fullname);
			if (strlen(A.ID) != 0)
				strcpy(B.ID, A.ID);
			if (A.DoB.Date != 0 && A.DoB.Month != 0 && A.DoB.Year != 0)
			{
				B.DoB.Date = A.DoB.Date;
				B.DoB.Month = A.DoB.Month;
				B.DoB.Year = A.DoB.Year;
			}
			if (A.sex != 0)
				B.sex = A.sex;
			if (strlen(A.email) != 0)
				strcpy(B.email, A.email);
			if (strlen(A.address) != 0)
				strcpy(B.address, A.address);

			err_2 = fopen_s(&f, link, "wb");
			if (err_2 == 0)
			{
				fwrite(&B, sizeof(Readers), 1, f);
				fclose(f);
			}

			drawRectangle(36, 12, 48, 3, 10);
			gotoxy(46, 13);
			printf("CHINH SUA THONG TIN THANH CONG");
			//Ngưng chương trình 1s để người dùng đọc thông báo
			Sleep(1000);
		}
		//Nếu đã ấn 'Trở về' [F12]
		else
		{
			drawRectangle(36, 6, 48, 19, 15);
			ReadersMenu(n, list);
			break;
		}
	} while (!BACK);
	gotoxy(44, 0);
}

//Thao tác Xóa thông tin một độc giả theo mã độc giả
void DeleteReader()
{
	bool BACK = false;
	Title(">>XOA THONG TIN DOC GIA");
	drawRectangle(36, 6, 48, 7, 3);
	gotoxy(38, 7);
	printf("Nhap ma doc gia sach can xoa: ");
	drawRectangle(38, 8, 44, 1, 15);
	Readers A;
	errno_t err;

	//Nhập ISBN
	do
	{
		drawRectangle(36, 9, 48, 3, 3);
		drawRectangle(38, 8, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(58, 10);
		printf("ENTER to Delete a reader");
		gotoxy(58, 11);
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
			int stt = remove(link);
			if (stt == 0)
			{
				//In thông báo
				drawRectangle(36, 9, 48, 3, 10);
				gotoxy(51, 10);
				printf("XOA SACH THANH CONG");
				Sleep(1000);
			}
			else
			{
				//In thông báo
				drawRectangle(36, 9, 48, 3, 12);
				gotoxy(51, 10);
				printf("DOC GIA KHONG TON TAI");
				Sleep(1000);
			}
		}
		//Nếu bấm 'Trở về'
		else
		{
			//Trở về BooksMenu
			int n;
			char list[10];
			ReadReadersMenuData(n, list);
			drawRectangle(36, 6, 48, 7, 15);
			ReadersMenu(n, list);
			break;
		}

	} while (!BACK);
}

void FullReadersInfo(int posX, int posY, int TextColor, int BgColor, Node_Reader *p)
{
	drawRectangle(posX, posY, 112, 9, 15);
	textBgColor(TextColor, BgColor);
	gotoxy(posX, posY);
	printf("- Ma doc gia: %09ld", p->Data.code);
	gotoxy(posX, posY + 1);
	printf("- Ho va ten: %s", p->Data.fullname);
	gotoxy(posX, posY + 2);
	printf("- CMND: %s", p->Data.ID);
	gotoxy(posX, posY + 3);
	printf("- Ngay sinh: %02d/%02d/%04d", p->Data.DoB.Date, p->Data.DoB.Month, p->Data.DoB.Year);
	gotoxy(posX, posY + 4);
	printf("- Gioi tinh: ");
	if (p->Data.sex == 1)
	{
		printf("Nam");
	}
	else
		if (p->Data.sex == 2)
		{
			printf("Nu");
		}
		else
		{
			printf("Khac");
		}
	gotoxy(posX, posY + 5);
	printf("- Email: %s", p->Data.email);
	gotoxy(posX, posY + 6);
	printf("- Dia chi: %s", p->Data.address);
	gotoxy(posX, posY + 7);
	printf("- Ngay lap the: %02d/%02d/%04d", p->Data.createdDay.Date, p->Data.createdDay.Month, p->Data.createdDay.Year);
	gotoxy(posX, posY + 8);
	printf("- Ngay het han: %02d/%02d/%04d", p->Data.expirationDay.Date, p->Data.expirationDay.Month, p->Data.expirationDay.Year);
}

void MoveSelectReadersView(List_Reader L, int CurrentLine, int rows)
{
	//Default
	Node_Reader *p = L.pHead;
	int CurrentSelect = 0;

	drawRectangle(36, CurrentLine, 48, 1, 9);
	if (p != NULL)
	{
		gotoxy(37, CurrentLine); printf("%09d", p->Data.code);
		if (strlen(p->Data.fullname) <= 20)
		{
			gotoxy(49, CurrentLine);
			printf("%s", p->Data.fullname);
		}
		else
		{
			gotoxy(49, CurrentLine);
			char fullname[18];
			fullname[17] = '\0';
			strncpy(fullname, p->Data.fullname, 17);
			printf("%s", fullname);
			printf("...");
		}
		gotoxy(71, CurrentLine);
		printf("%02d/%02d/%04d", p->Data.expirationDay.Date, p->Data.expirationDay.Month, p->Data.expirationDay.Year);

		FullReadersInfo(0, 18, 0, 15, p);
	}
	else
	{
		gotoxy(37, CurrentLine); printf("<NULL>");
		gotoxy(49, CurrentLine); printf("<NULL>");
		gotoxy(71, CurrentLine); printf("<NULL>");
	}

	VerticalLine(48, CurrentLine, 1, 15, 9);
	VerticalLine(69, CurrentLine, 1, 15, 9);
	/*
	#UP: 72
	#DOWN: 80
	*/
	if (p == NULL)
	{
		Sleep(800);
		int n;
		char list[10];
		ReadReadersMenuData(n, list);
		drawRectangle(36, 6, 48, 20, 15);
		ReadersMenu(n, list);
	}

	if (p != NULL)
	{
		int ch = getch();
		while (ch != 27)	//ESC
		{
			//MOVEUP
			if (ch == 72)
			{
				if (CurrentSelect > 0)
				{
					if (p->pPrev != NULL)
					{
						drawRectangle(36, CurrentLine, 48, 1, 3);

						gotoxy(37, CurrentLine); printf("%09d", p->Data.code);
						if (strlen(p->Data.fullname) <= 20)
						{
							gotoxy(49, CurrentLine);
							printf("%s", p->Data.fullname);
						}
						else
						{
							gotoxy(49, CurrentLine);
							char fullname[18];
							fullname[17] = '\0';
							strncpy(fullname, p->Data.fullname, 17);
							printf("%s", fullname);
							printf("...");
						}
						gotoxy(71, CurrentLine);
						printf("%02d/%02d/%04d", p->Data.expirationDay.Date, p->Data.expirationDay.Month, p->Data.expirationDay.Year);
						VerticalLine(48, CurrentLine, 1, 15, 3);
						VerticalLine(69, CurrentLine, 1, 15, 3);

						CurrentSelect--;
						CurrentLine--;
						p = p->pPrev;

						drawRectangle(36, CurrentLine, 48, 1, 9);

						gotoxy(37, CurrentLine); printf("%09d", p->Data.code);
						if (strlen(p->Data.fullname) <= 20)
						{
							gotoxy(49, CurrentLine);
							printf("%s", p->Data.fullname);
						}
						else
						{
							gotoxy(49, CurrentLine);
							char fullname[18];
							fullname[17] = '\0';
							strncpy(fullname, p->Data.fullname, 17);
							printf("%s", fullname);
							printf("...");
						}
						gotoxy(71, CurrentLine);
						printf("%02d/%02d/%04d", p->Data.expirationDay.Date, p->Data.expirationDay.Month, p->Data.expirationDay.Year);
						VerticalLine(48, CurrentLine, 1, 15, 9);
						VerticalLine(69, CurrentLine, 1, 15, 9);
					}
				}
				else
				{
					if (p->pPrev != NULL)
					{
						p = p->pPrev;

						drawRectangle(36, CurrentLine, 48, 1, 9);

						gotoxy(37, CurrentLine); printf("%09d", p->Data.code);
						if (strlen(p->Data.fullname) <= 20)
						{
							gotoxy(49, CurrentLine);
							printf("%s", p->Data.fullname);
						}
						else
						{
							gotoxy(49, CurrentLine);
							char fullname[18];
							fullname[17] = '\0';
							strncpy(fullname, p->Data.fullname, 17);
							printf("%s", fullname);
							printf("...");
						}
						gotoxy(71, CurrentLine);
						printf("%02d/%02d/%04d", p->Data.expirationDay.Date, p->Data.expirationDay.Month, p->Data.expirationDay.Year);
						VerticalLine(48, CurrentLine, 1, 15, 9);
						VerticalLine(69, CurrentLine, 1, 15, 9);

						Node_Reader *q = p->pNext;
						for (int i = 1; i <= rows - 1; i++)
						{
							drawRectangle(36, CurrentLine + i, 48, 1, 3);

							gotoxy(37, CurrentLine + i); printf("%09d", q->Data.code);
							if (strlen(q->Data.fullname) <= 20)
							{
								gotoxy(49, CurrentLine + i);
								printf("%s", q->Data.fullname);
							}
							else
							{
								gotoxy(49, CurrentLine + i);
								char fullname[18];
								fullname[17] = '\0';
								strncpy(fullname, q->Data.fullname, 17);
								printf("%s", fullname);
								printf("...");
							}
							gotoxy(71, CurrentLine + i);
							printf("%02d/%02d/%04d", q->Data.expirationDay.Date, q->Data.expirationDay.Month, q->Data.expirationDay.Year);
							VerticalLine(48, CurrentLine + i, 1, 15, 3);
							VerticalLine(69, CurrentLine + i, 1, 15, 3);
							q = q->pNext;
							if (q == NULL) break;
						}
					}
				}
			}
			//MOVEDOWN
			if (ch == 80)
			{
				if (CurrentSelect < rows -1 )
				{
					if (p->pNext != NULL)
					{
						drawRectangle(36, CurrentLine, 48, 1, 3);

						gotoxy(37, CurrentLine); printf("%09d", p->Data.code);
						if (strlen(p->Data.fullname) <= 20)
						{
							gotoxy(49, CurrentLine);
							printf("%s", p->Data.fullname);
						}
						else
						{
							gotoxy(49, CurrentLine);
							char fullname[18];
							fullname[17] = '\0';
							strncpy(fullname, p->Data.fullname, 17);
							printf("%s", fullname);
							printf("...");
						}
						gotoxy(71, CurrentLine);
						printf("%02d/%02d/%04d", p->Data.expirationDay.Date, p->Data.expirationDay.Month, p->Data.expirationDay.Year);
						VerticalLine(48, CurrentLine, 1, 15, 3);
						VerticalLine(69, CurrentLine, 1, 15, 3);

						CurrentSelect++;
						CurrentLine++;
						p = p->pNext;

						drawRectangle(36, CurrentLine, 48, 1, 9);

						gotoxy(37, CurrentLine); printf("%09d", p->Data.code);
						if (strlen(p->Data.fullname) <= 20)
						{
							gotoxy(49, CurrentLine);
							printf("%s", p->Data.fullname);
						}
						else
						{
							gotoxy(49, CurrentLine);
							char fullname[18];
							fullname[17] = '\0';
							strncpy(fullname, p->Data.fullname, 17);
							printf("%s", fullname);
							printf("...");
						}
						gotoxy(71, CurrentLine);
						printf("%02d/%02d/%04d", p->Data.expirationDay.Date, p->Data.expirationDay.Month, p->Data.expirationDay.Year);
						VerticalLine(48, CurrentLine, 1, 15, 9);
						VerticalLine(69, CurrentLine, 1, 15, 9);
					}
				}
				else
				{
					if (p->pNext != NULL)
					{
						p = p->pNext;
						drawRectangle(36, CurrentLine, 48, 1, 9);

						gotoxy(37, CurrentLine); printf("%09d", p->Data.code);
						if (strlen(p->Data.fullname) <= 20)
						{
							gotoxy(49, CurrentLine);
							printf("%s", p->Data.fullname);
						}
						else
						{
							gotoxy(49, CurrentLine);
							char fullname[18];
							fullname[17] = '\0';
							strncpy(fullname, p->Data.fullname, 17);
							printf("%s", fullname);
							printf("...");
						}
						gotoxy(71, CurrentLine);
						printf("%02d/%02d/%04d", p->Data.expirationDay.Date, p->Data.expirationDay.Month, p->Data.expirationDay.Year);
						VerticalLine(48, CurrentLine, 1, 15, 9);
						VerticalLine(69, CurrentLine, 1, 15, 9);

						Node_Reader *q = p->pPrev;
						for (int i = 1; i <= CurrentSelect; i++)
						{
							drawRectangle(36, CurrentLine - i, 48, 1, 3);

							gotoxy(37, CurrentLine - i); printf("%09d", q->Data.code);
							if (strlen(q->Data.fullname) <= 20)
							{
								gotoxy(49, CurrentLine - i);
								printf("%s", q->Data.fullname);
							}
							else
							{
								gotoxy(49, CurrentLine - i);
								char fullname[18];
								fullname[17] = '\0';
								strncpy(fullname, q->Data.fullname, 17);
								printf("%s", fullname);
								printf("...");
							}
							gotoxy(71, CurrentLine - i);
							printf("%02d/%02d/%04d", q->Data.expirationDay.Date, q->Data.expirationDay.Month, q->Data.expirationDay.Year);
							VerticalLine(48, CurrentLine - i, 1, 15, 3);
							VerticalLine(69, CurrentLine - i, 1, 15, 3);
							q = q->pPrev;
							if (q == NULL) break;
						}
					}
				}
			}

			FullReadersInfo(0, 18, 0, 15, p);

			//F12:BACK
			if (ch == 134)
			{
				//drawRectangle(36, 6, 48, 21, 15);
				int n;
				char list[11];
				SetBG();
				ReadReadersMenuData(n, list);
				ReadersMenu(n, list);
				break;
			}
			ch = getch();
		}
	}
}

void ViewListReaders(List_Reader L,  int CurrentLine, int fullHeight)
{
	Title(">>DANH SACH CAC DOC GIA");
	Nocursortype();
	drawRectangle(36, CurrentLine, 48, 1, 1);
	textBgColor(15, 1);
	gotoxy(37, CurrentLine); printf("MA DOC GIA");
	gotoxy(54, CurrentLine); printf("TEN DOC GIA");
	gotoxy(71, CurrentLine); printf("NGAY HET HAN");
	VerticalLine(48, CurrentLine, 1, 15, 1);
	VerticalLine(69, CurrentLine, 1, 15, 1);

	drawRectangle(36, CurrentLine + 1, 48, fullHeight - 1, 3);
	VerticalLine(48, CurrentLine + 1, fullHeight - 1, 15, 3);
	VerticalLine(69, CurrentLine + 1, fullHeight - 1, 15, 3);

	textBgColor(0, 3);
	Node_Reader *p = L.pHead;
	
	//int NumMonth = ReadNumMonth();

	for (int i = 0; i < fullHeight - 1; i++)
	{
		if (p == NULL) break;
		gotoxy(37, CurrentLine + 1 + i); printf("%09d", p->Data.code);
		if (strlen(p->Data.fullname) <= 20)
		{
			gotoxy(49, CurrentLine + 1 + i);
			printf("%s", p->Data.fullname);
		}
		else
		{
			gotoxy(49, CurrentLine + 1 + i);
			char fullname[18];
			fullname[17] = '\0';
			strncpy(fullname, p->Data.fullname, 17);
			printf("%s", fullname);
			printf("...");
		}
		gotoxy(71, CurrentLine + 1 + i);
		printf("%02d/%02d/%04d", p->Data.expirationDay.Date, p->Data.expirationDay.Month, p->Data.expirationDay.Year);
		p = p->pNext;
		if (p == NULL) break;
	}
	MoveSelectReadersView(L, CurrentLine + 1, fullHeight - 1);
}

void FullReadersInfoID(int posX, int posY, int TextColor, int BgColor, Readers reader)
{
	drawRectangle(posX, posY, 112, 9, 15);
	textBgColor(TextColor, BgColor);
	gotoxy(posX, posY);
	printf("- Ma doc gia: %09ld", reader.code);
	gotoxy(posX, posY + 1);
	printf("- Ho va ten: %s", reader.fullname);
	gotoxy(posX, posY + 2);
	printf("- CMND: %s", reader.ID);
	gotoxy(posX, posY + 3);
	printf("- Ngay sinh: %02d/%02d/%04d", reader.DoB.Date, reader.DoB.Month, reader.DoB.Year);
	gotoxy(posX, posY + 4);
	printf("- Gioi tinh: ");
	if (reader.sex == 1)
	{
		printf("Nam");
	}
	else
		if (reader.sex == 2)
		{
			printf("Nu");
		}
		else
		{
			printf("Khac");
		}
	gotoxy(posX, posY + 5);
	printf("- Email: %s", reader.email);
	gotoxy(posX, posY + 6);
	printf("- Dia chi: %s", reader.address);
	gotoxy(posX, posY + 7);
	printf("- Ngay lap the: %02d/%02d/%04d", reader.createdDay.Date, reader.createdDay.Month, reader.createdDay.Year);
	gotoxy(posX, posY + 8);
	printf("- Ngay het han: %02d/%02d/%04d", reader.expirationDay.Date, reader.expirationDay.Month, reader.expirationDay.Year);
}

void SearchReaderID()
{
	bool BACK = false;
	Title(">>TIM KIEM DOC GIA THEO CMND");
	drawRectangle(36, 6, 48, 7, 3);
	gotoxy(38, 7);
	printf("Nhap CMND: ");
	drawRectangle(38, 8, 44, 1, 15);
	Readers A;
	errno_t err;

	//Nhập CMND
	do
	{
		drawRectangle(36, 9, 48, 3, 3);
		drawRectangle(38, 8, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(58, 10);
		printf("ENTER to Search a reader");
		gotoxy(58, 11);
		printf("F12 to Back");
		textBgColor(0, 15);

		gotoxy(38, 8);

		int status = InputIndentity(A.ID);
		if (status == -1)
		{
			BACK = true;
		}

		//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
		if (!BACK)
		{
			List_Reader L = GetReadersData();
			List_Reader L2;
			Init_Reader(L2);
			Node_Reader *p;
			for (p = L.pTail; p != NULL; p = p->pPrev)
			{
				if (strcmp(p->Data.ID, A.ID) == 0 )
				{
					Insert_first_Reader(L2, p->Data);
				}
			}
			if (Len_Reader(L2) > 0)
			{
				ViewListReaders(L2, 13, 4);
				break;
			}
			else
			{
				//In thông báo
				drawRectangle(36, 9, 48, 3, 12);
				gotoxy(51, 10);
				printf("DOC GIA KHONG TON TAI");
				Sleep(1000);
			}
		}
		//Nếu bấm 'Trở về'
		else
		{
			//Trở về BooksMenu
			int n;
			char list[10];
			drawRectangle(0, 18, 112, 9, 15);
			ReadReadersMenuData(n, list);
			drawRectangle(36, 6, 48, 7, 15);
			ReadersMenu(n, list);
			break;
		}

	} while (!BACK);
}

void SearchReaderName()
{
	bool BACK = false;
	Title(">>TIM KIEM DOC GIA THEO TEN");
	drawRectangle(36, 6, 48, 7, 3);
	gotoxy(38, 7);
	printf("Nhap Ten: ");
	drawRectangle(38, 8, 44, 1, 15);
	Readers A;
	errno_t err;

	//Nhập tên sách
	do
	{
		drawRectangle(36, 9, 48, 3, 3);
		drawRectangle(38, 8, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(58, 10);
		printf("ENTER to Search a reader");
		gotoxy(58, 11);
		printf("F12 to Back");
		textBgColor(0, 15);

		gotoxy(38, 8);
		int status = InputFullname(A.fullname);
		if (status == -1)
		{
			BACK = true;
		}

		//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
		if (!BACK)
		{
			List_Reader L = GetReadersData();
			List_Reader L2;
			Init_Reader(L2);
			Node_Reader *p;
			for (p = L.pTail; p != NULL; p = p->pPrev)
			{
				if (strstr(p->Data.fullname, A.fullname) != NULL)
				{
					Insert_first_Reader(L2, p->Data);
				}
			}
			if (Len_Reader(L2) > 0)
			{
				ViewListReaders(L2, 13, 4);
				break;
			}
			else
			{
				//In thông báo
				drawRectangle(36, 9, 48, 3, 12);
				gotoxy(51, 10);
				printf("DOC GIA KHONG TON TAI");
				Sleep(1000);
			}
			//MoveSelectBooksView(L2);
			//FullBooksInfo(0, 18, 0, 15, L2.pHead);
		}
		//Nếu bấm 'Trở về'
		else
		{
			//Trở về BooksMenu
			int n;
			char list[10];
			SetBG();
			ReadReadersMenuData(n, list);
			//drawRectangle(36, 6, 48, 7, 15);
			ReadersMenu(n, list);
			break;
		}

	} while (!BACK);
}

