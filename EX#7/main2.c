
#define _CRT_SECURE_NO_WARNINGS   // 讓 Visual Studio 也能直接使用 fopen
#include <stdio.h>
 
#define BOOK_NUM 6   // 書籍數量
 
// 書籍資料的結構
typedef struct Books {
    int  id;           // 編號
    int  price;        // 價錢
    char title[100];   // 書名
} book_t;
 
// 獨立函式：計算所有書籍的總價錢，並輸出到螢幕上
void total_price(book_t books[], int n)
{
    int i, sum = 0;
 
    for (i = 0; i < n; i++)
        sum += books[i].price;
 
    printf("Total price: %d\n", sum);
}
 
// 獨立函式：輸出所有書籍資料到螢幕上
void list_books(book_t books[], int n)
{
    int i;
 
    printf("%3s  %5s  %s\n", "Id", "Price", "Title");
    printf("------------------------------------------------------------\n");
    for (i = 0; i < n; i++)
        printf("%3d  %5d  %s\n", books[i].id, books[i].price, books[i].title);
    printf("------------------------------------------------------------\n");
}
 
int main(void)
{
    // 在 main 中建立書籍資料
    book_t books[BOOK_NUM] = {
        {1, 1000, "All the Light We Cannot See"},
        {2,  300, "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4,  550, "Killers of the Flower Moon"},
        {5,  870, "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };
    book_t from_file[BOOK_NUM];   // 存放從 Book.bin 讀回來的資料
    int count;
    FILE *fp;
 
    // 1. 把書籍資料以二進位方式寫入 Book.bin
    fp = fopen("Book.bin", "wb");
    if (fp == NULL) {
        printf("Cannot create Book.bin\n");
        return 1;
    }
    fwrite(books, sizeof(book_t), BOOK_NUM, fp);
    fclose(fp);
 
    // 2. 從 Book.bin 讀回來，確認資料真的有存進檔案
    fp = fopen("Book.bin", "rb");
    if (fp == NULL) {
        printf("Cannot open Book.bin\n");
        return 1;
    }
    count = (int) fread(from_file, sizeof(book_t), BOOK_NUM, fp);
    fclose(fp);
 
    // 3. 透過 list_books() 輸出書籍資料，透過 total_price() 計算總價錢
    list_books(from_file, count);
    total_price(from_file, count);
 
    return 0;
}
 
