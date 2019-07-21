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
#include "linked-list.h"
#include "input.h"
#include "function-standard.h"
#include "books.h"

//Vẽ vùng [BOOKMENU]
void MakeFieldBooksMenu(int n)
{
	DrawAppNameTab(15, 2);
	Title(">>QUAN LI SACH");

	//Xóa khung Main Menu
	drawRectangle(36, 6, 48, 9, 15);

	//Vẽ khung menu
	drawRectangle(36, 6, 48, n, 3);
}

//Gọi tính năng thứ <I>
void BooksAction(int i)
{
	switch (i)
	{
	case 0:
		ViewListBooks();
		break;
	case 1:
		InputBooksData();
		break;
	case 2:
		ModifyBooksData();
		break;
	case 3:
		DeleteBook();
		break;
	case 4:
		SearchBookISBN();
		break;
	case 5:
		SearchBookName();
		break;
	default:
		break;
	}
}

//Tạo [BOOKSMENU] di chuyển lên xuống
void MoveBooksSelect(int n, char f[10][50], char list[])
{
	//Default
	Nocursortype();
	int CurrentSelect = 0, CurrentLine = 6;
	drawRectangle(36, CurrentLine, 48, 1, 1);
	textBgColor(15, 1);
	gotoxy(47, 6);
	PrintFeature(f[0]);
	/*
	#UP: 72
	#DOWN: 80
	*/
	int ch = getch();
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
					BooksAction(i);
					break;
				}
			}
		}

		if (ch == 134) //F12
		{
			int n;
			char list[10], user[21], pass[21];
			ReadMenuData(n, list);
			Menu(n, list);
			break;
		}
		if (ch == 13) break;
		ch = getch();
	}
}

//In ra [BOOKMENU] với số lượng <countFeatures> tính năng và danh sách <list> các tính năng
void BooksMenu(int countFeatures, char list[])
{
	/*
	countFeatures <= 10
	list = "xxxxxxxxxx'
	x = 1 : show feature
	x = 0 : hide feature
	*/
	char f[10][50] =
	{
		"Xem danh sach cac sach",
		"Them sach",
		"Chinh sua thong tin sach",
		"Xoa thong tin sach",
		"Tim kiem sach theo ISBN",
		"Tim kiem sach theo ten sach",
	};
	MakeFieldBooksMenu(countFeatures);
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
	MoveBooksSelect(countFeatures, fUse, list);
	gotoxy(44, 0);
}

//Hàm nhận vào loại người dùng để đưa vào [BOOKSMENU] với tính năng tương ứng
void CaseBooksMenu()
{
	int n = ReadClassification();
	FILE *f = fopen("cache/currentBooksMenu.txt", "w");	//Viết vào cache trạng thái Books menu
	switch (n)
	{
	case 1:	//admin
		fprintf(f, "%d %s", 6, "111111");
		fclose(f);
		BooksMenu(6, "111111");
		break;
	case 2:	//manager
		fprintf(f, "%d %s", 6, "111111");
		fclose(f);
		BooksMenu(6, "111111");
		break;
	case 3:	//expert
		fprintf(f, "%d %s", 2, "000011");
		fclose(f);
		BooksMenu(2, "000011");
		break;
	default:
		break;
	};
}

