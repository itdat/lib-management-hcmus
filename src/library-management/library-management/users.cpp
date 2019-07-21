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
#include "input.h"

//Cho biết <USERNAME> có khả dụng cho việc tạo mới hay không?
bool AcceptUser(char username[])
{
	if (strcmp(username, "admin") == 0) return false;	//Nếu tài khoản đăng kí mới trùng tên admin thì trả về false

	bool ACCEPT = true;

	//Kiểm tra các tài khoản thuộc nhóm Quản lý
	char link[100] = "user/managers/";
	strcat(link, username);
	strcat(link, ".bin");
	errno_t error;
	FILE *f;
	error = fopen_s(&f, link, "rb");
	if (error == 0)	//Mở được file để đọc
	{
		Accounts A;
		fread(&A, sizeof(Accounts), 1, f);
		fclose(f);
		if (A.active)
			ACCEPT = false;	//ACCEPT bằng false chỉ khi tài khoản đã được tạo trước đó và vẫn còn đang trạng thái ACTIVE
	}

	//Kiểm tra các tài khoản thuộc nhóm Chuyên viên
	strcpy(link, "user/experts/");
	strcat(link, username);
	strcat(link, ".bin");
	error = fopen_s(&f, link, "rb");
	if (error == 0)	//Mở được file để đọc
	{
		Accounts A;
		fread(&A, sizeof(Accounts), 1, f);
		fclose(f);
		if (A.active)
			ACCEPT = false;
	}
	return ACCEPT;
}

//Thêm Account
void AddAccount(Accounts A)
{
	char LINK[100], link[100], listlink[100];
	if (A.classification == 1)
		strcpy(LINK, "user/managers/");
	else
		strcpy(LINK, "user/experts/");

	strcpy(link, LINK);
	strcat(link, A.username);
	strcat(link, ".bin");

	errno_t error;
	FILE *f;
	error = fopen_s(&f, link, "rb");
	if (error != 0)	//Không mở được file để đọc
	{
		strcpy(listlink, LINK);
		strcat(listlink, "List.txt");
		fopen_s(&f, listlink, "a");
		fprintf(f, "%s\n", A.username);
		fclose(f);
	}
	else
		fclose(f);

	A.active = true;

	fopen_s(&f, link, "wb");
	fwrite(&A, sizeof(Accounts), 1, f);
	fclose(f);
}

