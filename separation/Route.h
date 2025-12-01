#ifndef SEPARATION_ROUTE_H
#define SEPARATION_ROUTE_H

namespace separation {

class Route {
public:
    int neighbor;
    int distance;
    int traffic;   // 0..10
    bool isBlocked;

    Route(int n = -1, int d = 0);
};

} // namespace separation

#endif // SEPARATION_ROUTE_H
