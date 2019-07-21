#include "consolegraph.h"
#include "conio.h"
#include "stdio.h"
#include "windows.h"

// Kiểm tra <USERNAME> có đúng quy ước hay không ?
bool TrueCharUser(char x)	//Qui ước <USERNAME> chỉ chứa dấu . _ và các kí tự 0-9, a-z, A-Z
{
	if (x == 46 || x == 95 || (x >= 48 && x <= 57) || (x >= 65 && x <= 90) || (x >= 97 && x <= 122))
		return true;
	return false;
}

//Kiểm tra <PASSWORD> có đúng quy ước hay không?
bool TrueCharPass(char x)	//Qui ước <PASSWORD> từ kí tự 33 đến 126
{
	if (x >= 33 && x <= 126)
		return true;
	return false;
}

//Kiểm tra <FULLNAME> có đúng quy ước hay không?
bool TrueCharFullname(char x)	//Qui ước <FULLNAME> chỉ chứa các kí tự A-Z, a-z
{
	if (x == 32 || (x >= 65 && x <= 90) || (x >= 97 && x <= 122))
		return true;
	return false;
}

//Kiểm tra <CHAR> có phải kí tự số hay không?
bool TrueCharNum(char x)
{
	if (x >= 48 && x <= 57)
		return true;
	return false;
}

//Hàm nhập <USERNAME>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputUsername(char username[])
{
	Yescursortype();
	int len = 0;
	int ch = getch();
	while (ch != 13)	//ENTER
	{
		if (ch == 0)	//Các phím từ F1-F10 kí tự đầu bằng 0
		{
			getch();
		}
		else
		{
			if (ch == 224)	//Thuộc bộ mã ASCII mở rộng kí tự đầu bằng 224
			{
				ch = getch();	//Đọc kí tự phía sau
				if (ch == 134)	//F12
				{
					return -1;
				}
			}
			//Thuộc bộ mã ASCII chuẩn
			else
			{
				//BACKSPACE
				if (ch == 8)
				{
					if (len > 0)
					{
						len--;
						gotoxy(whereX() - 1, whereY());
						printf(" ");
						gotoxy(whereX() - 1, whereY());
					}
				}
				else
				{
					//ESC
					if (ch == 27)
					{
						gotoxy(44, 0);
						textBgColor(15, 0);
						system("cls");
						exit(0);
					}
					//Nếu không phải ENTER, F2, BACKSPACE, ESC
					if (len < 20 && TrueCharUser(ch))
					{
						printf("%c", ch);
						username[len++] = ch;
					}
				}
			}
		}
		ch = getch();
	}
	username[len] = '\0';
	return 0;
}

//Hàm nhập <PASSWORD>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputPassword(char password[])
{
	Yescursortype();
	int len = 0;
	int ch = getch();
	while (ch != 13)	//ENTER
	{
		if (ch == 0)	//Các phím từ F1-F10 kí tự đầu bằng 0
		{
			getch();
		}
		else
		{
			if (ch == 224)	//Thuộc bộ mã ASCII mở rộng kí tự đầu bằng 224
			{
				ch = getch();	//Đọc kí tự phía sau
				if (ch == 134)	//F12
				{
					return -1;
				}
			}
			//Thuộc bộ mã ASCII chuẩn
			else
			{
				//BACKSPACE
				if (ch == 8)
				{
					if (len > 0)
					{
						len--;
						gotoxy(whereX() - 1, whereY());
						printf(" ");
						gotoxy(whereX() - 1, whereY());
					}
				}
				else
				{
					//ESC
					if (ch == 27)
					{
						gotoxy(44, 0);
						textBgColor(15, 0);
						system("cls");
						exit(0);
					}
					//Nếu không phải ENTER, F2, BACKSPACE, ESC
					if (len < 20 && TrueCharPass(ch))
					{
						printf("*");
						password[len++] = ch;
					}
				}
			}
		}
		ch = getch();
	}
	password[len] = '\0';
	return 0;
}

