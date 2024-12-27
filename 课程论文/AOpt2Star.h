

#ifndef AOPT2STAR_H
#define AOPT2STAR_H
#include"ABaseStar.h"

class AOpt2Star : public ABaseStar
{
  public:
    virtual std::vector<Node*> reconstructPathBidirectional(Node* intersectionFwd, Node* intersectionBwd) {
        // 从前向相遇点回溯到起点
        std::vector<Node*> pathFwd;
        {
            Node* curr = intersectionFwd;
            while (curr) {
                pathFwd.push_back(curr);
                curr = curr->parent;
            }
            std::reverse(pathFwd.begin(), pathFwd.end());
        }
        std::vector<Node*> pathBwd;
        {
            Node* curr = intersectionBwd;
            while (curr) {
                pathBwd.push_back(curr);
                curr = curr->parent;
            }

        }
        // 拼接时去掉 pathBwd 的第一个点以免重复
        if (!pathBwd.empty()) {
            pathBwd.erase(pathBwd.begin());
        }
        // 然后把 pathBwd 的节点追加到 pathFwd 之后
        std::reverse(pathBwd.begin(), pathBwd.end());
        pathFwd.insert(pathFwd.end(), pathBwd.begin(), pathBwd.end());
        return pathFwd;
    }


    virtual std::vector<Node*> aStarSearch (
    const Node& start,
    const Node& goal,
    const std::vector<std::vector<int>>& grid) override
{
    int rows = (int)grid.size();
    int cols = (int)grid[0].size();

    //  前向和后向各自的 gScore, closedSet
    //  ScoreFwd[x][y]: 前向搜索中 (x,y) 的 g 值
    //  gScoreBwd[x][y]: 后向搜索中 (x,y) 的 g 值
    std::vector<std::vector<int>> gScoreFwd(rows, std::vector<int>(cols, std::numeric_limits<int>::max()));
    std::vector<std::vector<int>> gScoreBwd(rows, std::vector<int>(cols, std::numeric_limits<int>::max()));
    std::vector<std::vector<bool>> closedSetFwd(rows, std::vector<bool>(cols, false));
    std::vector<std::vector<bool>> closedSetBwd(rows, std::vector<bool>(cols, false));

    // 前向和后向的 openSet
    std::priority_queue<Node*, std::vector<Node*>, NodeCompare> openSetFwd;
    std::priority_queue<Node*, std::vector<Node*>, NodeCompare> openSetBwd;

    // 起点进前向 openSet，目标进后向 openSet
    Node* startNode = new Node(start.x, start.y, 0, heuristic(start.x, start.y, goal.x, goal.y));
    Node* goalNode  = new Node(goal.x, goal.y, 0, heuristic(goal.x, goal.y, start.x, start.y));
    gScoreFwd[start.x][start.y] = 0;
    gScoreBwd[goal.x][goal.y]   = 0;
    openSetFwd.push(startNode);
    openSetBwd.push(goalNode);

    // 为了在相遇时拼接路径，需要保留所有已经生成的 Node 指针
    std::vector<std::vector<Node*>> cameFromFwd(rows, std::vector<Node*>(cols, nullptr));
    std::vector<std::vector<Node*>> cameFromBwd(rows, std::vector<Node*>(cols, nullptr));

    cameFromFwd[start.x][start.y] = startNode;
    cameFromBwd[goal.x][goal.y]   = goalNode;

    while (!openSetFwd.empty() && !openSetBwd.empty()) {

        // 扩展前向搜索
        Node* currentFwd = openSetFwd.top();
        openSetFwd.pop();

        if (closedSetFwd[currentFwd->x][currentFwd->y]) {
            delete currentFwd;
        } else {
            closedSetFwd[currentFwd->x][currentFwd->y] = true;

            // 检查该节点是否已在后向搜索的 closedSet中
            if (closedSetBwd[currentFwd->x][currentFwd->y]) {
                // 在后向搜索一侧拿到对应坐标的节点
                Node* meetBwd = cameFromBwd[currentFwd->x][currentFwd->y];
                // 拼接路径
                auto fullPath = reconstructPathBidirectional(currentFwd, meetBwd);
                return fullPath;
            }

            // 继续扩展它的邻居
            for (auto [nx, ny] : getNeighborCoords(currentFwd->x, currentFwd->y, grid)) {
                if (closedSetFwd[nx][ny])
                    continue;
                int tentative_g = gScoreFwd[currentFwd->x][currentFwd->y] + 1;
                if (tentative_g < gScoreFwd[nx][ny]) {
                    gScoreFwd[nx][ny] = tentative_g;
                    double hVal = heuristic(nx, ny, goal.x, goal.y);
                    Node* neighborNode = new Node(nx, ny, tentative_g, hVal, currentFwd);
                    cameFromFwd[nx][ny] = neighborNode;
                    openSetFwd.push(neighborNode);
                }
            }
        }

        //扩展后向搜索
        Node* currentBwd = openSetBwd.top();
        openSetBwd.pop();

        if (closedSetBwd[currentBwd->x][currentBwd->y]) {
            delete currentBwd;
        } else {
            closedSetBwd[currentBwd->x][currentBwd->y] = true;

            // 检查该节点是否已在前向搜索的 closedSet 中
            if (closedSetFwd[currentBwd->x][currentBwd->y]) {
                // 在前向搜索一侧拿到对应坐标的节点
                Node* meetFwd = cameFromFwd[currentBwd->x][currentBwd->y];
                // 拼接路径
                auto fullPath = reconstructPathBidirectional(meetFwd, currentBwd);
                return fullPath;
            }

            // 继续扩展它的邻居
            for (auto [nx, ny] : getNeighborCoords(currentBwd->x, currentBwd->y, grid)) {
                if (closedSetBwd[nx][ny]) continue;
                int tentative_g = gScoreBwd[currentBwd->x][currentBwd->y] + 1;
                if (tentative_g < gScoreBwd[nx][ny]) {
                    gScoreBwd[nx][ny] = tentative_g;
                    double hVal = heuristic(nx, ny, start.x, start.y);
                    Node* neighborNode = new Node(nx, ny, tentative_g, hVal, currentBwd);
                    cameFromBwd[nx][ny] = neighborNode;
                    openSetBwd.push(neighborNode);
                }
            }
        }
    }

    // 如果两个 openSet 有一个耗尽时仍没相遇，则无路径
    return {};
}
 };

#endif //AOPT2STAR_H
