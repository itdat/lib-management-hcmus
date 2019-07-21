#pragma once
//Gọi tính năng thứ <I>
void Action(int i);

//Vẽ vùng [MENU]
void MakeFieldMenu(int n);

//In tính năng
void PrintFeature(char str[]);

//Tạo [MENU] di chuyển lên xuống
void MoveSelect(int n, char f[10][50], char list[]);

//In ra [MENU] với số lượng <countFeatures> tính năng và danh sách <list> các tính năng
void Menu(int countFeatures, char list[]);



