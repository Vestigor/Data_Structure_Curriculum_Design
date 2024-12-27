#ifndef AFINALSTAR_H
#define AFINALSTAR_H
#include "AOpt5Star.h"

class AFinalStar : public AOpt5Star
{
  public:
     virtual double heuristic(int x1, int y1, int x2, int y2) override
    {
        return 1.5 * (std::abs(x1 - x2) + std::abs(y1 - y2));
    }
};

#endif //AFINALSTAR_H
