
#ifndef ABASESTAR_H
#define ABASESTAR_H

#include <queue>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>

struct Node {
    int x, y; // 坐标
    double g, h; // g: 从起点到该节点的代价, h: 启发式估计
    Node *parent; // 父节点指针，用于还原路径

    Node(int x_, int y_, double g_ = 0.0, double h_ = 0.0, Node *parent_ = nullptr)
        : x(x_), y(y_), g(g_), h(h_), parent(parent_) {}

    double f() const { return g + h; }
};

struct NodeCompare {
    bool operator()(const Node *a, const Node *b) const
    {
        return a->f() > b->f();
    }
};


class ABaseStar{
  public:


    ABaseStar(){};
    ~ABaseStar(){}

    virtual double heuristic(int x1, int y1, int x2, int y2)
    {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }

    virtual std::vector<std::pair<int, int> > getNeighborCoords(int x, int y,
                                                               const std::vector<std::vector<int> > &grid)
    {
        static const std::vector<std::pair<int, int> > directions = {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0}
        };

        std::vector<std::pair<int, int> > neighbors;
        for (auto &dir: directions) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            // 判断越界和是否可通行
            if (nx >= 0 && nx < (int) grid.size() &&
                ny >= 0 && ny < (int) grid[0].size() &&
                grid[nx][ny] == 1) {
                neighbors.emplace_back(nx, ny);
            }
        }
        return neighbors;
    }

    virtual std::vector<Node *> reconstructPath(Node *goal)
    {
        std::vector<Node *> path;
        Node *current = goal;
        while (current) {
            path.push_back(current);
            current = current->parent;
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    virtual std::vector<Node *> aStarSearch(const Node &start,
                                    const Node &goal,
                                    const std::vector<std::vector<int> > &grid)
    {
        int rows = grid.size();
        int cols = grid[0].size();

        // 用于记录从起点到各 (x,y) 已发现的最优代价
        std::vector<std::vector<double> > gScore(
            rows, std::vector<double>(cols, std::numeric_limits<double>::max()));
        // 用于标识某个 (x,y) 是否已“最终确定”
        std::vector<std::vector<bool> > closedSet(rows, std::vector<bool>(cols, false));

        // 定义一个优先队列 (openSet), 按 f 值(= g + h) 最小优先
        std::priority_queue<Node *, std::vector<Node *>, NodeCompare> openSet;

        // 起点入队，设置其 g, h
        Node *startNode = new Node(start.x, start.y, 0.0,
                                   heuristic(start.x, start.y, goal.x, goal.y));
        gScore[start.x][start.y] = 0.0;
        openSet.push(startNode);

        while (!openSet.empty()) {
            // 取出 f 值最小的节点
            Node *current = openSet.top();
            openSet.pop();

            // 如果已经在 closedSet 中，直接跳过
            if (closedSet[current->x][current->y]) {
                delete current;
                continue;
            }

            // 将当前节点标记为已确定
            closedSet[current->x][current->y] = true;

            // 如果到达目标节点，则还原路径返回
            if (current->x == goal.x && current->y == goal.y) {
                auto path = reconstructPath(current);
                while (!openSet.empty()) {
                    Node *n = openSet.top();
                    openSet.pop();
                    delete n;
                }

                return path;
            }

            // 遍历邻居
            auto neighborCoords = getNeighborCoords(current->x, current->y, grid);
            for (auto [nx, ny]: neighborCoords) {
                // 若已在 closedSet，则无需处理
                if (closedSet[nx][ny]) {
                    continue;
                }

                // 计算从起点到邻居的临时 g 值
                double tentative_g = gScore[current->x][current->y] + 1.0; // 假设移动代价=1

                // 如果发现更优路径
                if (tentative_g < gScore[nx][ny]) {
                    gScore[nx][ny] = tentative_g;
                    double hVal = heuristic(nx, ny, goal.x, goal.y);

                    Node *neighborNode = new Node(nx, ny, tentative_g, hVal, current);
                    openSet.push(neighborNode);
                }
            }
        }

        // 没找到路径
        return {};
    }

};

#endif //ABASESTAR_H
