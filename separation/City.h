#ifndef SEPARATION_CITY_H
#define SEPARATION_CITY_H

#include <string>
#include <climits>

namespace separation {

class City {
public:
    int distance;
    std::string name;

    City();
    City(const std::string &name_, int distance_ = INT_MAX);
};

} // namespace separation

#endif // SEPARATION_CITY_H
