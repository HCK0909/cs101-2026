#define _CRT_SECURE_NO_WARNINGS   // 讓 Visual Studio 也能直接使用 scanf、fopen
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SET 5    // 最多購買 5 組
#define NUM     7    // 每組 7 個數字
#define MAX_NUM 69   // 數字範圍 01 ~ 69

// 產生一組樂透：7 個 01 ~ 69 且不重複的數字
// 依照範例格式，前 6 個由小到大排序，第 7 個當特別號放在最後
void make_lotto(int num[])
{
    int used[MAX_NUM + 1] = {0};   // used[x] == 1 代表數字 x 已經被選過
    int len = NUM - 1;             // 要排序的個數 (前 6 個)
    int i, j, tmp;

    // 抽出 7 個不重複的數字
    for (i = 0; i < NUM; i++) {
        do {
            num[i] = rand() % MAX_NUM + 1;   // 1 ~ 69
        } while (used[num[i]]);              // 已經抽過就重抽
        used[num[i]] = 1;
    }

    // 前 6 個數字用氣泡排序由小到大排列
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - 1 - i; j++) {
            if (num[j] > num[j + 1]) {
                tmp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = tmp;
            }
        }
    }
}

int main(void)
{
    const char *week[]  = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    const char *month[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                           "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    int num[NUM];
    int n, i, j, ch;
    time_t now;
    struct tm *t;
    FILE *fp;

    srand((unsigned) time(NULL));   // 設定亂數種子，每次執行的號碼都不同

    // ---------- 開機畫面 ----------
    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩：");
    while (scanf("%d", &n) != 1 || n < 1 || n > MAX_SET) {
        while ((ch = getchar()) != '\n' && ch != EOF)   // 清掉輸入錯誤的那一行
            ;
        if (ch == EOF)                                   // 沒有輸入了就結束程式
            return 1;
        printf("只能購買 1 ~ %d 組，請重新輸入：", MAX_SET);
    }

    // ---------- 輸出 lotto.txt ----------
    fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        printf("無法建立 lotto.txt\n");
        return 1;
    }

    now = time(NULL);
    t = localtime(&now);   // 取得現在的日期與時間

    fprintf(fp, "======== lotto649 =========\n");
    fprintf(fp, "= %s %s %d %02d:%02d:%02d %d =\n",
            week[t->tm_wday], month[t->tm_mon], t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec, t->tm_year + 1900);

    for (i = 1; i <= MAX_SET; i++) {
        fprintf(fp, "[%d]:", i);
        if (i <= n) {                 // 有購買的組：印出 7 個號碼
            make_lotto(num);
            for (j = 0; j < NUM; j++)
                fprintf(fp, " %02d", num[j]);
        } else {                      // 沒購買的組：印出 --
            for (j = 0; j < NUM; j++)
                fprintf(fp, " --");
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "======== csie@CGU =========\n");
    fclose(fp);

    printf("以為您購買的 %d 組樂透組合輸出至 lotto.txt\n", n);
    return 0;
}
