#include "stdafx.h"
#include "conio.h"
#include "consolegraph.h"
#include "windows.h"
#include "linked-list.h"
#include "linked-list-readers.h"
#include "function-standard.h"
#include "repay-bill.h"
#include "cache.h"
#include "menu.h"
void Statistics()
{
	int clss = ReadClassification();
	textBgColor(0, 15);
	system("cls");
	DrawAppNameTab(15, 2);
	Title(">>THONG KE THU VIEN");
	HorizontalLine(2, 6, 116, 0, 15);
	textBgColor(0, 15);

	int Line = 7;

	if (clss != 3)
	{
		List L = GetBooksData();
		int countBook = 0;
		Node *p = L.pHead;
		while (p != NULL)
		{
			countBook += p->Data.number;
			p = p->pNext;
		}
		gotoxy(5, Line++);
		printf("So luong sach: %d", countBook);
		gotoxy(5, Line++);
		printf("So luong sach theo the loai: ");
		char label[100][45];
		int countCategory[100] = { 0 };
		int count = 0;
		p = L.pHead;
		while (p != NULL)
		{
			bool Exist = false;
			for (int i = 0; i < count; i++)
			{
				if (strcmp(p->Data.category, label[i]) == 0)
				{
					Exist = true;
					countCategory[i] += p->Data.number;
					break;
				}
			}
			if (!Exist)
			{
				strcpy(label[count], p->Data.category);
				countCategory[count] += p->Data.number;
				count++;
			}
			p = p->pNext;
		}
		for (int i = 0; i < count; i++)
		{
			gotoxy(7, Line++);
			printf("+ %s: %d", label[i], countCategory[i]);
		}

		List_Reader L_Reader = GetReadersData();
		gotoxy(5, Line++);
		printf("So luong doc gia: %d", Len_Reader(L_Reader));


		Node_Reader *p_reader = L_Reader.pHead;
		int countSex[3] = { 0 };

		while (p_reader != NULL)
		{
			if (p_reader->Data.sex == 1)
				countSex[1]++;
			else
				if (p_reader->Data.sex == 2)
					countSex[2]++;
				else
					countSex[0]++;
			p_reader = p_reader->pNext;
		}
		gotoxy(7, Line++);
		printf("+ Nam: %d", countSex[1]);
		gotoxy(7, Line++);
		printf("+ Nu: %d", countSex[2]);
		gotoxy(7, Line++);
		printf("+ Khac: %d", countSex[0]);
	}

	int bbcount = 0;
	List_Reader L_2 = GetReadersData();
	Node_Reader *p_reader = L_2.pHead;
	while (p_reader != NULL)
	{
		FILE *f;
		char code[10];
		strcpy(code, toStr(p_reader->Data.code));
		char link[128];
		strcpy(link, Path("borrowedbook/", code, ".bin"));
		errno_t error = fopen_s(&f, link, "rb");
		if (error == 0)
		{
			BorrowBook BB;
			while (fread(&BB, sizeof(BorrowBook), 1, f) != 0)
			{
				bbcount++;
			}
			fclose(f);
		}
		p_reader = p_reader->pNext;
	}
	gotoxy(5, Line++);
	printf("So sach dang duoc muon: %d", bbcount);
	gotoxy(5, Line++);
	printf("Danh sach doc gia tre han: ");
	int latecount = 0;
	Day NOW = GetToday();
	p_reader = L_2.pHead;
	while (p_reader != NULL)
	{
		FILE *f;
		char code[10];
		strcpy(code, toStr(p_reader->Data.code));
		char link[128];
		strcpy(link, Path("borrowedbook/", code, ".bin"));
		errno_t error = fopen_s(&f, link, "rb");
		if (error == 0)
		{
			bool isLate = false;
			BorrowBook BB;
			while (fread(&BB, sizeof(BorrowBook), 1, f) != 0)
			{
				int LengthDay = numDay(NOW.Date, NOW.Month, NOW.Year, BB.EndDay.Date, BB.EndDay.Month, BB.EndDay.Year);
				if (LengthDay > 0)
				{
					isLate = true;
					gotoxy(7, Line++);
					printf("+ %09d", p_reader->Data.code);
					break;
				}
			}
			if (isLate) latecount++;
			fclose(f);
		}
		p_reader = p_reader->pNext;
	}
	getch();
	int n;
	char list[10];
	ReadMenuData(n, list);
	SetBG();
	Menu(n, list);
}