//Hàm nhập <FULLNAME>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputFullname(char fullname[])
{
	Yescursortype();
	int len = 0;
	int ch = getch();
	while (ch != 13)	//ENTER
	{
		if (ch == 0)	//Các phím từ F1-F10 kí tự đầu bằng 0
		{
			getch();
		}
		else
		{
			if (ch == 224)	//Thuộc bộ mã ASCII mở rộng kí tự đầu bằng 224
			{
				ch = getch();	//Đọc kí tự phía sau
				if (ch == 134)	//F12
				{
					return -1;
				}
			}
			//Thuộc bộ mã ASCII chuẩn
			else
			{
				//BACKSPACE
				if (ch == 8)
				{
					if (len > 0)
					{
						len--;
						gotoxy(whereX() - 1, whereY());
						printf(" ");
						gotoxy(whereX() - 1, whereY());
					}
				}
				else
				{
					//ESC
					if (ch == 27)
					{
						gotoxy(44, 0);
						textBgColor(15, 0);
						system("cls");
						exit(0);
					}
					//Nếu không phải ENTER, F2, BACKSPACE, ESC
					if (len < 44 && TrueCharFullname(ch))
					{
						printf("%c", ch);
						fullname[len++] = ch;
					}
				}
			}
		}
		ch = getch();
	}
	fullname[len] = '\0';
	return 0;
}

//Hàm nhập 1 số 1 hoặc 2, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int Input1Num()
{
	Yescursortype();
	char day[2];
	int len = 0;
	int ch = getch();
	while (ch != 13)	//ENTER
	{
		if (ch == 0)	//Các phím từ F1-F10 kí tự đầu bằng 0
		{
			getch();
		}
		else
		{
			if (ch == 224)	//Thuộc bộ mã ASCII mở rộng kí tự đầu bằng 224
			{
				ch = getch();	//Đọc kí tự phía sau
				if (ch == 134)	//F12
				{
					return -1;
				}
			}
			//Thuộc bộ mã ASCII chuẩn
			else
			{
				//BACKSPACE
				if (ch == 8)
				{
					if (len > 0)
					{
						len--;
						gotoxy(whereX() - 1, whereY());
						printf(" ");
						gotoxy(whereX() - 1, whereY());
					}
				}
				else
				{
					//ESC
					if (ch == 27)
					{
						gotoxy(44, 0);
						textBgColor(15, 0);
						system("cls");
						exit(0);
					}
					//Nếu không phải ENTER, F2, BACKSPACE, ESC
					if (len < 1 && (ch == 49 || ch == 50))
					{
						printf("%c", ch);
						day[len++] = ch;
					}
				}
			}
		}
		ch = getch();
	}
	day[len] = '\0';
	return atoi(day);
}

//Hàm nhập 2 số, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int Input2Num()
{
	Yescursortype();
	char day[3];
	int len = 0;
	int ch = getch();
	while (ch != 13)	//ENTER
	{
		if (ch == 0)	//Các phím từ F1-F10 kí tự đầu bằng 0
		{
			getch();
		}
		else
		{
			if (ch == 224)	//Thuộc bộ mã ASCII mở rộng kí tự đầu bằng 224
			{
				ch = getch();	//Đọc kí tự phía sau
				if (ch == 134)	//F12
				{
					return -1;
				}
			}
			//Thuộc bộ mã ASCII chuẩn
			else
			{
				//BACKSPACE
				if (ch == 8)
				{
					if (len > 0)
					{
						len--;
						gotoxy(whereX() - 1, whereY());
						printf(" ");
						gotoxy(whereX() - 1, whereY());
					}
				}
				else
				{
					//ESC
					if (ch == 27)
					{
						gotoxy(44, 0);
						textBgColor(15, 0);
						system("cls");
						exit(0);
					}
					//Nếu không phải ENTER, F2, BACKSPACE, ESC
					if (len < 2 && TrueCharNum(ch))
					{
						printf("%c", ch);
						day[len++] = ch;
					}
				}
			}
		}
		ch = getch();
	}
	day[len] = '\0';
	return atoi(day);
}

