//
// Created by wangj on 2025/12/10.
//
/**
  0 0 0 0
  1 0 1 0
  0 0 1 0
  1 1 1 0
 */
#include <stdio.h>
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()

typedef struct  {
    int x;
    int y;
    int data;
} Pointer;
typedef struct {
    Pointer pointers[4][4];
} QP;
int main() {
    srand(time(NULL));  // 用当前时间作为种子
    Pointer pointer;
    QP qp;
    // int start = 0;
    int data;
    for (int i = 0; i <= 3; i++) {
        // start++;
        for (int j = 0; j <= 3; j++) {
            // start++;
            int r = rand() % 2;
            scanf("%d", &data);
            // pointer.data = data;
            // pointer.x = i;
            // pointer.y = j;
            // qp.pointers[i][j] = pointer;
            qp.pointers[i][j].x = i;
            qp.pointers[i][j].y = j;
            qp.pointers[i][j].data = data;
        }

    }

    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            printf("\t %d",qp.pointers[i][j].data);
        }
        printf("\n");
    }
    return 0;
}
