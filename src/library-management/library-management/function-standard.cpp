#include "stdlib.h"
#include "string.h"
#include "stdafx.h"
#include "ctime"
#include "library-management.h"
#include <direct.h>

// Khởi tạo thư mục
void initSystemFolder()
{
	mkdir("books");
	mkdir("borrowedbook");
	mkdir("cache");
	mkdir("parameterSYSTEM");
	mkdir("readers");
	mkdir("user");
	mkdir("user/admin");
	mkdir("user/experts");
	mkdir("user/managers");
}

//Tạo đường dẫn bằng cách ghép 3 chuỗi s1+s2+s3
char *Path(char s1[], char s2[], char s3[])
{
	char s[128];
	s[0] = '\0';
	strcpy(s, s1);
	strcat(s, s2);
	strcat(s, s3);
	s[strlen(s)] = '\0';
	return s;
}

//Tạo chuỗi mã độc giả
char *toStr(long n)
{
	char str[10];
	sprintf(str, "%ld", n);
	char S[10];
	S[0] = '\0';
	int count = 9 - strlen(str);
	while (count > 0)
	{
		strcat(S, "0");
		count--;
	}
	strcat(S, str);
	S[9] = '\0';
	return S;
}

int ReadNumMonth()
{
	FILE *f;
	int n;
	errno_t err = fopen_s(&f, "parameterSYSTEM/ReaderMonthTimeoutExpired.txt", "r");
	if (err == 0)
	{
		fscanf(f, "%d", &n);
		fclose(f);
		return n;
	}
	//Trường hợp không có file sẽ mặc định 48 tháng
	else
	{
		err = fopen_s(&f, "parameterSYSTEM/ReaderMonthTimeoutExpired.txt", "w");
		if (err == 0)
		{
			fprintf(f, "%d", 48);
			fclose(f);
		}
		return 48;
	}
}

tm *MakeEndDay(int Date, int Month, int Year, int NumMonth)
{
	tm created;
	created.tm_mday = Date;
	created.tm_mon = Month + NumMonth;
	created.tm_year = Year;
	created.tm_hour = 0;
	created.tm_isdst = 0;
	created.tm_min = 0;
	created.tm_sec = 0;
	created.tm_wday = 0;
	created.tm_yday = 0;
	time_t endtime = mktime(&created);
	tm *ended = localtime(&endtime);
	return ended;
}

//Trả về số lượng sách tối đa được mượn
int MaximumBooks()
{
	FILE *f;
	int n;
	errno_t err = fopen_s(&f, "parameterSYSTEM/MaximumBooks.txt", "r");
	if (err == 0)
	{
		fscanf(f, "%d", &n);
		fclose(f);
		return n;
	}
	else
	{
		err = fopen_s(&f, "parameterSYSTEM/MaximumBooks.txt", "w");
		if (err == 0)
		{
			fprintf(f, "%d", 5);
			fclose(f);
		}
		return 5;
	}
}

//Trả về thời hạn mượn tối đa một quyển sách không tính phí
int BorrowedTimeoutExpired()
{
	FILE *f;
	int n;
	errno_t err = fopen_s(&f, "parameterSYSTEM/BorrowedDayTimeoutExpired.txt", "r");
	if (err == 0)
	{
		fscanf(f, "%d", &n);
		fclose(f);
		return n;
	}
	else
	{
		fcloseall();
		err = fopen_s(&f, "parameterSYSTEM/BorrowedDayTimeoutExpired.txt", "w");
		if (err == 0)
		{
			fprintf(f, "%d", 7);
			fclose(f);
		}
		return 7;
	}
}

Day GetToday()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	Day TODAY;
	TODAY.Date = ltm->tm_mday;
	TODAY.Month = ltm->tm_mon + 1;
	TODAY.Year = ltm->tm_year + 1900;
	return TODAY;
}