// LibraryManagement.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "windows.h"
#include "consolegraph.h"
#include "login.h"
#include "library-management.h"
#include "cache.h"
#include "function-standard.h"

int main(int argc, char *argv[])
{
	if (argc == 3)
	{
		int Status = Login(argv[1], argv[2]);
		if (Status == -1)
		{
			printf("Dang Nhap That Bai. ");
			system("pause");
		}
		else
		{
			SetBG();
			CaseLogin(Status);
		}
	}
	else
		if (argc == 2)
		{
			if (strcmp(argv[1], "logout") == 0)
			{
				SetBG();
				LogOut();
			}
			else
			{
				printf("Lenh Nhap Sai. ");
				system("pause");
			}
		}
		else
			if (argc == 1)
			{
				char username[21], password[21];	//Tài khoản và mật khẩu tối đa 20 kí tự
				initSystemFolder();
				if (ReadCacheAccount(username, password) == 1)	//Đọc từ cache <USERNAME> và <PASSWORD>
				{
					SetBG();
					CaseLogin(Login(username, password));
				}
				else
				{
					SetBG();
					RepeatInput(username, password);
				}
			}
			else
			{
				printf("Lenh Nhap Sai. ");
				system("pause");
			}
	textBgColor(15, 0);
	system("cls");
	return 0;
}