//Bảng nhập thông tin Thêm sách mới
void InputBooksData()
{
	Yescursortype();
	bool BACK = false;	//Biến kiểm tra có bấm 'Trở về' [F12] hay chưa?
	Title(">>THEM MOI SACH");
	do
	{
		drawRectangle(36, 6, 48, 21, 3);
		//Ghi các thuộc tính của trường nhập
		gotoxy(38, 7);
		printf("ISBN[13]: ");
		gotoxy(38, 9);
		printf("Ten sach[100]: ");
		gotoxy(38, 11);
		printf("Tac gia[100]: ");
		gotoxy(38, 13);
		printf("Nha xuat ban[100]: ");
		gotoxy(38, 15);
		printf("Nam xuat ban: ");
		gotoxy(38, 17);
		printf("The loai[100]: ");
		gotoxy(38, 19);
		printf("Gia sach: (VND)");
		gotoxy(38, 21);
		printf("So luong: ");
		//Vẽ khung input
		drawRectangle(38, 8, 44, 1, 15);
		drawRectangle(38, 10, 44, 1, 15);
		drawRectangle(38, 12, 44, 1, 15);
		drawRectangle(38, 14, 44, 1, 15);
		drawRectangle(38, 16, 44, 1, 15);
		drawRectangle(38, 18, 44, 1, 15);
		drawRectangle(38, 20, 44, 1, 15);
		drawRectangle(38, 22, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(63, 24);
		printf("ENTER to Add a book");
		gotoxy(63, 25);
		printf("F12 to Back");
		textBgColor(0, 15);

		//Nhập
		Books A;
		//Nhập ISBN
		do
		{
			gotoxy(38, 8);
			int status = InputISBN(A.ISBN);
			if (status == -1)
			{
				BACK = true;
			}
		} while (strlen(A.ISBN) == 0 && !BACK);
		//Nhập tên sách
		if (!BACK)
		{
			do
			{
				gotoxy(38, 10);
				int status = InputString100(A.name);
				if (status == -1)
				{
					BACK = true;	//Đã bấm 'Trở về' [F12]
				}
			} while (strlen(A.name) == 0 && !BACK);
		}
		//Nhập Tác giả
		if (!BACK)
		{
			do
			{
				gotoxy(38, 12);
				int status = InputString100(A.author);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.author) == 0 && !BACK);
		}
		//Nhập Nhà xuất bản
		if (!BACK)
		{
			do
			{
				gotoxy(38, 14);
				int status = InputString100(A.publisher);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.publisher) == 0 && !BACK);
		}
		//Năm xuất bản
		if (!BACK)
		{
			do
			{
				gotoxy(38, 16);
				A.published = Input4Num();
				if (A.published == -1)
				{
					BACK = true;
				}
			} while (A.published == 0);
		}
		//Nhập Thể loại
		if (!BACK)
		{
			do
			{
				gotoxy(38, 18);
				int status = InputString100(A.category);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.category) == 0 && !BACK);
		}
		//Nhập Giá sách
		if (!BACK)
		{
			do
			{
				gotoxy(38, 20);
				int status = InputMoney(A.prices);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.prices) == 0 && !BACK);
		}
		//Nhập Số lượng
		if (!BACK)
		{
			do
			{
				gotoxy(38, 22);
				A.number = Input4Num();
				if (A.number == -1)
				{
					BACK = true;
				}
			} while (A.number == 0);
		}

		int n;
		char list[11];
		char user[21], pass[21];
		ReadBooksMenuData(n, list);
		ReadCacheAccount(user, pass);

		//Nếu chưa ấn 'Trở về' [F12]
		if (!BACK)
		{
			//Tạo biến link chứa giá trị đường dẫn đến file dữ liệu sách
			char link[100] = "books/";
			strcat(link, A.ISBN);
			strcat(link, ".bin");

			FILE *f;
			errno_t err = fopen_s(&f, link, "rb");
			//Nếu chưa tồn tại file có ISBN vừa nhập (không mở được file ISBN.bin)
			if (err != 0)
			{
				//Ghi ISBN vào file 'List.dat'
				err = fopen_s(&f, "books/List.tdat", "ab");
				if (err == 0)
				{
					fwrite(&A.ISBN, sizeof(A.ISBN), 1, f);
					fclose(f);
				}
				//Ghi dữ liệu sách vào file '<ISBN>.bin'
				err = fopen_s(&f, link, "wb");
				if (err == 0)
				{
					fwrite(&A, sizeof(Books), 1, f);
					fclose(f);
				}
			}
			//Nếu sách có ISBN đã tồn tại trong thư viện (mở được file ISBN.bin)
			else
			{
				Books B;
				fread(&B, sizeof(Books), 1, f);
				fclose(f);
				if (B.exist)
				{
					B.number += A.number;
					err = fopen_s(&f, link, "wb");
					if (err == 0)
					{
						fwrite(&B, sizeof(Books), 1, f);
						fclose(f);
					}
				}
				else
				{
					//Ghi dữ liệu sách vào file '<ISBN>.bin'
					err = fopen_s(&f, link, "wb");
					if (err == 0)
					{
						fwrite(&A, sizeof(Books), 1, f);
						fclose(f);
					}
				}
			}
			drawRectangle(36, 12, 48, 3, 10);
			gotoxy(50, 13);
			printf("THEM SACH THANH CONG");
			//Ngưng chương trình 1s để người dùng đọc thông báo
			Sleep(1000);
		}
		//Nếu đã ấn 'Trở về' [F12]
		else
		{
			drawRectangle(36, 6, 48, 21, 15);
			BooksMenu(n, list);
			break;
		}
	} while (!BACK);
	gotoxy(44, 0);
}

void FullBooksInfo(int posX, int posY, int TextColor, int BgColor, Node *p)
{
	drawRectangle(posX, posY, 112, 8, 15);
	textBgColor(TextColor, BgColor);
	gotoxy(posX, posY);
	printf("- ISBN: %s", p->Data.ISBN);
	gotoxy(posX, posY + 1);
	printf("- Ten sach: %s", p->Data.name);
	gotoxy(posX, posY + 2);
	printf("- Tac gia: %s", p->Data.author);
	gotoxy(posX, posY + 3);
	printf("- Nha xuat ban: %s", p->Data.publisher);
	gotoxy(posX, posY + 4);
	printf("- Nam xuat ban: %d", p->Data.published);
	gotoxy(posX, posY + 5);
	printf("- The loai: %s", p->Data.category);
	gotoxy(posX, posY + 6);
	printf("- Gia sach: %s", p->Data.prices);
	gotoxy(posX, posY + 7);
	printf("- So luong sach: %d", p->Data.number);
}

