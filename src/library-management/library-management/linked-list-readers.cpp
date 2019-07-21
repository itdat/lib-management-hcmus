#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "linked-list.h"
#include "string.h"
#include "library-management.h"
#include "function-standard.h"

//Khởi tạo Danh sách liên kết rỗng
void Init_Reader(List_Reader &L)
{
	L.pHead = NULL;
	L.pTail = NULL;
}

//Kiểm tra Danh sách liên kết rỗng hay không?
int Isempty_Reader(List_Reader L)
{
	return (L.pHead == NULL);
}

//Hàm trả về độ dài của Danh sách liên kết
int Len_Reader(List_Reader L)
{
	Node_Reader *PH = L.pHead, *PT = L.pTail; //PH duyệt từ đầu danh sách, PT duyệt từ cuối danh sách
	int i = 0; //Biến đếm
	if (PH != NULL) i = 1;
	while (PH != NULL)
	{
		if (PH == PT) break;
		PH = PH->pNext;
		i++;
		if (PH == PT) break;
		PT = PT->pPrev;
		i++;
	}
	return i;
}

//Tạo một Node chứa thông tin <X>
Node_Reader *Make_Node_Reader(Readers x)
{
	Node_Reader *P = (Node_Reader *)malloc(sizeof(Node_Reader));
	P->Data = x;
	P->pPrev = NULL;
	P->pNext = NULL;
	return P;
}

//Chèn <X> vào đầu Danh sách liên kết
void Insert_first_Reader(List_Reader &L, Readers x)
{
	Node_Reader *P;
	P = Make_Node_Reader(x);
	if (Isempty_Reader(L))
	{
		L.pHead = P;
		L.pTail = P;
	}
	else
	{
		P->pNext = L.pHead;
		L.pHead->pPrev = P;
		L.pHead = P;
	}
}

List_Reader GetReadersData()
{
	FILE *f;
	List_Reader L;
	Init_Reader(L);
	errno_t err = fopen_s(&f, "readers/List.tdat", "rb");
	errno_t err_2;
	if (err == 0)
	{
		long code;
		fread(&code, sizeof(long), 1, f);
		fclose(f);
		for (long i = 1; i <= code; i++)
		{
			char textcode[10];
			strcpy(textcode, toStr(i));
			char link[128];
			strcpy(link, Path("readers/", textcode, ".bin"));
			err_2 = fopen_s(&f, link, "rb");
			if (err_2 == 0)
			{
				Readers reader;
				fread(&reader, sizeof(Readers), 1, f);
				fclose(f);
				Insert_first_Reader(L, reader);
			}
		}
	}
	return L;
}

void FreeLinkList_Reader(List_Reader L)
{
	Node_Reader *p = L.pHead;
	while (p != NULL)
	{
		Node_Reader *q = p->pNext;
		free(p);
		p = q;
	}
}