//Bảng nhập thông tin Tạo người dùng mới
void InputUserData()
{
	bool BACK = false;	//Biến kiểm tra có bấm 'Trở về' [F12] hay chưa?
	Title(">>TAO NGUOI DUNG MOI");
	do
	{
		//Vẽ khung đăng nhập
		drawRectangle(36, 6, 48, 21, 3);
		//Ghi các thuộc tính của trường nhập
		gotoxy(38, 7);
		printf("Username[20]: ");
		gotoxy(38, 9);
		printf("Password[20]: ");
		gotoxy(38, 11);
		printf("Ho va ten[44]: ");
		gotoxy(38, 13);
		printf("Ngay sinh: dd/mm/yyyy");
		gotoxy(38, 15);
		printf("CMND[44]: ");
		gotoxy(38, 17);
		printf("Dia chi[100]: ");
		gotoxy(38, 19);
		printf("Gioi tinh: 1->Nam ; 2-> Nu");
		gotoxy(38, 21);
		printf("Phan quyen: 1->Quan ly ; 2->Chuyen vien");
		//Vẽ các trường nhập
		drawRectangle(38, 8, 44, 1, 15);
		drawRectangle(38, 10, 44, 1, 15);
		drawRectangle(38, 12, 44, 1, 15);
		drawRectangle(38, 14, 44, 1, 15);
		gotoxy(40, 14);
		printf("/  /");
		drawRectangle(38, 16, 44, 1, 15);
		drawRectangle(38, 18, 44, 1, 15);
		drawRectangle(38, 20, 44, 1, 15);
		drawRectangle(38, 22, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(60, 24);
		printf("ENTER to Creat account");
		gotoxy(60, 25);
		printf("F12 to Back");
		textBgColor(0, 15);
		//Nhập <USERNAME>
		Accounts A;
		do
		{
			gotoxy(38, 8);
			int status = InputUsername(A.username);
			if (status == -1)
			{
				BACK = true;	//Đã bấm 'Trở về' [F12]
			}
		} while (strlen(A.username) == 0 && !BACK);
		//Nhập Mật khẩu
		if (!BACK)
		{
			do
			{
				gotoxy(38, 10);
				int status = InputPassword(A.password);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.password) == 0 && !BACK);
		}
		//Nhập Họ tên
		if (!BACK)
		{
			do
			{
				gotoxy(38, 12);
				int status = InputFullname(A.fullname);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.fullname) == 0 && !BACK);
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
		//Nhập CMND
		if (!BACK)
		{
			do
			{
				gotoxy(38, 16);
				int status = InputIndentity(A.ID);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.ID) == 0 && !BACK);
		}
		//Nhập Địa chỉ
		if (!BACK)
		{
			do
			{
				gotoxy(38, 18);
				int status = InputAddress(A.address);
				if (status == -1)
				{
					BACK = true;
				}
			} while (strlen(A.address) == 0 && !BACK);
		}
		//Nhập Giới tính
		if (!BACK)
		{
			gotoxy(38, 20);
			A.sex = Input1Num();
			if (A.sex == -1)
			{
				BACK = true;
			}
		}
		//Nhập Phân quyền
		if (!BACK)
		{
			gotoxy(38, 22);
			A.classification = Input1Num();
			if (A.classification == -1)
			{
				BACK = true;
			}
		}

		int n;
		char list[11];
		char user[21], pass[21];
		ReadMenuData(n, list);
		ReadCacheAccount(user, pass);

		//Nếu chưa ấn 'Trở về' [F12]
		if (!BACK)
		{
			//Nếu username khả dụng thì tạo mới tài khoản kèm thông báo tạo thành công
			if (AcceptUser(A.username))
			{
				AddAccount(A);
				drawRectangle(36, 12, 48, 3, 10);
				char Alert[100] = "Tao thanh cong ";
				strcat(Alert, A.username);
				gotoxy(36 + (48 - strlen(Alert)) / 2, 13);
				printf("%s", Alert);
			}
			//Nếu username không khả dụng thì thông báo tài khoản đã được sử dụng
			else
			{
				drawRectangle(36, 12, 48, 3, 12);
				gotoxy(37, 13);
				char Alert[100] = "Tai khoan ";
				strcat(Alert, A.username);
				strcat(Alert, " da duoc su dung");
				gotoxy(36 + (48 - strlen(Alert)) / 2, 13);
				printf("%s", Alert);
			}
			//Ngưng chương trình 1s để người dùng đọc thông báo
			Sleep(1000);
		}
		//Nếu đã ấn 'Trở về' [F12]
		else
		{
			drawRectangle(36, 6, 48, 21, 15);
			Menu(n, list);
			break;
		}
	} while (!BACK);
	gotoxy(44, 0);
}


//Hàm trả về dữ liệu tài khoản theo đường dẫn <LINK>
Accounts ReadAccount(char link[])
{
	Accounts B;
	FILE *f = fopen(link, "rb");
	if (f)
	{
		fread(&B, sizeof(Accounts), 1, f);
		fclose(f);
	}
	return B;
}

//Viết dữ liệu <USER> vào file với đường dẫn <LINK>
int WriteAccount(char link[], Accounts user)
{
	fcloseall();
	FILE *f;
	errno_t err = fopen_s(&f, link, "wb");
	if (err == 0)
	{
		fwrite(&user, sizeof(Accounts), 1, f);
		fclose(f);
		return 1;
	}
	return 0;
}

