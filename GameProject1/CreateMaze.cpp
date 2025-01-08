#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include "CreateMaze.h"

using namespace std;

// �����Թ���С
int WIDTH = 100;
int HEIGHT = 100;

// ���巽��
const int DIR[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// ��ʼ���Թ�
vector<vector<int>> maze(HEIGHT, vector<int>(WIDTH, 1));

// ��������Ƿ����Թ���Χ��
bool isValid(int x, int y) {
    return x >= 0 && x < HEIGHT && y >= 0 && y < WIDTH;
}

// ʹ��DFS�����Թ�
void generateMaze(int startX, int startY) {
    stack<pair<int, int>> stack;
    stack.push({startX, startY});
    maze[startX][startY] = 1001; // �������Ϊ·��

    while (!stack.empty()) {
        auto current = stack.top();
        int x = current.first;
        int y = current.second;

        // ���ѡ��һ������
        vector<int> directions = {0, 1, 2, 3};
        std::random_device rd;
        std::mt19937 rng(rd());
        std::shuffle(directions.begin(), directions.end(), rng);

        bool moved = false;
        for (int dir : directions) {
            int nx = x + DIR[dir][0] * 2;
            int ny = y + DIR[dir][1] * 2;

            if (isValid(nx, ny) && maze[nx][ny] == 1) {
                maze[nx][ny] = 0; // ����Ϊ·��
                maze[x + DIR[dir][0]][y + DIR[dir][1]] = 0; // ��ͨǽ��
                stack.push({nx, ny});
                moved = true;
                break;
            }
        }

        if (!moved) {
            stack.pop(); // ����
        }
    }
}

// �����յ�
void setEndPoint() {
    // ���Թ������½�����Ϊ�յ�
    maze[HEIGHT - 2][WIDTH - 2] = 1002; // 1002 ��ʾ�յ�
}

// ��ӡ�Թ�
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

    srand(time(0)); // �������
    generateMaze(1, 1); // �� (1, 1) ��ʼ�����Թ�
    setEndPoint(); // �����յ�

    return maze;
}
