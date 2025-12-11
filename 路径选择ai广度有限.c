#include <stdio.h>
#include <stdbool.h>

#define N 4

// 方向：上、下、左、右
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// 用于记录每个点的前驱（parent）
typedef struct {
    int x, y;
} Point;

Point parent[N][N];  // parent[i][j] 表示 (i,j) 是从哪个点来的
bool visited[N][N];

// BFS 找最短路径
bool bfs(int grid[N][N]) {
    // 初始化
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            visited[i][j] = false;
            parent[i][j] = (Point){-1, -1};
        }
    }

    // 手动实现队列（固定大小）
    Point queue[N * N];
    int front = 0, rear = 0;

    if (grid[0][0] != 0) return false; // 起点不可达

    queue[rear++] = (Point){0, 0};
    visited[0][0] = true;

    while (front < rear) {
        Point cur = queue[front++];
        int x = cur.x, y = cur.y;

        if (x == N - 1 && y == N - 1) {
            return true; // 到达终点
        }

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N &&
                !visited[nx][ny] && grid[nx][ny] == 0) {
                visited[nx][ny] = true;
                parent[nx][ny] = (Point){x, y};
                queue[rear++] = (Point){nx, ny};
                }
        }
    }
    return false; // 无法到达终点
}

int main() {
    int grid[N][N];
    char output[N][N];

    // 读入 16 个数字
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
            output[i][j] = (grid[i][j] == 0) ? '0' : '1';
        }
    }

    // 执行 BFS
    if (bfs(grid)) {
        // 从终点回溯到起点，标记路径
        int x = N - 1, y = N - 1;
        while (x != -1 && y != -1) {
            output[x][y] = '*';
            Point p = parent[x][y];
            x = p.x;
            y = p.y;
        }
    }
    // 如果无法到达，output 保持原样（无 *）

    // 打印结果
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", output[i][j]);
        }
        printf("\n");
    }

    return 0;
}