void MoveSelectBooksView(List L, int CurrentLine, int rows)
{
	//Default
	Node *p = L.pHead;
	int CurrentSelect = 0;

	drawRectangle(0, CurrentLine, MAXWIDTH, 1, 9);


	if (p != NULL)
	{
		gotoxy(0, CurrentLine); printf("%s", p->Data.ISBN);
		if (strlen(p->Data.name) <= 59)
		{
			gotoxy(14, CurrentLine);
			printf("%s", p->Data.name);
		}
		else
		{
			gotoxy(14, CurrentLine);
			char name[57];
			name[56] = '\0';
			strncpy(name, p->Data.name, 56);
			printf("%s", name);
			printf("...");
		}
		if (strlen(p->Data.author) <= 29)
		{
			gotoxy(74, CurrentLine);
			printf("%s", p->Data.author);
		}
		else
		{
			gotoxy(74, CurrentLine);
			char author[27];
			author[26] = '\0';
			strncpy(author, p->Data.author, 26);
			printf("%s", author);
			printf("...");
		}
		gotoxy(104, CurrentLine); printf("%d", p->Data.number);

		FullBooksInfo(0, 18, 0, 15, p);
	}
	else
	{
		gotoxy(0, CurrentLine); printf("<NULL>");
		gotoxy(14, CurrentLine); printf("<NULL>");
		gotoxy(74, CurrentLine); printf("<NULL>");
		gotoxy(104, CurrentLine); printf("<NULL>");
	}
	VerticalLine(13, CurrentLine, 1, 15, 9);
	VerticalLine(73, CurrentLine, 1, 15, 9);
	VerticalLine(103, CurrentLine, 1, 15, 9);

	/*
	#UP: 72
	#DOWN: 80
	*/

	if (p == NULL)
	{
		Sleep(800);
		int n;
		char list[10];
		ReadBooksMenuData(n, list);
		SetBG();
		BooksMenu(n, list);
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
						drawRectangle(0, CurrentLine, MAXWIDTH, 1, 3);
						gotoxy(0, CurrentLine); printf("%s", p->Data.ISBN);
						if (strlen(p->Data.name) <= 59)
						{
							gotoxy(14, CurrentLine);
							printf("%s", p->Data.name);
						}
						else
						{
							gotoxy(14, CurrentLine);
							char name[57];
							name[56] = '\0';
							strncpy(name, p->Data.name, 56);
							printf("%s", name);
							printf("...");
						}
						if (strlen(p->Data.author) <= 29)
						{
							gotoxy(74, CurrentLine);
							printf("%s", p->Data.author);
						}
						else
						{
							gotoxy(74, CurrentLine);
							char author[27];
							author[26] = '\0';
							strncpy(author, p->Data.author, 26);
							printf("%s", author);
							printf("...");
						}
						gotoxy(104, CurrentLine); printf("%d", p->Data.number);
						VerticalLine(13, CurrentLine, 1, 15, 3);
						VerticalLine(73, CurrentLine, 1, 15, 3);
						VerticalLine(103, CurrentLine, 1, 15, 3);

						CurrentSelect--;
						CurrentLine--;
						p = p->pPrev;

						drawRectangle(0, CurrentLine, MAXWIDTH, 1, 9);
						gotoxy(0, CurrentLine); printf("%s", p->Data.ISBN);
						if (strlen(p->Data.name) <= 59)
						{
							gotoxy(14, CurrentLine);
							printf("%s", p->Data.name);
						}
						else
						{
							gotoxy(14, CurrentLine);
							char name[57];
							name[56] = '\0';
							strncpy(name, p->Data.name, 56);
							printf("%s", name);
							printf("...");
						}
						if (strlen(p->Data.author) <= 29)
						{
							gotoxy(74, CurrentLine);
							printf("%s", p->Data.author);
						}
						else
						{
							gotoxy(74, CurrentLine);
							char author[27];
							author[26] = '\0';
							strncpy(author, p->Data.author, 26);
							printf("%s", author);
							printf("...");
						}
						gotoxy(104, CurrentLine); printf("%d", p->Data.number);
						VerticalLine(13, CurrentLine, 1, 15, 9);
						VerticalLine(73, CurrentLine, 1, 15, 9);
						VerticalLine(103, CurrentLine, 1, 15, 9);
					}
				}
				else
				{
					if (p->pPrev != NULL)
					{
						p = p->pPrev;
						drawRectangle(0, CurrentLine, MAXWIDTH, 1, 9);
						gotoxy(0, CurrentLine); printf("%s", p->Data.ISBN);
						if (strlen(p->Data.name) <= 59)
						{
							gotoxy(14, CurrentLine);
							printf("%s", p->Data.name);
						}
						else
						{
							gotoxy(14, CurrentLine);
							char name[57];
							name[56] = '\0';
							strncpy(name, p->Data.name, 56);
							printf("%s", name);
							printf("...");
						}
						if (strlen(p->Data.author) <= 29)
						{
							gotoxy(74, CurrentLine);
							printf("%s", p->Data.author);
						}
						else
						{
							gotoxy(74, CurrentLine);
							char author[27];
							author[26] = '\0';
							strncpy(author, p->Data.author, 26);
							printf("%s", author);
							printf("...");
						}
						gotoxy(104, CurrentLine); printf("%d", p->Data.number);
						VerticalLine(13, CurrentLine, 1, 15, 9);
						VerticalLine(73, CurrentLine, 1, 15, 9);
						VerticalLine(103, CurrentLine, 1, 15, 9);

						Node *q = p->pNext;
						for (int i = 1; i <= rows; i++) //8->0
						{
							drawRectangle(0, CurrentLine + i, MAXWIDTH, 1, 3);
							gotoxy(0, CurrentLine + i); printf("%s", q->Data.ISBN);
							if (strlen(q->Data.name) <= 59)
							{
								gotoxy(14, CurrentLine + i);
								printf("%s", q->Data.name);
							}
							else
							{
								gotoxy(14, CurrentLine + i);
								char name[57];
								name[56] = '\0';
								strncpy(name, q->Data.name, 56);
								printf("%s", name);
								printf("...");
							}
							if (strlen(q->Data.author) <= 29)
							{
								gotoxy(74, CurrentLine + i);
								printf("%s", q->Data.author);
							}
							else
							{
								gotoxy(74, CurrentLine + i);
								char author[27];
								author[26] = '\0';
								strncpy(author, q->Data.author, 26);
								printf("%s", author);
								printf("...");
							}
							gotoxy(104, CurrentLine + i); printf("%d", q->Data.number);
							VerticalLine(13, CurrentLine + i, 1, 15, 3);
							VerticalLine(73, CurrentLine + i, 1, 15, 3);
							VerticalLine(103, CurrentLine + i, 1, 15, 3);
							q = q->pNext;
							if (q == NULL) break;
						}
					}
				}
			}
			//MOVEDOWN
			if (ch == 80)
			{
				if (CurrentSelect < rows)
				{
					if (p->pNext != NULL)
					{
						drawRectangle(0, CurrentLine, MAXWIDTH, 1, 3);
						gotoxy(0, CurrentLine); printf("%s", p->Data.ISBN);
						if (strlen(p->Data.name) <= 59)
						{
							gotoxy(14, CurrentLine);
							printf("%s", p->Data.name);
						}
						else
						{
							gotoxy(14, CurrentLine);
							char name[57];
							name[56] = '\0';
							strncpy(name, p->Data.name, 56);
							printf("%s", name);
							printf("...");
						}
						if (strlen(p->Data.author) <= 29)
						{
							gotoxy(74, CurrentLine);
							printf("%s", p->Data.author);
						}
						else
						{
							gotoxy(74, CurrentLine);
							char author[27];
							author[26] = '\0';
							strncpy(author, p->Data.author, 26);
							printf("%s", author);
							printf("...");
						}
						gotoxy(104, CurrentLine); printf("%d", p->Data.number);
						VerticalLine(13, CurrentLine, 1, 15, 3);
						VerticalLine(73, CurrentLine, 1, 15, 3);
						VerticalLine(103, CurrentLine, 1, 15, 3);

						CurrentSelect++;
						CurrentLine++;
						p = p->pNext;

						drawRectangle(0, CurrentLine, MAXWIDTH, 1, 9);
						gotoxy(0, CurrentLine); printf("%s", p->Data.ISBN);
						if (strlen(p->Data.name) <= 59)
						{
							gotoxy(14, CurrentLine);
							printf("%s", p->Data.name);
						}
						else
						{
							gotoxy(14, CurrentLine);
							char name[57];
							name[56] = '\0';
							strncpy(name, p->Data.name, 56);
							printf("%s", name);
							printf("...");
						}
						if (strlen(p->Data.author) <= 29)
						{
							gotoxy(74, CurrentLine);
							printf("%s", p->Data.author);
						}
						else
						{
							gotoxy(74, CurrentLine);
							char author[27];
							author[26] = '\0';
							strncpy(author, p->Data.author, 26);
							printf("%s", author);
							printf("...");
						}
						gotoxy(104, CurrentLine); printf("%d", p->Data.number);
						VerticalLine(13, CurrentLine, 1, 15, 9);
						VerticalLine(73, CurrentLine, 1, 15, 9);
						VerticalLine(103, CurrentLine, 1, 15, 9);
					}
				}
				else
				{
					if (p->pNext != NULL)
					{
						p = p->pNext;
						drawRectangle(0, CurrentLine, MAXWIDTH, 1, 9);
						gotoxy(0, CurrentLine); printf("%s", p->Data.ISBN);
						if (strlen(p->Data.name) <= 59)
						{
							gotoxy(14, CurrentLine);
							printf("%s", p->Data.name);
						}
						else
						{
							gotoxy(14, CurrentLine);
							char name[57];
							name[56] = '\0';
							strncpy(name, p->Data.name, 56);
							printf("%s", name);
							printf("...");
						}
						if (strlen(p->Data.author) <= 29)
						{
							gotoxy(74, CurrentLine);
							printf("%s", p->Data.author);
						}
						else
						{
							gotoxy(74, CurrentLine);
							char author[27];
							author[26] = '\0';
							strncpy(author, p->Data.author, 26);
							printf("%s", author);
							printf("...");
						}
						gotoxy(104, CurrentLine); printf("%d", p->Data.number);
						VerticalLine(13, CurrentLine, 1, 15, 9);
						VerticalLine(73, CurrentLine, 1, 15, 9);
						VerticalLine(103, CurrentLine, 1, 15, 9);

						Node *q = p->pPrev;
						for (int i = 1; i <= CurrentSelect; i++) //8->0
						{
							drawRectangle(0, CurrentLine - i, MAXWIDTH, 1, 3);
							gotoxy(0, CurrentLine - i); printf("%s", q->Data.ISBN);
							if (strlen(q->Data.name) <= 59)
							{
								gotoxy(14, CurrentLine - i);
								printf("%s", q->Data.name);
							}
							else
							{
								gotoxy(14, CurrentLine - i);
								char name[57];
								name[56] = '\0';
								strncpy(name, q->Data.name, 56);
								printf("%s", name);
								printf("...");
							}
							if (strlen(q->Data.author) <= 29)
							{
								gotoxy(74, CurrentLine - i);
								printf("%s", q->Data.author);
							}
							else
							{
								gotoxy(74, CurrentLine - i);
								char author[27];
								author[26] = '\0';
								strncpy(author, q->Data.author, 26);
								printf("%s", author);
								printf("...");
							}
							gotoxy(104, CurrentLine - i); printf("%d", q->Data.number);
							VerticalLine(13, CurrentLine - i, 1, 15, 3);
							VerticalLine(73, CurrentLine - i, 1, 15, 3);
							VerticalLine(103, CurrentLine - i, 1, 15, 3);
							q = q->pPrev;
							if (q == NULL) break;
						}
					}
				}
			}

			FullBooksInfo(0, 18, 0, 15, p);

			//F12:BACK
			if (ch == 134)
			{
				drawRectangle(36, 6, 48, 21, 15);
				int n;
				char list[11];
				SetBG();
				ReadBooksMenuData(n, list);
				BooksMenu(n, list);
				break;
			}
			ch = getch();
		}
	}
}

