
#ifndef AOPT5STAR_H
#define AOPT5STAR_H

#include <vector>
#include <queue>
#include <limits>
#include <thread>
#include <mutex>
#include <atomic>
#include"AOpt2Star.h"


class AOpt5Star : public AOpt2Star {
public:
    void forwardSearchThreadFunc(
        const std::vector<std::vector<int> > &grid,
        const Node &start,
        const Node &goal,
        std::vector<std::vector<double> > &gScoreFwd,
        std::vector<std::vector<bool> > &closedFwd,
        std::vector<std::vector<Node *> > &cameFromFwd,
        std::priority_queue<Node *, std::vector<Node *>, NodeCompare> &openSetFwd,
        std::mutex &mtxFwd,
        std::atomic<bool> &found,
        Node *&meetFwd,
        Node *&meetBwd,
        // 对方数据
        std::vector<std::vector<bool> > &closedBwd,
        std::vector<std::vector<Node *> > &cameFromBwd,
        std::mutex &mtxBwd
    )
    {
        //始化起点
        Node *startNode = new Node(start.x, start.y, 0.0,
                                   heuristic(start.x, start.y, goal.x, goal.y)); {
            std::lock_guard<std::mutex> lock(mtxFwd);
            gScoreFwd[start.x][start.y] = 0.0;
            cameFromFwd[start.x][start.y] = startNode;
            openSetFwd.push(startNode);
        }

        //循环
        while (!found) {
            Node *current = nullptr;

            //从 openSetFwd 取出 f 值最小的节点
            {
                std::lock_guard<std::mutex> lock(mtxFwd);
                if (openSetFwd.empty()) {
                    break; // 无路可走
                }
                current = openSetFwd.top();
                openSetFwd.pop();
            }

            //若已关闭，则跳过
            if (closedFwd[current->x][current->y]) {
                delete current;
                continue;
            }

            //标记已扩展
            closedFwd[current->x][current->y] = true;

            //若后向搜索已扩展此坐标，则说明相遇
            {
                std::lock_guard<std::mutex> lockBwd(mtxBwd);
                if (closedBwd[current->x][current->y]) {
                    // 相遇，记录 meet 节点
                    meetFwd = current;
                    meetBwd = cameFromBwd[current->x][current->y];
                    found = true;
                    break;
                }
            }

            //拓展邻居
            auto neighbors = getNeighborCoords(current->x, current->y, grid);
            for (auto &nb: neighbors) {
                int nx = nb.first;
                int ny = nb.second;
                if (closedFwd[nx][ny]) {
                    continue;
                }

                double tentative_g = gScoreFwd[current->x][current->y] + 1.0; // 假设移动代价=1
                double old_g = gScoreFwd[nx][ny];
                if (tentative_g < old_g) {
                    // 构造 neighborNode
                    Node *neighborNode = new Node(nx, ny, tentative_g,
                                                  heuristic(nx, ny, goal.x, goal.y), current); {
                        std::lock_guard<std::mutex> lock(mtxFwd);
                        gScoreFwd[nx][ny] = tentative_g;
                        cameFromFwd[nx][ny] = neighborNode;
                        openSetFwd.push(neighborNode);
                    }
                }
            }
        }
    }

