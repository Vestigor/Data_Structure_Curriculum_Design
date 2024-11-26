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
#include <cassert>
#include "my_stack.h"


/***********************************************************
* Class Name:       Maze
* Function:         迷宫类，生成随机迷宫并寻找路径
* Data Members:     height - 迷宫高度
*                   width - 迷宫宽度
*                   my_maze - 迷宫状态数组（墙、道路）
*                   my_route - 路径状态数组
*                   route - 存储路径的栈
*                   Start - 起点坐标
*                   End - 终点坐标
*                   min_size - 最小迷宫尺寸
* Member Functions:
*                   Maze() - 默认构造函数，初始化迷宫为最小尺寸
*                   Maze(int height, int width) - 带参数的构造函数，根据给定的高度和宽度初始化迷宫
*                   ~Maze() - 析构函数，释放迷宫和路径数组的内存
*                   void setHeight(int height_) - 设置迷宫高度
*                   void setWidth(int width_) - 设置迷宫宽度
*                   void MakeEmpty() - 清除迷宫数组和路径数组所占内存
*                   void Draw() - 生成并打印迷宫
*                   bool FindPath() - 查找从起点到终点的路径
*                   void PrintRoute() - 打印找到的路径
*                   void Initial() - 初始化迷宫数组和起点、终点
*                   void BreakWall(int x1, int y1, int x2, int y2) const - 打破两点之间的墙壁
*                   bool inBounds(int x, int y) const - 检查坐标是否在迷宫范围内
*                   void DrawMaze(int x, int y) - 递归方法生成迷宫
*                   bool GoThrough(int x, int y, int direction=0) - 递归查找路径
*                   void PrintMaze(bool is_print_route) const - 打印迷宫（可选打印路径）
***********************************************************/
class Maze {
private:
	const int UP=1;         // 上方向
	const int DOWN=2;      // 下方向
	const int LEFT=3 ;      // 左方向
	const int RIGHT =4;     //右方向

	const int min_size=5;
	int height;
	int width;
	enum State{WALL,ROAD,PATH};
	struct RouteDot {
		int x;
		int y;
	}Start{ 1,1 }, End{ height - 2,width - 2 };// 定义起点和终点
	State**my_maze;// 迷宫数组
	Stack<RouteDot> route;
private:
	void Initial();
	void BreakWall(int x1, int y1, int x2, int y2) const {my_maze[(x1 + x2) / 2][(y1 + y2) / 2] = ROAD;}
	bool inBounds(int x, int y) const {return (x > 0 && x < height-1 && y > 0 && y < width-1);}
	void DrawMaze(int x,int y);
	bool GoThrough(int x,int y,int direction=0);
    void  PrintMaze(bool is_print_route) const;
public:
	Maze():height(min_size),width(min_size),my_maze(nullptr){}
	Maze(int height, int width):height(height>=min_size?(height%2==0?height+1:height):min_size),width(width>=min_size?(width%2==0?width+1:width):min_size),my_maze(nullptr){Initial();}
	~Maze(){MakeEmpty();}
	void setHeight(int iheight){height=(iheight%2==0?iheight+1:iheight);}
	void setWidth(int iwidth){width=(iwidth%2==0?iwidth+1:iwidth);}
	void MakeEmpty();
	void Draw(){srand(static_cast<unsigned>(time(nullptr))); DrawMaze(Start.x, Start.y); std::cout<<"生成迷宫为：\n"; PrintMaze(false);}
	bool FindPath(){return GoThrough(Start.x, Start.y);}
	void PrintRoute();
};

/***********************************************************
* Function Name:   Initial
* Function:        初始化起点和终点，以及迷宫数组和轨迹数组
* Input Parameter:
* Returned Value:
***********************************************************/
void Maze::Initial()
{
	// 设置起点坐标
	Start.x=1;
	Start.y=1;
	// 设置终点坐标
	End.x=height-2;
	End.y=width-2;
	if(my_maze!=nullptr)// 如果迷宫已存在，则直接返回
		return;
	my_maze=new State*[height];// 创建迷宫数组
	assert(my_maze!=nullptr);
	for(int i=0;i<height;i++) {
		my_maze[i]=new State[width];
		assert(my_maze[i]!=nullptr);
	}
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++) {
			my_maze[i][j]=WALL;
		}
}

/***********************************************************
* Function Name:   MakeEmpty
* Function:        清除迷宫数组和轨迹数组所占内存
* Input Parameter:
* Returned Value:
***********************************************************/
void Maze::MakeEmpty()
{
	if(my_maze==nullptr)
		return;
	for(int i=0;i<height;i++)
			delete[] my_maze[i];
	delete[] my_maze;
	my_maze=nullptr;
}

