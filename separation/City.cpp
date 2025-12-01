#include "City.h"

namespace separation {

City::City() : distance(INT_MAX), name("") {}
City::City(const std::string &name_, int distance_) : distance(distance_), name(name_) {}

} // namespace separation
