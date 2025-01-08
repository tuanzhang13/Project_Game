#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include "CreateMaze.h"

using namespace std;

// 定义迷宫大小
int WIDTH = 100;
int HEIGHT = 100;

// 定义方向
const int DIR[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// 初始化迷宫
vector<vector<int>> maze(HEIGHT, vector<int>(WIDTH, 1));

// 检查坐标是否在迷宫范围内
bool isValid(int x, int y) {
    return x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH;
}

// 使用DFS生成迷宫
void generateMaze(int startX, int startY) {
    stack<pair<int, int>> stack;
    stack.push({startX, startY});
    maze[startX][startY] = 1001; // 起点设置为路径

    while (!stack.empty()) {
        auto current = stack.top();
        int x = current.first;
        int y = current.second;

        // 随机选择一个方向
        vector<int> directions = {0, 1, 2, 3};
        std::random_device rd;
        std::mt19937 rng(rd());
        std::shuffle(directions.begin(), directions.end(), rng);

        bool moved = false;
        for (int dir : directions) {
            int nx = x + DIR[dir][0] * 2;
            int ny = y + DIR[dir][1] * 2;

            if (isValid(nx, ny) && maze[nx][ny] == 1) {
                maze[nx][ny] = 0; // 设置为路径
                maze[x + DIR[dir][0]][y + DIR[dir][1]] = 0; // 打通墙壁
                stack.push({nx, ny});
                moved = true;
                break;
            }
        }

        if (!moved) {
            stack.pop(); // 回溯
        }
    }
}

// 设置终点
void setEndPoint() {
    // 将迷宫的右下角设置为终点
    maze[HEIGHT - 2][WIDTH - 2] = 1002; // 1002 表示终点
}

// 打印迷宫
void printMaze() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> createMaze(int width, int height) {
    WIDTH = width;
    HEIGHT = height;

    srand(time(0)); // 随机种子
    generateMaze(1, 1); // 从 (1, 1) 开始生成迷宫
    setEndPoint(); // 设置终点

    return maze;
}
