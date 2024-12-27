

#ifndef AOPT4STAR_H
#define AOPT4STAR_H
#include"AOpt2Star.h"

class AOpt4Star : public AOpt2Star {
   virtual double heuristic(int x1, int y1, int x2, int y2) override
    {
        return 1.5 * (std::abs(x1 - x2) + std::abs(y1 - y2));
    }
};
#endif //AOPT4STAR_H
