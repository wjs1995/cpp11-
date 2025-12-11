#include <stdio.h>

#define N 4
//深度优先
// 方向：上、下、左、右
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void dfs(int grid[N][N], char result[N][N], int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= N) return;
    if (grid[x][y] != 0 || result[x][y] == '*') return; // 已访问或非0

    result[x][y] = '*'; // 标记为星号

    // 向四个方向继续搜索
    for (int i = 0; i < 4; i++) {
        dfs(grid, result, x + dx[i], y + dy[i]);
    }
}

int main() {
    int grid[N][N];
    char result[N][N];

    // 初始化 result 为原始数字的字符表示
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
            if (grid[i][j] == 0) {
                result[i][j] = '0';
            } else {
                result[i][j] = '0' + grid[i][j]; // 假设数字是 0~9
            }
        }
    }

    // 如果左上角是 0，则从 (0,0) 开始 DFS
    if (grid[0][0] == 0) {
        dfs(grid, result, 0, 0);
    }

    // 打印结果
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}