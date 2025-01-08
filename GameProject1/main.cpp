#include <Windows.h>
#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <vector>
#include <string>
#include "Createmaze.h"

#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

using namespace std;

#define MAP_WIDTH 48
#define MAP_HEIGHT 20
#define BLOCK_WIDTH 32
#define BLOCK_HEIGHT 32
#define WIDTH BLOCK_WIDTH * MAP_WIDTH
#define HEIGHT BLOCK_HEIGHT * MAP_HEIGHT
#define PLAYER_WIDTH BLOCK_WIDTH
#define PLAYER_HEIGHT BLOCK_HEIGHT
#define PLAYER_ID 1001
#define PLAYER_MAP_X 1
#define PLAYER_MAP_Y 1
#define DOOR_ID 1002
#define WALL_COLOR 0x333333
#define FLOOR_COLOR 0x639a95



struct Player {
	int x, y;
};


vector<vector<int>> _map = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, PLAYER_ID, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, DOOR_ID, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

IMAGE playerImg;
IMAGE doorImg;
Player player;

void draw_player(Player player) {
	putimage(player.x, player.y, &playerImg);
}

void draw_door(int x, int y){
	putimage(x, y, &doorImg);
}

void draw_map(vector<vector<int>> map) 
{
	int i = 0 , j = 0;
	for (const auto& row : map) {
		for (int val : row) {
			if (val == 1) {
				setfillcolor(WALL_COLOR);
			}
			if (val == 0) {
				setfillcolor(FLOOR_COLOR);
			}
			if (val == PLAYER_ID) {
				player.x = BLOCK_WIDTH * i;
				player.y = BLOCK_HEIGHT * j;
				draw_player(player);
				++j;
				continue;
			}
			if (val == DOOR_ID) {
				draw_door(BLOCK_WIDTH * i, BLOCK_HEIGHT * j);
				++j;
				continue;
			}
			solidrectangle(BLOCK_WIDTH * i, BLOCK_HEIGHT * j, BLOCK_WIDTH * (i + 1), BLOCK_HEIGHT * (j + 1));
			++j;
		}
		++i;
		j = 0;
	}
	i = 0;
}

void refesh_map(int map_x, int map_y, int new_map_x, int new_map_y) {
	_map[new_map_x][new_map_y] = PLAYER_ID;
	_map[map_x][map_y] = 0;
}

bool move_player(Player& player, int dx, int dy) {
	int map_x = player.x / BLOCK_WIDTH;
	int map_y = player.y / BLOCK_HEIGHT;
	int new_map_x = (player.x + dx) / BLOCK_WIDTH;
	int new_map_y = (player.y + dy) / BLOCK_HEIGHT;
	int id = _map[new_map_x][new_map_y];
	if (id == 1) {
		return false;
	}
	if (id == DOOR_ID) {
		refesh_map(map_x, map_y, new_map_x, new_map_y);
		draw_map(_map);
		return true;
	}
	refesh_map(map_x, map_y, new_map_x, new_map_y);

	draw_map(_map);
	return false;

}


int mainloop() {
	int i = 0;
	bool end = false;
	while (true) {

		if (GetAsyncKeyState(87) != 0) {
			end = move_player(player, 0, -BLOCK_HEIGHT);
		}
		else if (GetAsyncKeyState(65) != 0) {
			end = move_player(player, -BLOCK_WIDTH, 0);
		}
		else if (GetAsyncKeyState(68) != 0) {
			end = move_player(player, BLOCK_WIDTH, 0);
		}
		else if (GetAsyncKeyState(83) != 0) {
			end = move_player(player, 0, BLOCK_HEIGHT);
		}
		if (end) {
			MessageBoxA(0, "ÓÎÏ·Ê¤Àû!!", "¹§Ï²", MB_OK | MB_ICONINFORMATION);
			break;
		}
		Sleep(100);
	}
	return 0;
	
}

void initGame() {
	initgraph(WIDTH, HEIGHT);
	setbkcolor(RED);
	cleardevice();
	loadimage(&playerImg, _T("./image/people.jpg"), PLAYER_WIDTH, PLAYER_HEIGHT);
	loadimage(&doorImg, _T("./image/door.png"), PLAYER_WIDTH, PLAYER_HEIGHT);
	player.x = 0;
	player.y = 0;
	draw_map(_map);
}

void closeGame() 
{
	closegraph();
	return;
}

void Create_Map() {
	_map = createMaze(MAP_HEIGHT - 1, MAP_WIDTH - 1);
}

void gameloop() {
	Create_Map();
	initGame();
	mainloop();
	closeGame();
}

int main()
{
	while (true) {
		gameloop();
	}
    return 0;
}

