/***********************************************************
* File:     maze.cpp
* Author:   Xiaolong Ma(马小龙)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: maze
* Date:     2024.10.10
* Update:   2024.10.11
***********************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "my_singly_link_list.h"

#define HEIGHT 7     // 迷宫的高度
#define WIDTH 7      // 迷宫的宽度
#define WALL false   // 墙壁的表示
#define ROAD true    // 道路的表示
#define UP 1         // 上方向
#define DOWN 2       // 下方向
#define LEFT 3       // 左方向
#define RIGHT 4      // 右方向

/***********************************************************
* Struct Name:   RouteDot
* Function:      定义路线上的点
* Data Members:  x - 点的x坐标
*                y - 点的y坐标
***********************************************************/
struct RouteDot {
	int x;
	int y;
}Start{ 1,1 }, End{ HEIGHT - 2,WIDTH - 2 };// 定义起点和终点

bool my_maze[HEIGHT][WIDTH] = { WALL };// 初始化迷宫数组，默认全部是墙壁

/***********************************************************
* Function Name:   inBounds
* Function:        检查坐标是否在迷宫范围内
* Input Parameter: x - 检查的x坐标
*                  y - 检查的y坐标
* Returned Value:  如果在范围内返回true，否则返回false
***********************************************************/
bool inBounds(int x, int y)
{
	if (x > 0 && x < HEIGHT-1 && y > 0 && y < WIDTH-1)
		return true;
	return false;
}

/***********************************************************
* Function Name:   BreakWall
* Function:        打破两点之间的墙壁
* Input Parameter: x1, y1 - 第一个点的坐标
*                  x2, y2 - 第二个点的坐标
***********************************************************/
void BreakWall(int x1, int y1, int x2, int y2) 
{
	my_maze[(x1 + x2) / 2][(y1 + y2) / 2] = ROAD;
}

/***********************************************************
* Function Name:   Draw
* Function:        使用递归方法生成迷宫
* Input Parameter: x - 当前坐标x
*                  y - 当前坐标y
***********************************************************/
void Draw(int x,int y) 
{
	my_maze[x][y] = true;// 标记当前点为道路
	const int directions[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
	int dir_order[4] = { UP,DOWN,LEFT,RIGHT };
	
	// 随机打乱方向顺序
	dir_order[0] = rand() % 4 + 1;
	do {
		dir_order[1] = rand() % 4 + 1;
	} while (dir_order[1]== dir_order[0]);
	do {
		dir_order[2] = rand() % 4 + 1;
	} while (dir_order[2] == dir_order[1]||dir_order[2] == dir_order[0]);
	dir_order[3] = UP * DOWN * LEFT * RIGHT / dir_order[0] / dir_order[1] / dir_order[2];

	// 遍历每个方向
	for (int i = 0; i < 4; i++) {
		int dir = dir_order[i] - 1;// 获取方向索引
		int nx = x + directions[dir][0]*2;// 计算下一个x坐标
		int ny = y + directions[dir][1]*2;// 计算下一个y坐标

		// 检查下一个坐标是否在范围内且未被访问
		if (inBounds(nx, ny) && !my_maze[nx][ny]) {
			BreakWall(x, y, nx, ny);// 打破墙壁
			Draw(nx, ny);
		}
	}
}

/***********************************************************
* Function Name:   GoThrough
* Function:        通过递归找到迷宫的路径
* Input Parameter: route - 用于存储路径的链表
*                  x - 当前坐标x
*                  y - 当前坐标y
*                  direction - 上一步的方向
* Returned Value:  如果找到路径返回true，否则返回false
***********************************************************/
bool GoThrough(LinkList<RouteDot>& route,int x,int y,int direction=0)
{
	RouteDot dot{ x,y };// 当前点
	if (!(inBounds(x, y)&& my_maze[x][y])) // 检查坐标是否有效
		return false;
	if (x == End.x && y == End.y) {// 如果到达终点
		route.inputFront(dot);// 将点加入路径
		return true;
	}

	// 尝试四个方向
	if (direction != DOWN && GoThrough(route, x - 1, y, UP)) {
		route.inputFront(dot);
		return true;
	}
	if (direction != UP && GoThrough(route, x + 1, y, DOWN)) {
		route.inputFront(dot);
		return true;
	}
	if (direction != RIGHT && GoThrough(route, x, y - 1, LEFT)) {
		route.inputFront(dot);
		return true;
	}
	if (direction != LEFT && GoThrough(route, x, y + 1, RIGHT)) {
		route.inputFront(dot);
		return true;
	}

	return false;// 如果没有路径返回false
}

/***********************************************************
* Function Name:   PrintSolution
* Function:        打印迷宫和找到的路径
* Input Parameter: route - 存储路径的链表
***********************************************************/
void PrintSolution(LinkList<RouteDot>& route)
{
	std::cout << "迷宫地图：\n\n";
	std::cout << "        0列     1列     2列     3列     4列     5列     6列\n";

	for (int i = 0; i < HEIGHT; i++) {
		std::cout << i << "行";
		for (int j = 0; j < WIDTH; j++) {
			if (my_maze[i][j]) {
				bool rout_dot=false;
				for (int k = 1; k <= route.Length(); k++) { // 检查该点是否在路径中
					if (i == route[k].x && j == route[k].y) {
						rout_dot = true;
						break;
					}	
				}
				if (rout_dot)
					std::cout << "     *  ";// 标记路径点
				else
					std::cout << "     0  ";// 标记非路径道路
			}
			else
				std::cout << "     #  ";// 打印墙壁
		}
		std::cout << "\n\n";
	}

	std::cout << "\n迷宫路径：\n\n";
	for (int i = 1; i <= route.Length();i++) {
		std::cout << "<" << route[i].x << "," << route[i].y << ">";
		if (i != route.Length())
			std::cout << " ---> ";
	}
	std::cout << "\n";
}

/***********************************************************
* Function Name:   Maze
* Function:        生成迷宫并寻找路径
***********************************************************/
void Maze()
{
	srand((unsigned)time(NULL));// 随机数种子
	Draw(Start.x,Start.y);// 开始生成迷宫
	LinkList<RouteDot> route;// 创建路径链表
	if (GoThrough(route, Start.x, Start.y))// 查找路径
		PrintSolution(route);// 打印路径
	else
		std::cout << "没有路径\n";
}

/***********************************************************
* Function Name:   main
* Function:        程序入口
***********************************************************/
int main() {

	// 生成迷宫并寻找路径
	Maze();

	return 0;
}