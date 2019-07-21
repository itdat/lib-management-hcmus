#pragma once
#include "library-management.h"
//Khởi tạo Danh sách liên kết rỗng
void Init_Reader(List_Reader &L);

//Kiểm tra Danh sách liên kết rỗng hay không?
int Isempty_Reader(List_Reader L);

//Hàm trả về độ dài của Danh sách liên kết
int Len_Reader(List_Reader L);

//Tạo một Node chứa thông tin <X>
Node_Reader *Make_Node_Reader(Readers x);

//Chèn <X> vào đầu Danh sách liên kết
void Insert_first_Reader(List_Reader &L, Readers x);

List_Reader GetReadersData();

void FreeLinkList_Reader(List_Reader L);