//Hàm nhập 4 số, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int Input4Num()
{
	Yescursortype();
	char year[5];
	int len = 0;
	int ch = getch();
	while (ch != 13)	//ENTER
	{
		if (ch == 0)	//Các phím từ F1-F10 kí tự đầu bằng 0
		{
			getch();
		}
		else
		{
			if (ch == 224)	//Thuộc bộ mã ASCII mở rộng kí tự đầu bằng 224
			{
				ch = getch();	//Đọc kí tự phía sau
				if (ch == 134)	//F12
				{
					return -1;
				}
			}
			//Thuộc bộ mã ASCII chuẩn
			else
			{
				//BACKSPACE
				if (ch == 8)
				{
					if (len > 0)
					{
						len--;
						gotoxy(whereX() - 1, whereY());
						printf(" ");
						gotoxy(whereX() - 1, whereY());
					}
				}
				else
				{
					//ESC
					if (ch == 27)
					{
						gotoxy(44, 0);
						textBgColor(15, 0);
						system("cls");
						exit(0);
					}
					//Nếu không phải ENTER, F2, BACKSPACE, ESC
					if (len < 4 && TrueCharNum(ch))
					{
						printf("%c", ch);
						year[len++] = ch;
					}
				}
			}
		}
		ch = getch();
	}
	year[len] = '\0';
	return atoi(year);
}

//Hàm nhập 9 số, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
long Input9Num()
{
	Yescursortype();
	char num9[11];
	int len = 0;
	int ch = getch();
	while (ch != 13)	//ENTER
	{
		if (ch == 0)	//Các phím từ F1-F10 kí tự đầu bằng 0
		{
			getch();
		}
		else
		{
			if (ch == 224)	//Thuộc bộ mã ASCII mở rộng kí tự đầu bằng 224
			{
				ch = getch();	//Đọc kí tự phía sau
				if (ch == 134)	//F12
				{
					return -1;
				}
			}
			//Thuộc bộ mã ASCII chuẩn
			else
			{
				//BACKSPACE
				if (ch == 8)
				{
					if (len > 0)
					{
						len--;
						gotoxy(whereX() - 1, whereY());
						printf(" ");
						gotoxy(whereX() - 1, whereY());
					}
				}
				else
				{
					//ESC
					if (ch == 27)
					{
						gotoxy(44, 0);
						textBgColor(15, 0);
						system("cls");
						exit(0);
					}
					//Nếu không phải ENTER, F2, BACKSPACE, ESC
					if (len < 9 && TrueCharNum(ch))
					{
						printf("%c", ch);
						num9[len++] = ch;
					}
				}
			}
		}
		ch = getch();
	}
	num9[len] = '\0';
	return atoi(num9);
}

//Hàm nhập <ID>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputIndentity(char ID[])
{
	Yescursortype();
	int len = 0;
	int ch = getch();
	while (ch != 13)	//ENTER
	{
		if (ch == 0)	//Các phím từ F1-F10 kí tự đầu bằng 0
		{
			getch();
		}
		else
		{
			if (ch == 224)	//Thuộc bộ mã ASCII mở rộng kí tự đầu bằng 224
			{
				ch = getch();	//Đọc kí tự phía sau
				if (ch == 134)	//F12
				{
					return -1;
				}
			}
			//Thuộc bộ mã ASCII chuẩn
			else
			{
				//BACKSPACE
				if (ch == 8)
				{
					if (len > 0)
					{
						len--;
						gotoxy(whereX() - 1, whereY());
						printf(" ");
						gotoxy(whereX() - 1, whereY());
					}
				}
				else
				{
					//ESC
					if (ch == 27)
					{
						gotoxy(44, 0);
						textBgColor(15, 0);
						system("cls");
						exit(0);
					}
					//Nếu không phải ENTER, F2, BACKSPACE, ESC
					if (len < 44 && TrueCharNum(ch))
					{
						printf("%c", ch);
						ID[len++] = ch;
					}
				}
			}
		}
		ch = getch();
	}
	ID[len] = '\0';
	return 0;
}