//Thay đổi mật khẩu
void ChangePassword()
{
	Title(">>THAY DOI MAT KHAU");
	//Vẽ khung
	drawRectangle(36, 6, 48, 11, 3);
	//In các tiêu đề của trường nhập
	gotoxy(38, 7);
	printf("Nhap lai mat khau cu: ");
	gotoxy(38, 9);
	printf("Nhap mat khau moi: ");
	gotoxy(38, 11);
	printf("Xac nhan mat khau moi: ");
	//Vẽ trường nhập
	drawRectangle(38, 8, 44, 1, 15);
	drawRectangle(38, 10, 44, 1, 15);
	drawRectangle(38, 12, 44, 1, 15);
	//Vẽ nút chức năng
	textBgColor(0, 7);
	gotoxy(58, 14);
	printf("ENTER to Change Password");
	gotoxy(58, 15);
	printf("F12 to Back");
	textBgColor(0, 15);

	//Thực thi
	bool BACK = false;
	char user[21], pass[21];
	ReadCacheAccount(user, pass);
	char currentPassword[21], newPassword[21], confirmPassword[21];
	int status;
	
	do
	{
		drawRectangle(36, 9, 48, 3, 3);
		gotoxy(38, 9);
		printf("Nhap mat khau moi: ");
		gotoxy(38, 11);
		printf("Xac nhan mat khau moi: ");
		drawRectangle(38, 8, 44, 1, 15);
		drawRectangle(38, 10, 44, 1, 15);
		drawRectangle(38, 12, 44, 1, 15);

		gotoxy(38, 8);
		status = InputPassword(currentPassword);
		if (status == -1)
		{
			BACK = true;
		}
		if (!BACK) {
			if (strcmp(currentPassword, pass) != 0)
			{
				drawRectangle(36, 9, 48, 3, 12);
				gotoxy(51, 10);
				printf("NHAP SAI MAT KHAU");
				Sleep(1000);
			}
		}
		else
		{
			int n;
			char list[11];
			ReadMenuData(n, list);
			drawRectangle(36, 6, 48, 11, 15);
			Menu(n, list);
			break;
		}
	} while (strcmp(currentPassword, pass) != 0 || BACK);

	if (!BACK)
	{
		do
		{
			drawRectangle(36, 9, 48, 3, 3);
			gotoxy(38, 9);
			printf("Nhap mat khau moi: ");
			gotoxy(38, 11);
			printf("Xac nhan mat khau moi: ");

			drawRectangle(38, 10, 44, 1, 15);
			drawRectangle(38, 12, 44, 1, 15);

			if (!BACK)
			{
				gotoxy(38, 10);
				status = InputPassword(newPassword);
				if (status == -1)
				{
					BACK = true;
				}
			}
			if (!BACK)
			{
				gotoxy(38, 12);
				status = InputPassword(confirmPassword);
				if (status == -1)
				{
					BACK = true;
				}
			}
			if (!BACK)
			{
				if (strcmp(newPassword, confirmPassword) != 0)
				{
					drawRectangle(36, 9, 48, 3, 12);
					gotoxy(46, 10);
					printf("MAT KHAU XAC NHAN KHONG DUNG");
					Sleep(1000);
				}
				else
				{
					int k = ReadClassification();

					//Tạo đường dẫn đến file người dùng
					char link[256];
					if (k == 1)
						strcpy(link, "user/admin/");
					if (k == 2)
						strcpy(link, "user/managers/");
					if (k == 3)
						strcpy(link, "user/experts/");
					strcat(link, user);

					strcat(link, ".bin\0");

					Accounts A = ReadAccount(link);

					//Cập nhật mật khẩu mới
					strcpy(A.password, newPassword);

					WriteAccount(link, A);

					FILE *f = fopen("cache/currentAccount.txt", "w");
					if (f)
					{
						fprintf(f, "%s %s", user, newPassword);
						fclose(f);
					}
					

					drawRectangle(36, 9, 48, 3, 10);
					gotoxy(46, 10);
					printf("THAY DOI MAT KHAU THANH CONG");
					Sleep(1000);

					int n;
					char list[11];
					ReadMenuData(n, list);
					drawRectangle(36, 6, 48, 11, 15);
					Menu(n, list);
					break;
				}
			}
			else
			{
				int n;
				char list[11];
				ReadMenuData(n, list);
				SetBG();
				Menu(n, list);
				break;
			}
		} while (strcmp(newPassword, confirmPassword) != 0 || BACK);
	}
	gotoxy(44, 0);
}

