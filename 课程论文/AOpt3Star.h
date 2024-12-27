
#ifndef AOPT3STAR_H
#define AOPT3STAR_H
#include"ABaseStar.h"
#include <omp.h>

class AOpt3Star : public ABaseStar{
public:
    virtual std::vector<Node*> aStarSearch(const Node& start,
                                          const Node& goal,
                                          const std::vector<std::vector<int>>& grid) override
{
    int rows = grid.size();
    int cols = grid[0].size();

    //gScore[x][y] 存放从起点到 (x,y) 的最优 g 值，初始化为无穷大
    std::vector<std::vector<double>> gScore(rows, std::vector<double>(cols, std::numeric_limits<double>::max()));
    //closedSet[x][y] 表示该节点是否已经确定最优(已扩展)
    std::vector<std::vector<bool>> closedSet(rows, std::vector<bool>(cols, false));

    //优先队列（小根堆），按 f 值最小优先
    //对于并行操作，需要小心处理共享资源
    std::priority_queue<Node*, std::vector<Node*>, NodeCompare> openSet;

    //将起点放入 openSet
    Node* startNode = new Node(start.x, start.y, 0.0, heuristic(start.x, start.y, goal.x, goal.y), nullptr);
    gScore[start.x][start.y] = 0.0;
    openSet.push(startNode);

    while (!openSet.empty()) {
        // 取出f值最小的节点
        Node* current = openSet.top();
        openSet.pop();

        // 如果该节点已经被扩展过，跳过
        if (closedSet[current->x][current->y]) {
            delete current;  // 释放这块内存
            continue;
        }
        // 标记为已扩展
        closedSet[current->x][current->y] = true;

        // 如果到达目标，直接还原路径
        if (current->x == goal.x && current->y == goal.y) {
            std::vector<Node*> path = reconstructPath(current);
            return path;
        }

        //获取邻居坐标
        auto neighborCoords = getNeighborCoords(current->x, current->y, grid);

        //并行拓展邻居
        //对每个邻居执行相同的代价计算和数据更新
        //并行计算临时结果 -> 统一推入队列
        std::vector<Node*> newNodes;
        newNodes.reserve(neighborCoords.size());

        // 并行区域
        #pragma omp parallel
        {
            // 每个线程独立维护一个临时容器
            std::vector<Node*> localNodes;
            localNodes.reserve(neighborCoords.size());

            #pragma omp for nowait
            for (int i = 0; i < (int)neighborCoords.size(); i++) {
                int nx = neighborCoords[i].first;
                int ny = neighborCoords[i].second;

                // 如果已经在 closedSet，则无需处理
                if (closedSet[nx][ny]) {
                    continue;
                }

                double tentative_g = gScore[current->x][current->y] + 1.0;
                // 如果发现更优路径
                if (tentative_g < gScore[nx][ny]) {
                    // 这里要读取共享数据gScore[nx][ny]，同时需保证线程安全
                    Node* neighborNode = new Node(nx, ny, tentative_g,
                                                  heuristic(nx, ny, goal.x, goal.y),
                                                  current);
                    // 暂存在本线程的 localNodes
                    localNodes.push_back(neighborNode);
                }
            }

            // 结束并行 for 后，将本线程产生的新节点合并回 newNodes
            #pragma omp critical
            {
                newNodes.insert(newNodes.end(), localNodes.begin(), localNodes.end());
            }
        }

        //统一更新 gScore 并推入 openSet
        for (auto n : newNodes) {
            int nx = n->x;
            int ny = n->y;
            // 处理不同线程写入使可能存在的竞态
            double tentative_g = n->g;
            if (tentative_g < gScore[nx][ny]) {
                gScore[nx][ny] = tentative_g;
                openSet.push(n);
            } else {
                delete n; // 如果发现 gScore 已被更新得更优，就丢弃
            }
        }
    }

    // 没找到路径
    return {};
}

  };
#endif //AOPT3STAR_H