/***********************************************************
* Function Name:   DrawMaze
* Function:        使用递归方法生成迷宫
* Input Parameter: x - 当前坐标x
*                  y - 当前坐标y
***********************************************************/
void Maze::DrawMaze(int x,int y)
{
    if(my_maze==nullptr)// 如果迷宫未初始化，调用初始化
    	Initial();
	my_maze[x][y] = ROAD;// 标记当前点为道路


    constexpr int directions[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
	int dir_order[4] = { UP,DOWN,LEFT,RIGHT };

	// 随机打乱方向顺序
	dir_order[0] = rand() % 4 + 1;// 随机选择一个方向
	do {
		dir_order[1] = rand() % 4 + 1;// 随机选择第二个方向
	} while (dir_order[1]== dir_order[0]);// 确保不同
	do {
		dir_order[2] = rand() % 4 + 1;// 随机选择第三个方向
	} while (dir_order[2] == dir_order[1]||dir_order[2] == dir_order[0]); // 确保不同
	dir_order[3] = UP * DOWN * LEFT * RIGHT / dir_order[0] / dir_order[1] / dir_order[2];// 确定最后一个方向

	// 遍历每个方向
	for (int i : dir_order) {
		int dir = i - 1;// 获取方向索引
		int nx = x + directions[dir][0]*2;// 计算下一个x坐标
		int ny = y + directions[dir][1]*2;// 计算下一个y坐标

		// 检查下一个坐标是否在范围内且未被访问
		if (inBounds(nx, ny)&&my_maze[nx][ny]==WALL) {
			BreakWall(x, y, nx, ny);// 打破墙壁
			DrawMaze(nx, ny);
		}
	}

}

/***********************************************************
* Function Name:   GoThrough
* Function:        通过递归找到迷宫的路径
* Input Parameter: route - 用于存储路径的栈
*                  x - 当前坐标x
*                  y - 当前坐标y
*                  direction - 上一步的方向
* Returned Value:  如果找到路径返回true，否则返回false
***********************************************************/
bool Maze::GoThrough(int x,int y,int direction)
{
	RouteDot dot{ x,y };// 当前点
	if (!(inBounds(x, y)&& my_maze[x][y]==ROAD)) // 检查坐标是否有效
		return false;
	if (x == End.x && y == End.y) {// 如果到达终点
		route.Push(dot);// 将点加入路径
		my_maze[x][y] = PATH;
		return true;
	}

	// 尝试四个方向
	if (direction != DOWN && GoThrough(x - 1, y, UP)) {
		route.Push(dot);
		my_maze[x][y] = PATH;
		return true;
	}
	if (direction != UP && GoThrough(x + 1, y, DOWN)) {
		route.Push(dot);
		my_maze[x][y] = PATH;
		return true;
	}
	if (direction != RIGHT && GoThrough(x, y - 1, LEFT)) {
		route.Push(dot);
		my_maze[x][y] = PATH;
		return true;
	}
	if (direction != LEFT && GoThrough(x, y + 1, RIGHT)) {
		route.Push(dot);
		my_maze[x][y] = PATH;
		return true;
	}

	return false;// 如果没有路径返回false
}
/***********************************************************
* Function Name:   PrintMaze
* Function:        打印迷宫
* Input Parameter: is_print_route: false-不打印轨迹
*                                  true:-打印轨迹
* Returned Value:
***********************************************************/
void  Maze::PrintMaze(bool is_print_route) const {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j <width; j++) {
			if (my_maze[i][j]!=WALL) {
				if(i==Start.x&&j==Start.y)
					std::cout<<"始";
				else if (i==End.x&&j==End.y)
					std::cout<<"终";
				else {
					if(is_print_route) {
						if(my_maze[i][j]==PATH)
							std::cout<<"。";
						else
							std::cout<<"  ";
					}
					else
						std::cout<<"  ";

				}
			}
			else
				std::cout << "墙";// 打印墙壁
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

/***********************************************************
* Function Name:   PrintSolution
* Function:        打印迷宫地图和找到的路径
* Input Parameter:
* Returned Value:
***********************************************************/
void Maze::PrintRoute()
{
	std::cout << "\n迷宫地图为：\n";
	PrintMaze(true);
	std::cout << "\n迷宫路径：\n";
	bool first=true;
	int h=0;
	while(!route.IsEmpty()) {
		h++;
		if(!first)
			std::cout << " ---> ";
		RouteDot path=route.Pop();
		std::cout << "<" << path.x << "," << path.y << ">";
		first=false;
		if(h%10==0)
			std::cout<<"\n";
	}
	std::cout << "\n";
}



/***********************************************************
* Function Name:   Inout
* Function:        输入迷宫的高度或宽度
* Input Parameter: str - 输入提示信息
* Returned Value:  输入的宽度或高度
***********************************************************/


int Input(const char* str)
{
	int temp;
	double d_temp;
	while(true) {
		std::cout<<"请输入迷宫的"<<str<<"(应当为不小于5的正奇数)：\n";
		std::cin>>d_temp;
		if(std::cin.fail()||d_temp !=static_cast<int>(d_temp)||d_temp<5||static_cast<int>(d_temp)%2==0) {
			std::cout<<"输入不符合要求！\n";
			std::cin.clear();
			std::cin.ignore(1000000000,'\n');
			continue;
		}
		temp=static_cast<int>(d_temp);
		std::cin.clear();
		std::cin.ignore(1000000000,'\n');
		break;
	}
	return temp;
}

/***********************************************************
* Function Name:   Maze
* Function:        生成迷宫并寻找路径
***********************************************************/
void MazeAdventureGame()
{
	std::cout << "+-----------------------+\n" ;
	std::cout << "|     勇闯迷宫游戏      |\n" ;
	std::cout << "|  Maze Adventure Game  |\n" ;
	std::cout << "+-----------------------+\n" ;
	Maze maze;
	maze.setHeight(Input("高度"));
	maze.setWidth(Input("宽度"));
	maze.Draw();

	if (maze.FindPath())// 查找路径
		maze.PrintRoute();// 打印路径
	else
		std::cout << "没有路径\n";
}

/***********************************************************
* Function Name:   main
* Function:        程序入口
***********************************************************/
int main() {

	// 生成迷宫并寻找路径
	MazeAdventureGame();

	return 0;
}