//Chỉnh sửa thông tin
void ModifyInfo()
{
	bool BACK = false;
	Title(">>CHINH SUA THONG TIN");
	do
	{
		int n;
		char list[11];
		char user[21], pass[21];
		ReadMenuData(n, list);
		ReadCacheAccount(user, pass);
		int k = ReadClassification();

		//Tạo đường dẫn đến file người dùng
		char link[256];
		if (k == 1)
		{
			strcpy(link, "user/admin/");
		}
		if (k == 2)
		{
			strcpy(link, "user/managers/");
		}
		if (k == 3)
		{
			strcpy(link, "user/experts/");
		}
		strcat(link, user);
		strcat(link, ".bin\0");

		Accounts A = ReadAccount(link);

		//Vẽ khung nhập thông tin
		drawRectangle(36, 6, 48, 20, 3);
		//Ghi các thuộc tính của trường nhập và Thông tin của tài khoản hiện hành
		gotoxy(38, 7);
		printf("Ho va ten[44]: ");
		gotoxy(38, 8);
		if (strlen(A.fullname) > 0)
		{
			printf("%s", A.fullname);
		}
		else
		{
			printf("<NULL>");
		}
		gotoxy(38, 10);
		printf("Ngay sinh: ");
		gotoxy(38, 11);
		printf("%02d/%02d/%02d", A.DoB.Date, A.DoB.Month, A.DoB.Year);
		gotoxy(38, 13);
		printf("CMND[44]: ");
		gotoxy(38, 14);
		if (strlen(A.ID) > 0)
		{
			printf("%s", A.ID);
		}
		else
		{
			printf("<NULL>");
		}
		gotoxy(38, 16);
		printf("Dia chi[100]:");
		gotoxy(38, 17);
		if (strlen(A.ID) > 0)
		{
			if (strlen(A.address) > 44)
			{
				for (int i = 0; i < 41; i++)
					printf("%c", A.address[i]);
				printf("...");
			}
			else
			{
				printf("%s", A.address);
			}
		}
		else
		{
			printf("<NULL>");
		}
		gotoxy(38, 19);
		printf("Gioi tinh: 1->Nam ; 2-> Nu");
		gotoxy(38, 20);
		if (A.sex == 1)
		{
			printf("Nam");
		}
		else
		{
			if (A.sex == 2)
			{
				printf("Nu");
			}
			else
			{
				printf("Khong xac dinh");
			}
		}
		//Vẽ khung input
		drawRectangle(38, 9, 44, 1, 15);
		drawRectangle(38, 12, 44, 1, 15);
		gotoxy(40, 12);
		printf("/  /");
		drawRectangle(38, 15, 44, 1, 15);
		drawRectangle(38, 18, 44, 1, 15);
		drawRectangle(38, 21, 44, 1, 15);
		//Vẽ nút điều hướng
		textBgColor(0, 7);
		gotoxy(62, 23);
		printf("ENTER to Skip a step");
		gotoxy(62, 24);
		printf("F12 to Back");
		textBgColor(0, 15);

		Accounts B;
		//Nhập Họ tên
		if (!BACK)
		{
			gotoxy(38, 9);
			int status = InputFullname(B.fullname);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Ngày sinh
		if (!BACK)
		{
			gotoxy(38, 12);
			B.DoB.Date = Input2Num();
			if (B.DoB.Date == -1)
			{
				BACK = true;
			}
		}
		if (!BACK)
		{
			gotoxy(41, 12);
			B.DoB.Month = Input2Num();
			if (B.DoB.Month == -1)
			{
				BACK = true;
			}
		}
		if (!BACK)
		{
			gotoxy(44, 12);
			B.DoB.Year = Input4Num();
			if (B.DoB.Year == -1)
			{
				BACK = true;
			}
		}
		//Nhập CMND
		if (!BACK)
		{
			gotoxy(38, 15);
			int status = InputIndentity(B.ID);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Địa chỉ
		if (!BACK)
		{
			gotoxy(38, 18);
			int status = InputAddress(B.address);
			if (status == -1)
			{
				BACK = true;
			}
		}
		//Nhập Giới tính
		if (!BACK)
		{
			gotoxy(38, 21);
			B.sex = Input1Num();
			if (B.sex == -1)
			{
				BACK = true;
			}
		}
		//Nếu chưa bấm 'Trở về' thì Xử lý
		if (!BACK)
		{
			//Cập nhật các trường mà người dùng có nhập thông tin chỉnh sửa
			//Các trường người Dùng không nhập và ấn Enter thì bỏ qua
			if (strlen(B.fullname) != 0)
			{
				strcpy(A.fullname, B.fullname);
			}
			if (B.DoB.Date != 0 && B.DoB.Month != 0 && B.DoB.Year != 0)
			{
				A.DoB.Date = B.DoB.Date;
				A.DoB.Month = B.DoB.Month;
				A.DoB.Year = B.DoB.Year;
			}
			if (strlen(B.ID) != 0)
			{
				strcpy(A.ID, B.ID);
			}
			if (strlen(B.address) != 0)
			{
				strcpy(A.address, B.address);
			}
			if (B.sex != 0)
			{
				A.sex = B.sex;
			}
			//Cập nhật dữ liệu
			WriteAccount(link, A);
			//Thông báo chỉnh sửa thành công
			drawRectangle(36, 12, 48, 3, 10);
			gotoxy(45, 13);
			printf("CHINH SUA THONG TIN THANH CONG");
			Sleep(1000);
		}
		//Nếu đã bấm 'Trở về' thì quay về Main Menu
		else
		{
			drawRectangle(36, 6, 48, 20, 15);
			Menu(n, list);
			break;
		}
	} while (!BACK);
	gotoxy(44, 0);
}