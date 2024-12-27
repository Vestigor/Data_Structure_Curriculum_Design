#ifndef AOPT6STAR_H
#define AOPT6STAR_H
#include "AOpt3Star.h"
class AOpt6Star : public AOpt3Star{
 public:
   virtual double heuristic(int x1, int y1, int x2, int y2) override
    {
        return 1.5 * (std::abs(x1 - x2) + std::abs(y1 - y2));
    }
 };
#endif //AOPT6STAR_H
