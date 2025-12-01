#include "Route.h"

namespace separation {

Route::Route(int n, int d) : neighbor(n), distance(d), traffic(0), isBlocked(false) {}

} // namespace separation