void ViewListBooks()
{
	Title(">>DANH SACH CAC QUYEN SACH");
	Nocursortype();
	drawRectangle(0, 6, MAXWIDTH, 1, 1);
	textBgColor(15, 1);
	gotoxy(4, 6); printf("ISBN");
	gotoxy(39, 6); printf("TEN SACH");
	gotoxy(85, 6); printf("TAC GIA");
	gotoxy(108, 6); printf("SO LUONG");
	VerticalLine(13, 6, 1, 15, 1);
	VerticalLine(73, 6, 1, 15, 1);
	VerticalLine(103, 6, 1, 15, 1);

	drawRectangle(0, 7, MAXWIDTH, 9, 3);
	VerticalLine(13, 7, 9, 15, 3);
	VerticalLine(73, 7, 9, 15, 3);
	VerticalLine(103, 7, 9, 15, 3);

	textBgColor(0, 3);;
	List L = GetBooksData();
	Node *p = L.pHead;

	for (int i = 0; i < 9; i++)
	{
		if (p == NULL) break;
		gotoxy(0, 7 + i); printf("%s", p->Data.ISBN);
		if (strlen(p->Data.name) <= 59)
		{
			gotoxy(14, 7 + i);
			printf("%s", p->Data.name);
		}
		else
		{
			gotoxy(14, 7 + i);
			char name[57];
			name[56] = '\0';
			strncpy(name, p->Data.name, 56);
			printf("%s", name);
			printf("...");
		}
		if (strlen(p->Data.author) <= 29)
		{
			gotoxy(74, 7 + i);
			printf("%s", p->Data.author);
		}
		else
		{
			gotoxy(74, 7 + i);
			char author[27];
			author[26] = '\0';
			strncpy(author, p->Data.author, 26);
			printf("%s", author);
			printf("...");
		}
		gotoxy(104, 7 + i); printf("%d", p->Data.number);
		p = p->pNext;
		if (p == NULL) break;
	}
	MoveSelectBooksView(L, 7, 8);
}

