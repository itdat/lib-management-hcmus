#include "stdio.h"
#include "conio.h"
#include "windows.h"
#include "consolegraph.h"
#include "menu.h"
#include "stdlib.h"
#include "library-management.h"
#include "cache.h"
#include "input.h"
#include "users.h"

//Hàm tạo giao diện đăng nhập cho người dùng
void LayoutLogin(char username[], char password[])
{
	Yescursortype();
	//Vẽ khung tên phần mềm [NỀN ĐỎ] chỉ trạng thái chưa đăng nhập
	DrawAppNameTab(0, 4);

	//Vẽ khung đăng nhập
	drawRectangle(47, 6, 27, 10, 3);
	gotoxy(48, 7);
	printf("Username: ");
	gotoxy(48, 10);
	printf("Password: ");

	//Vẽ khung input
	drawRectangle(48, 8, 25, 1, 15);
	drawRectangle(48, 11, 25, 1, 15);
	gotoxy(57, 14);
	printf("ENTER to login");

	//Nhập
	gotoxy(48, 8);
	InputUsername(username);
	gotoxy(48, 11);
	InputPassword(password);
	gotoxy(44, 0);
}

//Hàm trả về loại người dùng, -1 nếu <USERNAME> hoặc <PASSWORD> không chính xác
int Login(char username[], char password[])
{
	/*
		1: admin
		2: manager
		3: expert
	*/

	errno_t error;
	FILE *f;
	error = fopen_s(&f, "user/admin/admin.bin", "rb");
	if (error == 0)
	{
		Accounts ad;
		fread(&ad, sizeof(Accounts), 1, f);
		fclose(f);
		//Tài khoản Admin luôn ở trạng thái ACTIVE
		if ((strcmp(username, ad.username) == 0) && (strcmp(password, ad.password) == 0))
		{
			WriteCacheAccount(username, password);
			return 1;
		}
	}
	else
	{
		if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0)
		{
			WriteCacheAccount(username, password);
			Accounts root_admin;
			strcpy(root_admin.username, "admin");
			strcpy(root_admin.password, "admin");
			root_admin.active = true;
			strcpy(root_admin.fullname, "Nguyen Tuan Dat");
			Day dob = { 13,10,1999 };
			root_admin.DoB = dob;
			strcpy(root_admin.ID, "123456789");
			strcpy(root_admin.address, "TP. Ho Chi Minh");
			root_admin.sex = 1;
			root_admin.classification = 1;
			WriteAccount("user/admin/admin.bin", root_admin);
			return 1;
		}
	}

	char link[100] = "user/managers/";
	strcat(link, username);
	strcat(link, ".bin");
	error = fopen_s(&f, link, "rb");
	if (error == 0)
	{
		Accounts member;
		while (fread(&member, sizeof(Accounts), 1, f)!=NULL)
		{
			if ((strcmp(username, member.username) == 0) && (strcmp(password, member.password) == 0))
			{
				if (member.active)
				{
					WriteCacheAccount(username, password);
					return 2;
				}
			}
		}
		fclose(f);
	}

	strcpy(link, "user/experts/");
	strcat(link, username);
	strcat(link, ".bin");
	error = fopen_s(&f, link, "rb");
	if (error == 0)
	{
		Accounts member;
		while (fread(&member, sizeof(Accounts), 1, f) != NULL)
		{
			if ((strcmp(username, member.username) == 0) && (strcmp(password, member.password) == 0))
			{
				if (member.active)
				{
					WriteCacheAccount(username, password);
					return 3;
				}
			}
		}
		fclose(f);
	}

	return -1;
}

//Hàm nhận vào loại người dùng để đưa vào [MENU] với tính năng tương ứng
void CaseLogin(int n)
{
	FILE *f = fopen("cache/currentMenu.txt", "w");	//Viết vào cache trạng thái menu
	FILE *g = fopen("cache/currentClassification.txt", "w");	//Viết vào cache loại người dùng
	switch (n)
	{
	case 1:	//admin
		fprintf(g, "%s", "1");
		fclose(g);
		fprintf(f, "%d %s", 9, "111111111");
		fclose(f);
		Menu(9, "111111111");
		break;
	case 2:	//manager
		fprintf(g, "%s", "2");
		fclose(g);
		fprintf(f, "%d %s", 8, "110111111");
		fclose(f);
		Menu(8, "110111111");
		break;
	case 3:	//expert
		fprintf(g, "%s", "3");
		fclose(g);
		fprintf(f, "%d %s", 8, "110111111");
		fclose(f);
		Menu(8, "110111111");
		break;
	default:
		break;
	};
}

//Lặp lại bước nhập <USERNAME> và <PASSWORD> đến khi nào đăng nhập thành công hoặc ấn phím [ESC]
void RepeatInput(char username[], char password[])
{
	int statusLogin;
	//SetBG();
	do
	{
		drawRectangle(36, 9, 48, 3, 15);
		LayoutLogin(username, password);
		statusLogin = Login(username, password);
		if (statusLogin == -1)
		{
			drawRectangle(36, 9, 48, 3, 12);
			gotoxy(51, 10);
			printf("DANG NHAP THAT BAI");
			Sleep(900);
		}
	} while (statusLogin == -1);
	CaseLogin(statusLogin);
}

//Đăng xuất
void LogOut()
{
	WriteCacheAccount("###", "###");
	char username[21], password[21];
	Title(" ");
	drawRectangle(36, 6, 48, 10, 15);
	RepeatInput(username, password);
}