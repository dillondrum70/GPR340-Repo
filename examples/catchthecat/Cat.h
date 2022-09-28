#ifndef CAT_H
#define CAT_H

#include "Agent.h"

class Cat: public Agent {
private:
    bool noEscape = false;

public:
    explicit Cat():Agent(){};
    Point2D Move(World *) override;
    void Reset() { noEscape = false; }
};

#endif  // CAT_H