//Hàm nhập <ADDRESS>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputAddress(char address[])
{
	Yescursortype();
	int len = 0, leninput = 0;
	int ch = getch();
	while (ch != 13)	//ENTER
	{
		if (ch == 0)	//Các phím từ F1-F10 kí tự đầu bằng 0
		{
			getch();
		}
		else
		{
			if (ch == 224)	//Thuộc bộ mã ASCII mở rộng kí tự đầu bằng 224
			{
				ch = getch();	//Đọc kí tự phía sau
				if (ch == 134)	//F12
				{
					return -1;
				}
			}
			//Thuộc bộ mã ASCII chuẩn
			else
			{
				//Nếu bấm BackSpace
				if (ch == 8)	//BACKSPACE
				{
					//Chỉ thực hiện khi nội dung nhập có độ dài lớn hơn 0
					if (len > 0)
					{
						//Nếu nội dung có độ dài lớn hơn 44 kí tự
						if (leninput > 1)
						{
							len--;
							leninput--;
							gotoxy(whereX() - 1, whereY());
							printf(" ");
							gotoxy(whereX() - 1, whereY());
						}
						//Nếu nội dung có độ dài nhỏ hơn hoặc bằng 44 kí tự
						else
						{
							leninput = 44;
							gotoxy(38, whereY());
							if (len >= 44)
							{
								for (int i = len - 44; i < len; i++)
								{
									printf("%c", address[i]);
								}
							}
							else
							{
								for (int i = 0; i < len; i++)
								{
									printf("%c", address[i]);
								}
							}
							len--;
							leninput--;
							gotoxy(whereX() - 1, whereY());
							printf(" ");
							gotoxy(whereX() - 1, whereY());
						}
					}
				}
				//Nếu không phải là phím BackSpace, không phải là phím F12
				else
				{
					//Nếu bấm ESC thì thoát lập tức chương trình
					if (ch == 27)	//ESC
					{
						gotoxy(44, 0);
						textBgColor(15, 0);
						system("cls");
						exit(0);
					}
					//Nếu không phải là phím BackSpace, F12, ESC
					//Nếu nội dung nhập vào chưa quá 100 kí tự thì vẫn còn nhập được
					if (len < 100 && ch != 9)
					{
						//Nếu nội dung nhập vào chưa quá 44 kí tự (chưa quá khung nhập)
						if (len < 44)
						{
							//Thì in kí tự ra bình thường
							printf("%c", ch);
						}
						//Nếu nội dung tràn khung nhập
						else
						{
							gotoxy(38, whereY());
							for (int i = len - 43; i < len; i++)
							{
								printf("%c", address[i]);
							}
							printf("%c", ch);
						}
						if (leninput < 44) leninput++;
						address[len++] = ch;
					}
				}
			}
		}
		ch = getch();
	}
	address[len] = '\0';
	return 0;
}

int InputString100(char string100[])
{
	Yescursortype();
	int len = 0, leninput = 0;
	int ch = getch();
	while (ch != 13)	//ENTER
	{
		if (ch == 0)	//Các phím từ F1-F10 kí tự đầu bằng 0
		{
			getch();
		}
		else
		{
			if (ch == 224)	//Thuộc bộ mã ASCII mở rộng kí tự đầu bằng 224
			{
				ch = getch();	//Đọc kí tự phía sau
				if (ch == 134)	//F12
				{
					return -1;
				}
			}
			//Thuộc bộ mã ASCII chuẩn
			else
			{
				//Nếu bấm BackSpace
				if (ch == 8)	//BACKSPACE
				{
					//Chỉ thực hiện khi nội dung nhập có độ dài lớn hơn 0
					if (len > 0)
					{
						//Nếu nội dung có độ dài lớn hơn 44 kí tự
						if (leninput > 1)
						{
							len--;
							leninput--;
							gotoxy(whereX() - 1, whereY());
							printf(" ");
							gotoxy(whereX() - 1, whereY());
						}
						//Nếu nội dung có độ dài nhỏ hơn hoặc bằng 44 kí tự
						else
						{
							leninput = 44;
							gotoxy(38, whereY());
							if (len >= 44)
							{
								for (int i = len - 44; i < len; i++)
								{
									printf("%c", string100[i]);
								}
							}
							else
							{
								for (int i = 0; i < len; i++)
								{
									printf("%c", string100[i]);
								}
							}
							len--;
							leninput--;
							gotoxy(whereX() - 1, whereY());
							printf(" ");
							gotoxy(whereX() - 1, whereY());
						}
					}
				}
				//Nếu không phải là phím BackSpace, không phải là phím F12
				else
				{
					//Nếu bấm ESC thì thoát lập tức chương trình
					if (ch == 27)	//ESC
					{
						gotoxy(44, 0);
						textBgColor(15, 0);
						system("cls");
						exit(0);
					}
					//Nếu không phải là phím BackSpace, F12, ESC
					//Nếu nội dung nhập vào chưa quá 100 kí tự thì vẫn còn nhập được
					if (len < 100 && ch != 9)
					{
						//Nếu nội dung nhập vào chưa quá 44 kí tự (chưa quá khung nhập)
						if (len < 44)
						{
							//Thì in kí tự ra bình thường
							printf("%c", ch);
						}
						//Nếu nội dung tràn khung nhập
						else
						{
							gotoxy(38, whereY());
							for (int i = len - 43; i < len; i++)
							{
								printf("%c", string100[i]);
							}
							printf("%c", ch);
						}
						if (leninput < 44) leninput++;
						string100[len++] = ch;
					}
				}
			}
		}
		ch = getch();
	}
	string100[len] = '\0';
	return 0;
}

