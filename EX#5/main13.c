#include <stdio.h>

int multi(int i, int j) {
    if (j == 1) {
        if (i > 1) {
            multi(i - 1, 9); 
        }
        printf("%d*%d=%d ", i, j, i * j); 
        return 0;
    } else {
        multi(i, j - 1); 
        printf("%d*%d=%d ", i, j, i * j);
        
        if (j == 9) {
            printf("\n"); 
        }
        return 0;
    }
}

int main() {
    multi(9, 9); 
    return 0;
}
