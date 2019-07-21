#pragma once
#include "library-management.h"
//Khởi tạo Danh sách liên kết rỗng
void Init(List &L);

//Kiểm tra Danh sách liên kết rỗng hay không?
int Isempty(List L);

//Hàm trả về độ dài của Danh sách liên kết
int Len(List L);

//Tạo một Node chứa thông tin <X>
Node *Make_Node(Books x);

//Chèn <X> vào đầu Danh sách liên kết
void Insert_first(List &L, Books x);

List GetBooksData();

void FreeLinkList(List L);