#include "stdafx.h"
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "linked-list.h"
#include "string.h"
#include "library-management.h"

//Khởi tạo Danh sách liên kết rỗng
void Init(List &L)
{
	L.pHead = NULL;
	L.pTail = NULL;
}

//Kiểm tra Danh sách liên kết rỗng hay không?
int Isempty(List L)
{
	return (L.pHead == NULL);
}

//Hàm trả về độ dài của Danh sách liên kết
int Len(List L)
{
	Node *PH = L.pHead, *PT = L.pTail; //PH duyệt từ đầu danh sách, PT duyệt từ cuối danh sách
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
Node *Make_Node(Books x)
{
	Node *P = (Node *)malloc(sizeof(Node));
	P->Data = x;
	P->pPrev = NULL;
	P->pNext = NULL;
	return P;
}

//Chèn <X> vào đầu Danh sách liên kết
void Insert_first(List &L, Books x)
{
	Node *P;
	P = Make_Node(x);
	if (Isempty(L))
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

List GetBooksData()
{
	FILE *f, *g;
	char ISBN[14];
	List L;
	Init(L);
	errno_t err = fopen_s(&f, "books/List.tdat", "rb");
	errno_t err_2;
	if (err == 0)
	{
		while (fread(&ISBN, sizeof(ISBN), 1, f) != 0)
		{
			char link[100] = "books/";
			strcat(link, ISBN);
			strcat(link, ".bin");
			err_2 = fopen_s(&g, link, "rb");
			if (err_2 == 0)
			{
				Books book;
				fread(&book, sizeof(Books), 1, g);
				fclose(g);
				if (book.exist)
				{
					Insert_first(L, book);
				}
			}
		}
		fclose(f);
	}
	return L;
}
void FreeLinkList(List L)
{
	Node *p = L.pHead;
	while (p != NULL)
	{
		Node *q = p->pNext;
		free(p);
		p = q;
	}
}