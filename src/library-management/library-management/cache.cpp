#include "stdio.h"
#include "conio.h"
#include "windows.h"
#include "consolegraph.h"
#include "menu.h"
#include "stdlib.h"
#include "library-management.h"
#include "cache.h"

//Ghi vào cache Tài khoản và mật khẩu đăng nhập hiện hành
void WriteCacheAccount(char username[], char password[])
{
	FILE *f = fopen("cache/currentAccount.txt", "w");
	fprintf(f, "%s %s", username, password);
	fclose(f);
}

//Đọc từ cache Tài khoản và mật khẩu đăng nhập hiện hành
int ReadCacheAccount(char username[], char password[])
{
	FILE *f = fopen("cache/currentAccount.txt", "r");
	if (f)
	{
		fscanf(f, "%s%s", username, password);
		fclose(f);
		if (strcmp(username, "###") == 0)
			return 0;
		return 1;
	}
}

//Hàm trả về phân quyền của tài khoản hiện tại
int ReadClassification()
{
	int n;
	FILE *f = fopen("cache/currentClassification.txt", "r");
	if (f)
	{
		fscanf(f, "%d", &n);
		fclose(f);
		return n;
	}
	return -1;
}

//Đọc từ cache định dạng [MENU]
void ReadMenuData(int &n, char list[])
{
	FILE *f = fopen("cache/currentMenu.txt", "r");
	if (f)
	{
		fscanf(f, "%d%s", &n, list);
	}
	fclose(f);
}

//Đọc từ cache định dạng [BOOKSMENU]
void ReadBooksMenuData(int &n, char list[])
{
	FILE *f = fopen("cache/currentBooksMenu.txt", "r");
	if (f)
	{
		fscanf(f, "%d%s", &n, list);
	}
	fclose(f);
}

//Đọc từ cache định dạng [READERSMENU]
void ReadReadersMenuData(int &n, char list[])
{
	FILE *f = fopen("cache/currentReadersMenu.txt", "r");
	if (f)
	{
		fscanf(f, "%d%s", &n, list);
	}
	fclose(f);
}