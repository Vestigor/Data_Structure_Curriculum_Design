
#ifndef AOPT1STAR_H
#define AOPT1STAR_H
#include"ABaseStar.h"

class AOpt1Star : public ABaseStar {
public:
    virtual double heuristic(int x1, int y1, int x2, int y2) override
    {
        return 0.5* (std::abs(x1 - x2) + std::abs(y1 - y2));
    }
};


#endif //AOPT1STAR_H