//Hàm nhập <STRING[44]>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputMoney(char string44[])
{
	Yescursortype();
	int len = 0;
	int ch = getch();
	while (ch != 13)	//ENTER
	{
		if (ch == 0)	//Các phím từ F1-F10 kí tự đầu bằng 0
		{
			getch();
		}
		else
		{
			if (ch == 224)	//Thuộc bộ mã ASCII mở rộng kí tự đầu bằng 224
			{
				ch = getch();	//Đọc kí tự phía sau
				if (ch == 134)	//F12
				{
					return -1;
				}
			}
			//Thuộc bộ mã ASCII chuẩn
			else
			{
				//BACKSPACE
				if (ch == 8)
				{
					if (len > 0)
					{
						len--;
						gotoxy(whereX() - 1, whereY());
						printf(" ");
						gotoxy(whereX() - 1, whereY());
					}
				}
				else
				{
					//ESC
					if (ch == 27)
					{
						gotoxy(44, 0);
						textBgColor(15, 0);
						system("cls");
						exit(0);
					}
					//Nếu không phải ENTER, F2, BACKSPACE, ESC
					if (len < 10 && TrueCharNum(ch))
					{
						printf("%c", ch);
						string44[len++] = ch;
					}
				}
			}
		}
		ch = getch();
	}
	string44[len] = '\0';
	return 0;
}

//Hàm nhập <ISBN>, [ESC]: thoát; [BACKSPACE]: xóa kí tự; [F12]: trả về -1
int InputISBN(char ISBN[])
{
	Yescursortype();
	int len = 0;
	int ch = getch();
	while (ch != 13)	//ENTER
	{
		if (ch == 0)	//Các phím từ F1-F10 kí tự đầu bằng 0
		{
			getch();
		}
		else
		{
			if (ch == 224)	//Thuộc bộ mã ASCII mở rộng kí tự đầu bằng 224
			{
				ch = getch();	//Đọc kí tự phía sau
				if (ch == 134)	//F12
				{
					return -1;
				}
			}
			//Thuộc bộ mã ASCII chuẩn
			else
			{
				//BACKSPACE
				if (ch == 8)
				{
					if (len > 0)
					{
						len--;
						gotoxy(whereX() - 1, whereY());
						printf(" ");
						gotoxy(whereX() - 1, whereY());
					}
				}
				else
				{
					//ESC
					if (ch == 27)
					{
						gotoxy(44, 0);
						textBgColor(15, 0);
						system("cls");
						exit(0);
					}
					//Nếu không phải ENTER, F2, BACKSPACE, ESC
					if (len < 13 && TrueCharNum(ch))
					{
						printf("%c", ch);
						ISBN[len++] = ch;
					}
				}
			}
		}
		ch = getch();
	}
	ISBN[len] = '\0';
	return 0;
}