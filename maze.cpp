/***********************************************************
* File:     maze.cpp
* Author:   Xiaolong Ma(��С��)
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

#define HEIGHT 7     // �Թ��ĸ߶�
#define WIDTH 7      // �Թ��Ŀ��
#define WALL false   // ǽ�ڵı�ʾ
#define ROAD true    // ��·�ı�ʾ
#define UP 1         // �Ϸ���
#define DOWN 2       // �·���
#define LEFT 3       // ����
#define RIGHT 4      // �ҷ���

/***********************************************************
* Struct Name:   RouteDot
* Function:      ����·���ϵĵ�
* Data Members:  x - ���x����
*                y - ���y����
***********************************************************/
struct RouteDot {
	int x;
	int y;
}Start{ 1,1 }, End{ HEIGHT - 2,WIDTH - 2 };// ���������յ�

bool my_maze[HEIGHT][WIDTH] = { WALL };// ��ʼ���Թ����飬Ĭ��ȫ����ǽ��

/***********************************************************
* Function Name:   inBounds
* Function:        ��������Ƿ����Թ���Χ��
* Input Parameter: x - ����x����
*                  y - ����y����
* Returned Value:  ����ڷ�Χ�ڷ���true�����򷵻�false
***********************************************************/
bool inBounds(int x, int y)
{
	if (x > 0 && x < HEIGHT-1 && y > 0 && y < WIDTH-1)
		return true;
	return false;
}

/***********************************************************
* Function Name:   BreakWall
* Function:        ��������֮���ǽ��
* Input Parameter: x1, y1 - ��һ���������
*                  x2, y2 - �ڶ����������
***********************************************************/
void BreakWall(int x1, int y1, int x2, int y2) 
{
	my_maze[(x1 + x2) / 2][(y1 + y2) / 2] = ROAD;
}

/***********************************************************
* Function Name:   Draw
* Function:        ʹ�õݹ鷽�������Թ�
* Input Parameter: x - ��ǰ����x
*                  y - ��ǰ����y
***********************************************************/
void Draw(int x,int y) 
{
	my_maze[x][y] = true;// ��ǵ�ǰ��Ϊ��·
	const int directions[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
	int dir_order[4] = { UP,DOWN,LEFT,RIGHT };
	
	// ������ҷ���˳��
	dir_order[0] = rand() % 4 + 1;
	do {
		dir_order[1] = rand() % 4 + 1;
	} while (dir_order[1]== dir_order[0]);
	do {
		dir_order[2] = rand() % 4 + 1;
	} while (dir_order[2] == dir_order[1]||dir_order[2] == dir_order[0]);
	dir_order[3] = UP * DOWN * LEFT * RIGHT / dir_order[0] / dir_order[1] / dir_order[2];

	// ����ÿ������
	for (int i = 0; i < 4; i++) {
		int dir = dir_order[i] - 1;// ��ȡ��������
		int nx = x + directions[dir][0]*2;// ������һ��x����
		int ny = y + directions[dir][1]*2;// ������һ��y����

		// �����һ�������Ƿ��ڷ�Χ����δ������
		if (inBounds(nx, ny) && !my_maze[nx][ny]) {
			BreakWall(x, y, nx, ny);// ����ǽ��
			Draw(nx, ny);
		}
	}
}

/***********************************************************
* Function Name:   GoThrough
* Function:        ͨ���ݹ��ҵ��Թ���·��
* Input Parameter: route - ���ڴ洢·��������
*                  x - ��ǰ����x
*                  y - ��ǰ����y
*                  direction - ��һ���ķ���
* Returned Value:  ����ҵ�·������true�����򷵻�false
***********************************************************/
bool GoThrough(LinkList<RouteDot>& route,int x,int y,int direction=0)
{
	RouteDot dot{ x,y };// ��ǰ��
	if (!(inBounds(x, y)&& my_maze[x][y])) // ��������Ƿ���Ч
		return false;
	if (x == End.x && y == End.y) {// ��������յ�
		route.inputFront(dot);// �������·��
		return true;
	}

	// �����ĸ�����
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

	return false;// ���û��·������false
}

/***********************************************************
* Function Name:   PrintSolution
* Function:        ��ӡ�Թ����ҵ���·��
* Input Parameter: route - �洢·��������
***********************************************************/
void PrintSolution(LinkList<RouteDot>& route)
{
	std::cout << "�Թ���ͼ��\n\n";
	std::cout << "        0��     1��     2��     3��     4��     5��     6��\n";

	for (int i = 0; i < HEIGHT; i++) {
		std::cout << i << "��";
		for (int j = 0; j < WIDTH; j++) {
			if (my_maze[i][j]) {
				bool rout_dot=false;
				for (int k = 1; k <= route.Length(); k++) { // ���õ��Ƿ���·����
					if (i == route[k].x && j == route[k].y) {
						rout_dot = true;
						break;
					}	
				}
				if (rout_dot)
					std::cout << "     *  ";// ���·����
				else
					std::cout << "     0  ";// ��Ƿ�·����·
			}
			else
				std::cout << "     #  ";// ��ӡǽ��
		}
		std::cout << "\n\n";
	}

	std::cout << "\n�Թ�·����\n\n";
	for (int i = 1; i <= route.Length();i++) {
		std::cout << "<" << route[i].x << "," << route[i].y << ">";
		if (i != route.Length())
			std::cout << " ---> ";
	}
	std::cout << "\n";
}

/***********************************************************
* Function Name:   Maze
* Function:        �����Թ���Ѱ��·��
***********************************************************/
void Maze()
{
	srand((unsigned)time(NULL));// ���������
	Draw(Start.x,Start.y);// ��ʼ�����Թ�
	LinkList<RouteDot> route;// ����·������
	if (GoThrough(route, Start.x, Start.y))// ����·��
		PrintSolution(route);// ��ӡ·��
	else
		std::cout << "û��·��\n";
}

/***********************************************************
* Function Name:   main
* Function:        �������
***********************************************************/
int main() {

	// �����Թ���Ѱ��·��
	Maze();

	return 0;
}