    void backwardSearchThreadFunc(
        const std::vector<std::vector<int> > &grid,
        const Node &start, // "goal"坐标
        const Node &goal, // "start"坐标
        std::vector<std::vector<double> > &gScoreBwd,
        std::vector<std::vector<bool> > &closedBwd,
        std::vector<std::vector<Node *> > &cameFromBwd,
        std::priority_queue<Node *, std::vector<Node *>, NodeCompare> &openSetBwd,
        std::mutex &mtxBwd,
        std::atomic<bool> &found,
        Node *&meetFwd,
        Node *&meetBwd,
        // 对方数据
        std::vector<std::vector<bool> > &closedFwd,
        std::vector<std::vector<Node *> > &cameFromFwd,
        std::mutex &mtxFwd
    )
    {
        //初始化"起点"
        Node *goalNode = new Node(start.x, start.y, 0.0,
                                  heuristic(start.x, start.y, goal.x, goal.y)); {
            std::lock_guard<std::mutex> lock(mtxBwd);
            gScoreBwd[start.x][start.y] = 0.0;
            cameFromBwd[start.x][start.y] = goalNode;
            openSetBwd.push(goalNode);
        }

        while (!found) {
            Node *current = nullptr; {
                std::lock_guard<std::mutex> lock(mtxBwd);
                if (openSetBwd.empty()) {
                    break;
                }
                current = openSetBwd.top();
                openSetBwd.pop();
            }

            if (closedBwd[current->x][current->y]) {
                delete current;
                continue;
            }
            closedBwd[current->x][current->y] = true;

            {
                std::lock_guard<std::mutex> lockFwd(mtxFwd);
                if (closedFwd[current->x][current->y]) {
                    meetBwd = current;
                    meetFwd = cameFromFwd[current->x][current->y];
                    found = true;
                    break;
                }
            }

            auto neighbors = getNeighborCoords(current->x, current->y, grid);
            for (auto &nb: neighbors) {
                int nx = nb.first;
                int ny = nb.second;
                if (closedBwd[nx][ny]) {
                    continue;
                }
                double tentative_g = gScoreBwd[current->x][current->y] + 1.0;
                double old_g = gScoreBwd[nx][ny];
                if (tentative_g < old_g) {
                    Node *neighborNode = new Node(nx, ny, tentative_g,
                                                  heuristic(nx, ny, goal.x, goal.y), current); {
                        std::lock_guard<std::mutex> lock(mtxBwd);
                        gScoreBwd[nx][ny] = tentative_g;
                        cameFromBwd[nx][ny] = neighborNode;
                        openSetBwd.push(neighborNode);
                    }
                }
            }
        }
    }

     virtual std::vector<Node *> aStarSearch(
        const Node &start,
        const Node &goal,
        const std::vector<std::vector<int> > &grid) override
    {
        //初始化
        int rows = (int) grid.size();
        int cols = (int) grid[0].size();

        // 前向数据
        std::vector<std::vector<double> > gScoreFwd(
            rows, std::vector<double>(cols, std::numeric_limits<double>::infinity()));
        std::vector<std::vector<bool> > closedFwd(rows, std::vector<bool>(cols, false));
        std::vector<std::vector<Node *> > cameFromFwd(rows, std::vector<Node *>(cols, nullptr));
        std::priority_queue<Node *, std::vector<Node *>, NodeCompare> openSetFwd;
        std::mutex mtxFwd;

        // 后向数据
        std::vector<std::vector<double> > gScoreBwd(
            rows, std::vector<double>(cols, std::numeric_limits<double>::infinity()));
        std::vector<std::vector<bool> > closedBwd(rows, std::vector<bool>(cols, false));
        std::vector<std::vector<Node *> > cameFromBwd(rows, std::vector<Node *>(cols, nullptr));
        std::priority_queue<Node *, std::vector<Node *>, NodeCompare> openSetBwd;
        std::mutex mtxBwd;

        // 共享标志
        std::atomic<bool> found(false);

        // 相遇节点
        Node *meetFwd = nullptr;
        Node *meetBwd = nullptr;


        std::thread tFwd([this, &grid, &start, &goal, &gScoreFwd, &closedFwd, &cameFromFwd,
            &openSetFwd, &mtxFwd, &found, &meetFwd, &meetBwd, &closedBwd, &cameFromBwd, &mtxBwd] {
            this->forwardSearchThreadFunc(
                grid,
                start,
                goal,
                gScoreFwd,
                closedFwd,
                cameFromFwd,
                openSetFwd,
                mtxFwd,
                found,
                meetFwd,
                meetBwd,
                closedBwd,
                cameFromBwd,
                mtxBwd
            );
        });

        std::thread tBwd([this, &grid, &start, &goal, &gScoreBwd, &closedBwd, &cameFromBwd,
            &openSetBwd, &mtxBwd, &found, &meetFwd, &meetBwd, &closedFwd, &cameFromFwd, &mtxFwd] {
            this->backwardSearchThreadFunc(
                grid,
                goal, // 后向搜索，起点是goal
                start, // 终点是start
                gScoreBwd,
                closedBwd,
                cameFromBwd,
                openSetBwd,
                mtxBwd,
                found,
                meetFwd,
                meetBwd,
                closedFwd,
                cameFromFwd,
                mtxFwd
            );
        });

        //等待线程结束
        tFwd.join();
        tBwd.join();

        //found为true说明相遇，即存在路径，拼接路径
        if (found && meetFwd && meetBwd) {
            return reconstructPathBidirectional(meetFwd, meetBwd);
        }

        // 返回空路径
        return {};
    }
};

#endif //AOPT5STAR_H