//Bảng nhập thông tin Chỉnh sửa thông tin sách
void ModifyBooksData()
{
	Yescursortype();
	bool BACK = false;	//Biến kiểm tra có bấm 'Trở về' [F12] hay chưa?
	Title(">>CHINH SUA THONG TIN SACH");
	Books book;
	do
	{
		drawRectangle(36, 6, 48, 19, 3);
		//Ghi các thuộc tính của trường nhập
		gotoxy(38, 7);
		printf("Nhap ISBN cua sach: ");
		gotoxy(38, 9);
		printf("Ten sach[100]: ");
		gotoxy(38, 11);
		printf("Tac gia[100]: ");
		gotoxy(38, 13);
		printf("Nha xuat ban[100]: ");
		gotoxy(38, 15);
		printf("Nam xuat ban: ");
		gotoxy(38, 17);
		printf("The loai[100]: ");
		gotoxy(38, 19);
		printf("Gia sach[VND]: ");
		//Vẽ khung input
		drawRectangle(38, 8, 44, 1, 15);
		drawRectangle(38, 10, 44, 1, 15);
		drawRectangle(38, 12, 44, 1, 15);
		drawRectangle(38, 14, 44, 1, 15);
		drawRectangle(38, 16, 44, 1, 15);
		drawRectangle(38, 18, 44, 1, 15);
		drawRectangle(38, 20, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(60, 22);
		printf("ENTER to Modify a book");
		gotoxy(60, 23);
		printf("F12 to Back");
		textBgColor(0, 15);

		//Nhập
		Books A;
		errno_t err;
		//Nhập ISBN
		do
		{
			drawRectangle(36, 9, 48, 3, 3);
			gotoxy(38, 9);
			printf("Ten sach[100]: ");
			gotoxy(38, 11);
			printf("Tac gia[100]: ");
			gotoxy(38, 13);
			printf("Nha xuat ban[100]: ");
			drawRectangle(38, 8, 44, 1, 15);
			drawRectangle(38, 10, 44, 1, 15);

			gotoxy(38, 8);
			int status = InputISBN(A.ISBN);
			if (status == -1)
			{
				BACK = true;
			}

			if (!BACK)
			{
				//Tạo biến link chứa giá trị đường dẫn đến file dữ liệu sách
				char link[100] = "books/";
				strcat(link, A.ISBN);
				strcat(link, ".bin");

				FILE *f;
				err = fopen_s(&f, link, "rb");
				//Nếu sách đã được thêm trước đó
				if (err == 0)
				{
					fread(&book, sizeof(Books), 1, f);
					fclose(f);
					//Nếu sách chưa bị xóa thì in ra thông tin của sách
					if (book.exist)
					{
						textBgColor(0, 3);

						gotoxy(53, 9);
						if (strlen(book.name) <= 29)
						{
							printf("%s", book.name);
						}
						else
						{
							char name[27];
							name[26] = '\0';
							strncpy(name, book.name, 26);
							printf("%s", name);
							printf("...");
						}

						gotoxy(52, 11);
						if (strlen(book.author) <= 30)
						{
							printf("%s", book.author);
						}
						else
						{
							char author[28];
							author[27] = '\0';
							strncpy(author, book.author, 27);
							printf("%s", author);
							printf("...");
						}

						gotoxy(57, 13);
						if (strlen(book.publisher) <= 25)
						{
							printf("%s", book.publisher);
						}
						else
						{
							char publisher[23];
							publisher[22] = '\0';
							strncpy(publisher, book.publisher, 22);
							printf("%s", publisher);
							printf("...");
						}

						gotoxy(52, 15);
						printf("%d", book.published);

						gotoxy(53, 17);
						if (strlen(book.category) <= 24)
						{
							printf("%s", book.category);
						}
						else
						{
							char category[22];
							category[21] = '\0';
							strncpy(category, book.category, 21);
							printf("%s", category);
							printf("...");
						}

						gotoxy(53, 19);
						if (strlen(book.prices) <= 24)
						{
							printf("%s", book.prices);
						}
						else
						{
							char prices[22];
							prices[21] = '\0';
							strncpy(prices, book.prices, 21);
							printf("%s", prices);
							printf("...");
						}

						textBgColor(0, 15);
					}
					//Nếu sách đã bị xóa
					else
					{
						drawRectangle(36, 9, 48, 3, 12);
						gotoxy(51, 10);
						printf("SACH KHONG TON TAI");
						Sleep(1000);
					}
				}
				//Nếu sách chưa được thêm trước đó
				else
				{
					drawRectangle(36, 9, 48, 3, 12);
					gotoxy(51, 10);
					printf("SACH KHONG TON TAI");
					Sleep(1000);
				}
			}

		} while (((strlen(A.ISBN) == 0 || err != 0) || (err == 0 && book.exist == false)) && !BACK);
		//Nhập tên sách
		if (!BACK)
		{
			gotoxy(38, 10);
			int status = InputString100(A.name);
			if (status == -1)
			{
				BACK = true;	//Đã bấm 'Trở về' [F12]
			}
		}
		//Nhập Tác giả
		if (!BACK)
		{
			gotoxy(38, 12);
			int status = InputString100(A.author);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Nhà xuất bản
		if (!BACK)
		{
			gotoxy(38, 14);
			int status = InputString100(A.publisher);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Năm xuất bản
		if (!BACK)
		{
			gotoxy(38, 16);
			A.published = Input4Num();
			if (A.published == -1)
			{
				BACK = true;
			}
		}
		//Nhập Thể loại
		if (!BACK)
		{
			gotoxy(38, 18);
			int status = InputString100(A.category);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Giá sách
		if (!BACK)
		{
			gotoxy(38, 20);
			int status = InputMoney(A.prices);
			if (status == -1)
			{
				BACK = true;
			}
		}

		int n;
		char list[11];
		char user[21], pass[21];
		ReadBooksMenuData(n, list);
		ReadCacheAccount(user, pass);

		//Nếu chưa ấn 'Trở về' [F12]
		if (!BACK)
		{
			//Tạo biến link chứa giá trị đường dẫn đến file dữ liệu sách
			char link[100] = "books/";
			strcat(link, A.ISBN);
			strcat(link, ".bin");

			FILE *f;
			Books B;
			errno_t err = fopen_s(&f, link, "rb");
			if (err == 0)
			{
				fread(&B, sizeof(Books), 1, f);
				fclose(f);
			}

			if (strlen(A.name) != 0)
				strcpy(B.name, A.name);
			if (strlen(A.author) != 0)
				strcpy(B.author, A.author);
			if (strlen(A.publisher) != 0)
				strcpy(B.publisher, A.publisher);
			if (A.published != 0)
				B.published = A.published;
			if (strlen(A.category) != 0)
				strcpy(B.category, A.category);
			if (strlen(A.prices) != 0)
				strcpy(B.prices, A.prices);


			err = fopen_s(&f, link, "wb");
			if (err == 0)
			{
				fwrite(&B, sizeof(Books), 1, f);
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
			BooksMenu(n, list);
			break;
		}
	} while (!BACK);
	gotoxy(44, 0);
}

//Thao tác Xóa thông tin một quyển sách thao ISBN
void DeleteBook()
{
	bool BACK = false;
	Title(">>XOA THONG TIN SACH");
	drawRectangle(36, 6, 48, 7, 3);
	gotoxy(38, 7);
	printf("Nhap ISBN sach can xoa: ");
	drawRectangle(38, 8, 44, 1, 15);
	Books A;
	errno_t err;

	//Nhập ISBN
	do
	{
		drawRectangle(36, 9, 48, 3, 3);
		drawRectangle(38, 8, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(60, 10);
		printf("ENTER to Delete a book");
		gotoxy(60, 11);
		printf("F12 to Back");
		textBgColor(0, 15);

		gotoxy(38, 8);
		int status = InputISBN(A.ISBN);
		if (status == -1)
		{
			BACK = true;
		}
		//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
		if (!BACK)
		{
			//Tạo biến link chứa giá trị đường dẫn đến file dữ liệu sách
			char link[100] = "books/";
			strcat(link, A.ISBN);
			strcat(link, ".bin");

			FILE *f;
			err = fopen_s(&f, link, "rb");
			//Nếu sách tồn tại trước đó
			if (err == 0)
			{
				Books book;
				fread(&book, sizeof(Books), 1, f);
				fclose(f);

				//Nếu sách chưa bị xóa
				if (book.exist)
				{
					//Chuyển sang trạng thái xóa
					book.exist = false;
					//Cập nhật dữ liệu
					err = fopen_s(&f, link, "wb");
					if (err == 0)
					{
						fwrite(&book, sizeof(Books), 1, f);
						fclose(f);
					}
					//In thông báo
					drawRectangle(36, 9, 48, 3, 10);
					gotoxy(51, 10);
					printf("XOA SACH THANH CONG");
					Sleep(1000);
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
			//Trở về BooksMenu
			int n;
			char list[10];
			ReadBooksMenuData(n, list);
			drawRectangle(36, 6, 48, 7, 15);
			BooksMenu(n, list);
			break;
		}

	} while (!BACK);
}

void FullBooksInfoISBN(int posX, int posY, int TextColor, int BgColor, Books book)
{
	drawRectangle(posX, posY, 112, 8, 15);
	textBgColor(TextColor, BgColor);
	gotoxy(posX, posY);
	printf("- ISBN: %s", book.ISBN);
	gotoxy(posX, posY + 1);
	printf("- Ten sach: %s", book.name);
	gotoxy(posX, posY + 2);
	printf("- Tac gia: %s", book.author);
	gotoxy(posX, posY + 3);
	printf("- Nha xuat ban: %s", book.publisher);
	gotoxy(posX, posY + 4);
	printf("- Nam xuat ban: %d", book.published);
	gotoxy(posX, posY + 5);
	printf("- The loai: %s", book.category);
	gotoxy(posX, posY + 6);
	printf("- Gia sach: %s", book.prices);
	gotoxy(posX, posY + 7);
	printf("- So luong sach: %d", book.number);
}

void SearchBookISBN()
{
	bool BACK = false;
	Title(">>TIM KIEM SACH THEO ISBN");
	drawRectangle(36, 6, 48, 7, 3);
	gotoxy(38, 7);
	printf("Nhap ISBN: ");
	drawRectangle(38, 8, 44, 1, 15);
	Books A;
	errno_t err;

	//Nhập ISBN
	do
	{
		drawRectangle(36, 9, 48, 3, 3);
		drawRectangle(38, 8, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(60, 10);
		printf("ENTER to Search a book");
		gotoxy(60, 11);
		printf("F12 to Back");
		textBgColor(0, 15);

		gotoxy(38, 8);
		int status = InputISBN(A.ISBN);
		if (status == -1)
		{
			BACK = true;
		}
		//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
		if (!BACK)
		{
			char link[128];
			strcpy(link, Path("books/", A.ISBN, ".bin"));
			FILE *f;
			err = fopen_s(&f, link, "rb");
			//Nếu sách tồn tại trước đó
			if (err == 0)
			{
				Books book;
				fread(&book, sizeof(Books), 1, f);
				fclose(f);

				//Nếu sách chưa bị xóa
				if (book.exist)
				{
					FullBooksInfoISBN(0, 18, 0, 15, book);
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
			//Trở về BooksMenu
			int n;
			char list[10];
			drawRectangle(0, 18, 112, 8, 15);
			ReadBooksMenuData(n, list);
			drawRectangle(36, 6, 48, 7, 15);
			BooksMenu(n, list);
			break;
		}

	} while (!BACK);
}

void ViewListBooksSearchName(List L)
{
	//Title(">>DANH SACH CAC QUYEN SACH");
	Nocursortype();
	drawRectangle(0, 13, MAXWIDTH, 1, 1);
	textBgColor(15, 1);
	gotoxy(4, 13); printf("ISBN");
	gotoxy(39, 13); printf("TEN SACH");
	gotoxy(85, 13); printf("TAC GIA");
	gotoxy(108, 13); printf("SO LUONG");
	VerticalLine(13, 13, 1, 15, 1);
	VerticalLine(73, 13, 1, 15, 1);
	VerticalLine(103, 13, 1, 15, 1);

	drawRectangle(0, 14, MAXWIDTH, 3, 3);
	VerticalLine(13, 14, 3, 15, 3);
	VerticalLine(73, 14, 3, 15, 3);
	VerticalLine(103, 14, 3, 15, 3);

	textBgColor(0, 3);

	Node *p = L.pHead;

	for (int i = 0; i < 3; i++)
	{
		if (p == NULL) break;
		gotoxy(0, 14 + i); printf("%s", p->Data.ISBN);
		if (strlen(p->Data.name) <= 59)
		{
			gotoxy(14, 14 + i);
			printf("%s", p->Data.name);
		}
		else
		{
			gotoxy(14, 14 + i);
			char name[57];
			name[56] = '\0';
			strncpy(name, p->Data.name, 56);
			printf("%s", name);
			printf("...");
		}
		if (strlen(p->Data.author) <= 29)
		{
			gotoxy(74, 14 + i);
			printf("%s", p->Data.author);
		}
		else
		{
			gotoxy(74, 14 + i);
			char author[27];
			author[26] = '\0';
			strncpy(author, p->Data.author, 26);
			printf("%s", author);
			printf("...");
		}
		gotoxy(104, 14 + i); printf("%d", p->Data.number);
		p = p->pNext;
		if (p == NULL) break;
	}
	MoveSelectBooksView(L, 14, 2);
}

void SearchBookName()
{
	bool BACK = false;
	Title(">>TIM KIEM SACH THEO TEN");
	drawRectangle(36, 6, 48, 7, 3);
	gotoxy(38, 7);
	printf("Nhap Ten: ");
	drawRectangle(38, 8, 44, 1, 15);
	Books A;
	errno_t err;

	//Nhập tên sách
	do
	{
		drawRectangle(36, 9, 48, 3, 3);
		drawRectangle(38, 8, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(60, 10);
		printf("ENTER to Search a book");
		gotoxy(60, 11);
		printf("F12 to Back");
		textBgColor(0, 15);

		gotoxy(38, 8);
		int status = InputString100(A.name);
		if (status == -1)
		{
			BACK = true;
		}
		//Nếu chưa bấm 'Trở về' thì Xử lý dữ liệu
		if (!BACK)
		{
			List L = GetBooksData();
			List L2;
			Init(L2);
			Node *p;
			for (p = L.pTail; p != NULL; p = p->pPrev)
			{
				if (strstr(p->Data.name, A.name) != NULL)
				{
					Insert_first(L2, p->Data);
				}
			}
			if (Len(L2) > 0)
			{
				ViewListBooksSearchName(L2);
				break;
			}
			else
			{
				//In thông báo
				drawRectangle(36, 9, 48, 3, 12);
				gotoxy(51, 10);
				printf("SACH KHONG TON TAI");
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
			ReadBooksMenuData(n, list);
			//drawRectangle(36, 6, 48, 7, 15);
			BooksMenu(n, list);
			break;
		}

	} while (!BACK);
}